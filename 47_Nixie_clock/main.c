/*
 * main.c
 *
 *  Created on: 29 sie 2018
 *      Author: Daniel
 */

#include <avr/io.h>			// obs�uga port�w wej�cia/wyj�cia
#include <util/delay.h>		// obs�uga op�nie�
#include <avr/interrupt.h>	// obs�uga przerwa�

#include "LAMP/lamp.h"
#include "I2C_TWI/i2c_twi.h"
#include "DEBOUNCE/debounce.h"
#include "RTC/rtc.h"

int main(void) {

	rtc_isr_init();			// inicjalizacja przerwania zewnetrznego INT0 (co 1s)
	lamp_disp_init();		// inicjalizacja portow i kierunkow lamp
	sw_init();				// inicjalizacja przyciskow
	i2cSetBitrate( 100 ); 	// ustawiamy pr�dko�� 100 kHz na magistrali I2C
	program_timer_init();	// inicjalizacja timerow programowych na potrzeby debounce


	sei();			// w��czenie globalnego zezwolenia na przerwania

//		bufor[0] = 0;			// setne cz�ci sekundy
//		bufor[1] = dec2bcd(0);	// sekundy
//		bufor[2] = dec2bcd(46);	// minuty
//		bufor[3] = dec2bcd(19);	// godziny
//		// zapis 4 bajt�w z bufora pod adres 0x01 w pami�ci RAM naszego RTC
//		TWI_write_buf( PCF8583_ADDR, 0x01, 4, bufor );
	// cos tamttasdasht
	while (1) {
		digit1 = (godz > 9)? godz/10 : 0;
		digit2 = godz%10;
		digit3 = min/10;
		digit4 = min%10;

		SuperDebounce(&SW_PIN, SW1, 10, 100, inc_godz, inc_godz);
		SuperDebounce(&SW_PIN, SW2, 10, 100, inc_min, inc_min);


		if ( int0_flag ) {
			//odczyt 4 bajt�w do bufora od adresu 0x01 z pami�ci RAM naszego RTC
			TWI_read_buf( PCF8583_ADDR, 0x01, 4, bufor );

			sek = bcd2dec( bufor[ss] );
			min = bcd2dec( bufor[mm] );
			godz = bcd2dec( bufor[hh] );

			CLN_TOG;
			int0_flag=0;
		}
	}
}



