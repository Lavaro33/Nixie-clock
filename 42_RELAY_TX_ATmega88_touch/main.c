/*
 * main.c
 *
 *  Created on: 18 kwi 2017
 *      Author: Daniel
 */

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#include "MPR121/mpr121.h"
#include "I2C_TWI/i2c_twi.h"
#include "LED/led.h"
#include "nRF24L01/nRF24L01.h"
#include "DEBOUNCE/debounce.h"

#define DEBOUNCE_DELAY1 8
#define DEBOUNCE_DELAY2 8
#define DEBOUNCE_DELAY3 50
#define DEBOUNCE_DELAY4 50

#define BUFF_SIZE 11

#define ELE0 (1<<0)
#define ELE1 (1<<1)
#define ELE2 (1<<2)
#define ELE3 (1<<3)
#define ELE4 (1<<4)
#define ELE5 (1<<5)
#define ELE6 (1<<6)
#define ELE7 (1<<7)

#define ELE8 (1<<0)

void led_init(void);

// tablica do przeslania
char transmit[BUFF_SIZE];

volatile uint8_t low_stat = 0;
volatile uint8_t high_stat = 0;

//BIBLIOTEKA MPR121 JEST INICJALIZOWANA TYLKO DLA 4 PRZYCISKOW!!! plik.c
int main(void) {
	i2cSetBitrate(100);
	MPR121_init();
	led_init();
	//inicjalizacja nRFa
	nRF_init();
	program_timer_init();

	prog_timer1 = DEBOUNCE_DELAY1;
	prog_timer2 = DEBOUNCE_DELAY2;
	prog_timer3 = DEBOUNCE_DELAY3;
	prog_timer4 = DEBOUNCE_DELAY4;

	// zezwolenie na przerwania
	sei();

	while (1) {
		// odczyt stanu przyciskow
		low_stat = MPR121_read(ELE_L);
		high_stat = MPR121_read(ELE_H);

		// brak akcji
		//low byte
		if (!(low_stat & ELE0))
			LED1_OFF;
		else
			LED1_ON;
		if (!(low_stat & ELE1))
			LED2_OFF;
		else
			LED2_ON;
		if (!(low_stat & ELE2))
			LED3_OFF;
		else
			LED3_ON;
		if (!(low_stat & ELE3))
			LED4_OFF;
		else
			LED4_ON;
		if (!(low_stat & ELE4))
			LED5_OFF;
		else
			LED5_ON;
		if (!(low_stat & ELE5))
			LED6_OFF;
		else
			LED6_ON;
		if (!(low_stat & ELE6))
			LED7_OFF;
		else
			LED7_ON;
		if (!(low_stat & ELE7))
			LED8_OFF;
		else
			LED8_ON;
// high byte
		if (!(high_stat & ELE8))
			LED9_OFF;
		else
			LED9_ON;


		// obsluga przyciskow
		if (low_stat & ELE0) {
			transmit[0] = '1';
		} else {
			transmit[0] = '0';
		}

		if (low_stat & ELE1) {
			transmit[1] = '1';
		} else {
			transmit[1] = '0';
		}

		if (low_stat & ELE2) {
			transmit[2] = '1';
		} else {
			transmit[2] = '0';
		}

		if (low_stat & ELE3) {
			transmit[3] = '1';
		} else {
			transmit[3] = '0';
		}

		if (low_stat & ELE4) {
			transmit[4] = '1';
		} else {
			transmit[4] = '0';
		}

		if (low_stat & ELE5) {
			transmit[5] = '1';
		} else {
			transmit[5] = '0';
		}

		if (low_stat & ELE6) {
			transmit[6] = '1';
		} else {
			transmit[6] = '0';
		}

		if (low_stat & ELE7) {
			transmit[7] = '1';
		} else {
			transmit[7] = '0';
		}
		//high byte
		if (high_stat & ELE8) {
			transmit[8] = '1';
		} else {
			transmit[8] = '0';
		}

//		if ((low_stat & (ELE0 | ELE1 | ELE2 | ELE3 | ELE4 | ELE5 | ELE6 | ELE7)) || (high_stat & (ELE8))) {
//			LED_DEBUG_ON;
//			transmit[BUFF_SIZE - 1] = '\0';
//			nRF_SendDataToAir(transmit); // do dlugosci wlicza sie jeszcze '0' na koniec stringa
//			for (uint8_t i = 0; i < BUFF_SIZE - 1; i++) {
//				transmit[i] = 0;
//			}
//		}
//		else LED_DEBUG_OFF;

		if (low_stat & (ELE0 | ELE1 | ELE4 | ELE5)) {
			LED_DEBUG_ON;
			transmit[BUFF_SIZE - 1] = '\0';
			nRF_SendDataToAir(transmit); // do dlugosci wlicza sie jeszcze '0' na koniec stringa
			for (uint8_t i = 0; i < BUFF_SIZE - 1; i++) {
				transmit[i] = 0;
			}
		}
		else LED_DEBUG_OFF;
	};
}
