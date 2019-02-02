/*
 * rtc.c
 *
 *  Created on: 14 sty 2019
 *      Author: Daniel
 */
#include <avr/io.h>
#include <avr/interrupt.h>

#include "../LAMP/lamp.h"
#include "../I2C_TWI/i2c_twi.h"
#include "rtc.h"

void rtc_isr_init(){
	// Przerwanie INT0
	MCUCR |= (1<<ISC01)|(1<<ISC00);	// wyzwalanie zboczem opadaj¹cym
	GICR |= (1<<INT0);		// odblokowanie przerwania
	PORTD |= (1<<PD2);		// podci¹gniêcie pinu INT0 do VCC
}

// procedura obs³ugi przerwania INT 0
ISR( INT0_vect ) {
	int0_flag = 1;
}


// konwersja liczby dziesiêtnej na BCD
uint8_t dec2bcd(uint8_t dec) {
return ((dec / 10)<<4) | (dec % 10);
}

// konwersja liczby BCD na dziesiêtn¹
uint8_t bcd2dec(uint8_t bcd) {
    return ((((bcd) >> 4) & 0x0F) * 10) + ((bcd) & 0x0F);
}

void inc_godz(void)
{
	sek = bcd2dec( bufor[ss] );
	min = bcd2dec( bufor[mm] );
	godz = bcd2dec( bufor[hh] );

	godz = (godz < 23)? godz+1 : 0;

	bufor[0] = 0;			// setne czêœci sekundy
	bufor[1] = dec2bcd(0);	// sekundy
	bufor[2] = dec2bcd(min);	// minuty
	bufor[3] = dec2bcd(godz);	// godziny
	// zapis 4 bajtów z bufora pod adres 0x01 w pamiêci RAM naszego RTC
	TWI_write_buf( PCF8583_ADDR, 0x01, 4, bufor );
}

void inc_min(void)
{
	sek = bcd2dec( bufor[ss] );
	min = bcd2dec( bufor[mm] );
	godz = bcd2dec( bufor[hh] );

	min = (min < 59)? min+1 : 0;

	bufor[0] = 0;			// setne czêœci sekundy
	bufor[1] = dec2bcd(0);	// sekundy
	bufor[2] = dec2bcd(min);	// minuty
	bufor[3] = dec2bcd(godz);	// godziny
	// zapis 4 bajtów z bufora pod adres 0x01 w pamiêci RAM naszego RTC
	TWI_write_buf( PCF8583_ADDR, 0x01, 4, bufor );
}
