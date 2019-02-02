/*
 * debounce.c
 *
 *  Created on: 20 sie 2015
 *      Author: Daniel
 */

#include <avr/io.h>
#include <avr/interrupt.h>

#include "debounce.h"

volatile uint16_t timer_debounce;		// timery programowe - przerwanie co 10ms (100Hz)

void switch_init(void)
{
	SW1_PORT |= SW1;	// pullup
	SW2_PORT |= SW2;
	SW3_PORT |= SW3;
	SW4_PORT |= SW4;
	SW5_PORT |= SW5;

	SW1_DDR &= ~SW1;	// kierunek wejœciowy
	SW2_DDR &= ~SW2;
	SW3_DDR &= ~SW3;
	SW4_DDR &= ~SW4;
	SW5_DDR &= ~SW5;
}

void program_timer_init(void)
{
	/* ustawienie TIMER2 dla F_CPU=8MHzMHz */
	TCCR1B |= (1<<WGM12);						/* tryb CTC */
	TCCR1B |= (1<<CS12)|(1<<CS10);				/* preskaler = 1024 */
	OCR1A = 78;									/* dodatkowy podzia³ przez 78 (rej. przepe³nienia) */
	TIMSK1 |= (1<<OCIE1A);						/* zezwolenie na przerwanie CompareMatch */
	/* przerwanie wykonywane z czêstotliwoœci¹ ok 10ms (100 razy na sekundê) */
}

/*
 * Obsluga przyciskow.
 * (pin przycisku, numer pinu w porcie, czas pomiedzy repami, opoznienie pierwszego repa,
 * normalna funkcja, funkcja repowa)
 */
void SuperDebounce(volatile uint8_t *KPIN, uint8_t key_mask, uint16_t rep_time, uint16_t rep_wait,
		void (*push_proc)(void), void (*rep_proc)(void))
{
	enum KS{idle, debounce, go_rep, wait_rep, rep};

	static enum KS key_state;	// przechowuje stan przycisku, kiedy jest on wcisniety
	static uint8_t last_key;	// ostatnio uzyty przycisku

	uint8_t key_press; 			// bufor stanu przycisku w trakcie dzialania funkcji

	// zabezpieczenie przed jednoczesnym wciskaniem dwoch przyciskow
	if(last_key && last_key != key_mask) return;

	key_press = !(*KPIN & key_mask);	// stan klawisza

	if(key_press && !key_state)
	{
		// jesli wcisniety, poczekaj az mina ddgania stykow (50ms)
		key_state = debounce;
		timer_debounce = 5;
	}
	else
	{
		// jesli przycisk nadal wcisniety, a minal juz czas drgan stykow
		if(key_state)
		{
			if(key_press && debounce == key_state && !timer_debounce)
			{
				key_state = go_rep;
				timer_debounce = 3; 		// odczekaj jeszcze 30ms po czasie drgan
				last_key = key_mask;
			}
			else
				// jesli w czasie czekania na REPEAT przycisk zostal zwolniony
				if(!key_press && key_state > debounce && key_state < rep)
				{
					// wykonaj funkcje, jesli wskaznik rozny od zera
					if(push_proc) push_proc();		//key_up
					key_state = idle;
					last_key = 0;
				}
				else
				{
					// jesli minal czas drgan, zacznij odmierzac czas oczekiwania na REPEAT
					if(key_press && go_rep == key_state && !timer_debounce)
					{
						// nadanie wartosci domyslnych, jesli parametr mial wartosc = 0
						if(!rep_time) rep_time = 20;
						if(!rep_wait) rep_wait = 150;
						key_state = wait_rep;
						timer_debounce = rep_wait;
					}
					else
					{
						// jesli minal czas oczekiwania na REPEAT, przejdz do trybu powtawrzania akcji
						if(key_press && wait_rep == key_state && !timer_debounce)
						{
							key_state = rep;
						}
						else
							// tryb powtarzania akcji/funkcji rep_proc, jesli wskaznik rozny od zera
							// przez caly czas, gdy przycik jest wciaz wcisniety
							if(key_press && rep == key_state && !timer_debounce)
							{
								timer_debounce = rep_time;
								if(rep_proc) rep_proc();		// key_rep
							}
					}
					// jesli klawisz zostal zwolniony w trybie rep, przejdz do stanu oczekiwania
					if(key_state >= wait_rep && ! key_press)
					{
						key_state = idle;
						last_key = 0;
					}
				}
		}
	}
}

/////////////////////////////////////////
// PRZERWANIA TIMEROW PROGRAMOWYCH
////////////////////////////////////////////////////////////
ISR(TIMER1_COMPA_vect)
{
	uint16_t x;
	//timery programowe (100Hz = 10ms):
	x = timer_debounce;
	if(x) timer_debounce = --x;
}
