/*
 * main.c
 *
 *  Created on: 18 kwi 2017
 *      Author: Daniel
 */

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#include "nRF24L01/nRF24L01.h"
#include "Switch/switch.h"

#define LED_DEBUG (1<<PD0)
#define LED_DEBUG_PORT PORTD
#define LED_DEBUG_DDR DDRD
#define LED_DEBUG_ON LED_DEBUG_PORT |= LED_DEBUG
#define LED_DEBUG_OFF LED_DEBUG_PORT &= ~LED_DEBUG
#define LED_DEBUG_TOG LED_DEBUG_PORT ^= LED_DEBUG

#define S0 (1<<0)
#define S1 (1<<1)
#define S2 (1<<2)
#define S3 (1<<3)
#define S4 (1<<4)
#define S5 (1<<5)
#define S6 (1<<6)
#define S7 (1<<7)

#define S8 (1<<0)
#define S9 (1<<1)
#define S10 (1<<2)

#define BUFF_SIZE 12

// tablica do przeslania
char transmit[BUFF_SIZE];

void program_timer_init(void) {
	/* ustawienie TIMER2 dla F_CPU=8MHzMHz */
	TCCR1B |= (1 << WGM12); /* tryb CTC */
	TCCR1B |= (1 << CS12) | (1 << CS10); /* preskaler = 1024 */
	OCR1A = 108; /* dodatkowy podzia³ przez  (rej. przepe³nienia) */
	TIMSK1 |= (1 << OCIE1A); /* zezwolenie na przerwanie CompareMatch */
	/* przerwanie wykonywane z czêstotliwoœci¹ ok 10ms (100 razy na sekundê) */
}

volatile uint16_t prog_timer1, prog_timer2, prog_timer3, prog_timer4,
		prog_timer5, prog_timer6, prog_timer7, prog_timer8, prog_timer9,
		prog_timer10, prog_timer11;

uint8_t low_stat;
uint8_t high_stat;

int main(void) {
	sw_init();
	//inicjalizacja nRFa
	nRF_init();
	nRF_Set_Channel(6);
	program_timer_init();

	LED_DEBUG_DDR |= LED_DEBUG;
	LED_DEBUG_OFF;

	// zezwolenie na przerwania
	sei();

	prog_timer1 = 30;
	prog_timer2 = 30;
	prog_timer3 = 30;
	prog_timer4 = 30;
	prog_timer5 = 30;
	prog_timer6 = 30;
	prog_timer7 = 30;
	prog_timer8 = 30;
	prog_timer9 = 30;
	prog_timer10 = 30;
	prog_timer11 = 30;

	while (1) {
		// odczyt stanu przyciskow
		//przycisk 1
		if (!(SW1_PIN & SW1)) {
			if (!prog_timer1 && !(SW1_PIN & SW1)) {
				low_stat |= S0;
				transmit[0] = '1';
				prog_timer1 = 30;
			}
		} else {
			low_stat &= ~S0;
			transmit[0] = '0';
		}

		//przycisk 2
		if (!(SW2_PIN & SW2)) {
			if (!prog_timer2 && !(SW2_PIN & SW2)) {
				low_stat |= S1;
				transmit[1] = '1';
				prog_timer2 = 30;
			}
		} else {
			low_stat &= ~S1;
			transmit[1] = '0';
		}

		//przycisk 3
		if (!(SW3_PIN & SW3)) {
			if (!prog_timer3 && !(SW3_PIN & SW3)) {
				low_stat |= S2;
				transmit[2] = '1';
				prog_timer3 = 30;
			}
		} else {
			low_stat &= ~S2;
			transmit[2] = '0';
		}

		//przycisk 4
		if (!(SW4_PIN & SW4)) {
			if (!prog_timer4 && !(SW4_PIN & SW4)) {
				low_stat |= S3;
				transmit[3] = '1';
				prog_timer4 = 30;
			}
		} else {
			low_stat &= ~S3;
			transmit[3] = '0';
		}

		//przycisk 5
		if (!(SW5_PIN & SW5)) {
			if (!prog_timer5 && !(SW5_PIN & SW5)) {
				low_stat |= S4;
				transmit[4] = '1';
				prog_timer5 = 30;
			}
		} else {
			low_stat &= ~S4;
			transmit[4] = '0';
		}

		//przycisk 6
		if (!(SW6_PIN & SW6)) {
			if (!prog_timer6 && !(SW6_PIN & SW6)) {
				low_stat |= S5;
				transmit[5] = '1';
				prog_timer6 = 30;
			}
		} else {
			low_stat &= ~S5;
			transmit[5] = '0';
		}

		//przycisk 7
		if (!(SW7_PIN & SW7)) {
			if (!prog_timer7 && !(SW7_PIN & SW7)) {
				low_stat |= S6;
				transmit[6] = '1';
				prog_timer7 = 30;
			}
		} else {
			low_stat &= ~S6;
			transmit[6] = '0';
		}

		//przycisk 8
		if (!(SW8_PIN & SW8)) {
			if (!prog_timer8 && !(SW8_PIN & SW8)) {
				low_stat |= S7;
				transmit[7] = '1';
				prog_timer8 = 30;
			}
		} else {
			low_stat &= ~S7;
			transmit[7] = '0';
		}

		//przycisk 9
		if (!(SW9_PIN & SW9)) {
			if (!prog_timer9 && !(SW9_PIN & SW9)) {
				high_stat |= S8;
				transmit[8] = '1';
				prog_timer9 = 30;
			}
		} else {
			high_stat &= ~S8;
			transmit[8] = '0';
		}

		//przycisk 10
		if (!(SW10_PIN & SW10)) {
			if (!prog_timer10 && !(SW10_PIN & SW10)) {
				high_stat |= S9;
				transmit[9] = '1';
				prog_timer10 = 30;
			}
		} else {
			high_stat &= ~S9;
			transmit[9] = '0';
		}

		//przycisk 11
		if (!(SW11_PIN & SW11)) {
			if (!prog_timer11 && !(SW11_PIN & SW11)) {
				high_stat |= S10;
				transmit[10] = '1';
				prog_timer11 = 30;
			}
		} else {
			high_stat &= ~S10;
			transmit[10] = '0';
		}

//		if ((low_stat & (S0 | S1 | S2 | S3 | S4 | S5 | S6 | S7))
//				|| (high_stat & (S8 | S9 | S10))) {
//			LED_DEBUG_ON;
//			transmit[BUFF_SIZE - 1] = '\0';
//			nRF_SendDataToAir(transmit); // do dlugosci wlicza sie jeszcze '0' na koniec stringa
//		} else
//			LED_DEBUG_OFF;
		if (low_stat & (S0 | S1 | S6 | S7)) {
			LED_DEBUG_ON;
			transmit[BUFF_SIZE - 1] = '\0';
			nRF_SendDataToAir(transmit); // do dlugosci wlicza sie jeszcze '0' na koniec stringa
		} else
			LED_DEBUG_OFF;
	};
}

ISR(TIMER1_COMPA_vect) {
	uint16_t x;
	//timery programowe (100Hz = 10ms):
	x = prog_timer1;
	if (x)
		prog_timer1 = --x;
	x = prog_timer2;
	if (x)
		prog_timer2 = --x;
	x = prog_timer3;
	if (x)
		prog_timer3 = --x;
	x = prog_timer4;
	if (x)
		prog_timer4 = --x;
	x = prog_timer5;
	if (x)
		prog_timer5 = --x;
	x = prog_timer6;
	if (x)
		prog_timer6 = --x;
	x = prog_timer7;
	if (x)
		prog_timer7 = --x;
	x = prog_timer8;
	if (x)
		prog_timer8 = --x;
	x = prog_timer9;
	if (x)
		prog_timer9 = --x;
	x = prog_timer10;
	if (x)
		prog_timer10 = --x;
	x = prog_timer11;
	if (x)
		prog_timer11 = --x;
}
