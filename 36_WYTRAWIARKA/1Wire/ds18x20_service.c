/*
 * ds18x20_service.c
 *
 *  Created on: 1 wrz 2016
 *      Author: Daniel
 */

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <avr/pgmspace.h>
#include <avr/eeprom.h>

#include "ds18x20.h"
#include "../DEBOUNCE/debounce.h"
#include "ds18x20_service.h"

uint8_t czujniki_cnt;		/* ilo�� czujnik�w na magistrali */
volatile uint8_t sek_flag;	/* flaga tykni�cia timera co 1 sekund� */
volatile uint8_t sekundy;	/* licznik sekund 0-59 */

void ds18x20_timer_init()
{
	timer_ds18x20 = 75;
	/* ustawienie TIMER0 dla F_CPU=11,059200MHz */
	TCCR0 |= (1<<WGM01);				/* tryb CTC */
	TCCR0 |= (1<<CS02)|(1<<CS00);		/* preskaler = 1024 */
	OCR0 = 108;							/* dodatkowy podzia� przez 78 (rej. przepe�nienia) */
	TIMSK |= (1<<OCIE0);				/* zezwolenie na przerwanie CompareMatch */
	/* przerwanie wykonywane z cz�stotliwo�ci� ok 10ms (100 razy na sekund�) */
}

temp ds18x20_get_temp()
{
	temp t_result;

	/* sprawdzamy ile czujnik�w DS18xxx widocznych jest na magistrali */
	czujniki_cnt = search_sensors();

	/* wysy�amy rozkaz wykonania pomiaru temperatury
	 * do wszystkich czujnik�w na magistrali 1Wire
	 * zak�adaj�c, �e zasilane s� w trybie NORMAL,
	 * gdyby by� to tryb Parasite, nale�a�oby u�y�
	 * jako pierwszego prarametru DS18X20_POWER_PARASITE */
	DS18X20_start_meas( DS18X20_POWER_EXTERN, NULL );

	if(!timer_ds18x20)
	{
		/* dokonujemy odczytu temperatury z pierwszego czujnika o ile zosta� wykryty */
		/* wy�wietlamy temperatur� gdy czujnik wykryty */
		if( DS18X20_OK == DS18X20_read_meas(gSensorIDs[0], &t_result.subzero, &t_result.cel, &t_result.cel_fract_bits)) return t_result;
		timer_ds18x20 = 75;
	}

	if(sek_flag) {	/* sprawdzanie flagi tykni�� timera programowego co 1 sekund� */

		/* co dwie sekundy gdy reszta z dzielenia modulo 2 == 0 wysy�aj rozkaz pomiaru do czujnik�w */
		if( 0 == (sekundy%2) ) DS18X20_start_meas( DS18X20_POWER_EXTERN, NULL );

		/* co dwie sekundy gdy reszta z dzielenia modulo 3 == 2 czyli jedn� sekund� po rozkazie konwersji
		 *  dokonuj odczytu i wy�wietlania temperatur z 2 czujnik�w je�li s� pod��czone, je�li nie
		 *  to poka� komunikat o b��dzie
		 */
		if( 1 == (sekundy%2) ) {
			if( DS18X20_OK == DS18X20_read_meas(gSensorIDs[0], &t_result.subzero, &t_result.cel, &t_result.cel_fract_bits)) return t_result;
		}

		/* zerujemy flag� aby tylko jeden raz w ci�gu sekundy wykona� operacje */
		sek_flag=0;
	}
	return t_result;
}

/* pe�ni funkcj� timera programowego wyznaczaj�cego podstaw� czasu = 1s */
ISR(TIMER0_COMP_vect)
{
	static uint8_t cnt=0;

	if(++cnt>99) {	/* gdy licznik ms > 99 (min�a 1 sekunda) */
		sek_flag=1;
		sekundy++;
		if(sekundy>59) sekundy=0;
		cnt=0;
	}
}
