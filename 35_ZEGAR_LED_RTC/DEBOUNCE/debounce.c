/*
 * debounce.c
 *
 *  Created on: 20 sie 2015
 *      Author: Daniel
 */

#include <avr/io.h>
#include <avr/interrupt.h>

#include "debounce.h"

volatile uint16_t timer0, timer1, timer2;		// timery programowe - przerwanie co 10ms (100Hz)

void program_timer_init(void)
{
	/* ustawienie TIMER2 dla F_CPU=8000000MHz */
	TCCR2A |= (1<<WGM21);						/* tryb CTC */
	TCCR2B |= (1<<CS22)|(1<<CS21)|(1<<CS20);		/* preskaler = 1024 */
	OCR2A = 78;									/* dodatkowy podzia³ przez 78 (rej. przepe³nienia) */
	TIMSK2 |= (1<<OCIE1A);						/* zezwolenie na przerwanie CompareMatch */
	/* przerwanie wykonywane z czêstotliwoœci¹ ok 10ms (100 razy na sekundê) */
}

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
		timer0 = 5;
	}
	else
	{
		// jesli przycisk nadal wcisniety, a minal juz czas drgan stykow
		if(key_state)
		{
			if(key_press && debounce == key_state && !timer0)
			{
				key_state = go_rep;
				timer0 = 3; 		// odczekaj jeszcze 30ms po czasie drgan
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
					if(key_press && go_rep == key_state && !timer0)
					{
						// nadanie wartosci domyslnych, jesli parametr mial wartosc = 0
						if(!rep_time) rep_time = 20;
						if(!rep_wait) rep_wait = 150;
						key_state = wait_rep;
						timer0 = rep_wait;
					}
					else
					{
						// jesli minal czas oczekiwania na REPEAT, przejdz do trybu powtawrzania akcji
						if(key_press && wait_rep == key_state && !timer0)
						{
							key_state = rep;
						}
						else
							// tryb powtarzania akcji/funkcji rep_proc, jesli wskaznik rozny od zera
							// przez caly czas, gdy przycik jest wciaz wcisniety
							if(key_press && rep == key_state && !timer0)
							{
								timer0 = rep_time;
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
ISR(TIMER2_COMPA_vect)
{
	uint16_t x;
	// dwa timery programowe (100Hz = 10ms):
	x = timer0;
	if(x) timer0 = --x;
	x = timer1;
	if(x) timer1 = --x;
	x = timer2;
	if(x) timer2 = --x;
}
