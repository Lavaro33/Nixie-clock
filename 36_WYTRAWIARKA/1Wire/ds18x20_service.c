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

uint8_t czujniki_cnt;		/* iloœæ czujników na magistrali */
volatile uint8_t sek_flag;	/* flaga tykniêcia timera co 1 sekundê */
volatile uint8_t sekundy;	/* licznik sekund 0-59 */

void ds18x20_timer_init()
{
	timer_ds18x20 = 75;
	/* ustawienie TIMER0 dla F_CPU=11,059200MHz */
	TCCR0 |= (1<<WGM01);				/* tryb CTC */
	TCCR0 |= (1<<CS02)|(1<<CS00);		/* preskaler = 1024 */
	OCR0 = 108;							/* dodatkowy podzia³ przez 78 (rej. przepe³nienia) */
	TIMSK |= (1<<OCIE0);				/* zezwolenie na przerwanie CompareMatch */
	/* przerwanie wykonywane z czêstotliwoœci¹ ok 10ms (100 razy na sekundê) */
}

temp ds18x20_get_temp()
{
	temp t_result;

	/* sprawdzamy ile czujników DS18xxx widocznych jest na magistrali */
	czujniki_cnt = search_sensors();

	/* wysy³amy rozkaz wykonania pomiaru temperatury
	 * do wszystkich czujników na magistrali 1Wire
	 * zak³adaj¹c, ¿e zasilane s¹ w trybie NORMAL,
	 * gdyby by³ to tryb Parasite, nale¿a³oby u¿yæ
	 * jako pierwszego prarametru DS18X20_POWER_PARASITE */
	DS18X20_start_meas( DS18X20_POWER_EXTERN, NULL );

	if(!timer_ds18x20)
	{
		/* dokonujemy odczytu temperatury z pierwszego czujnika o ile zosta³ wykryty */
		/* wyœwietlamy temperaturê gdy czujnik wykryty */
		if( DS18X20_OK == DS18X20_read_meas(gSensorIDs[0], &t_result.subzero, &t_result.cel, &t_result.cel_fract_bits)) return t_result;
		timer_ds18x20 = 75;
	}

	if(sek_flag) {	/* sprawdzanie flagi tykniêæ timera programowego co 1 sekundê */

		/* co dwie sekundy gdy reszta z dzielenia modulo 2 == 0 wysy³aj rozkaz pomiaru do czujników */
		if( 0 == (sekundy%2) ) DS18X20_start_meas( DS18X20_POWER_EXTERN, NULL );

		/* co dwie sekundy gdy reszta z dzielenia modulo 3 == 2 czyli jedn¹ sekundê po rozkazie konwersji
		 *  dokonuj odczytu i wyœwietlania temperatur z 2 czujników jeœli s¹ pod³¹czone, jeœli nie
		 *  to poka¿ komunikat o b³êdzie
		 */
		if( 1 == (sekundy%2) ) {
			if( DS18X20_OK == DS18X20_read_meas(gSensorIDs[0], &t_result.subzero, &t_result.cel, &t_result.cel_fract_bits)) return t_result;
		}

		/* zerujemy flagê aby tylko jeden raz w ci¹gu sekundy wykonaæ operacje */
		sek_flag=0;
	}
	return t_result;
}

/* pe³ni funkcjê timera programowego wyznaczaj¹cego podstawê czasu = 1s */
ISR(TIMER0_COMP_vect)
{
	static uint8_t cnt=0;

	if(++cnt>99) {	/* gdy licznik ms > 99 (minê³a 1 sekunda) */
		sek_flag=1;
		sekundy++;
		if(sekundy>59) sekundy=0;
		cnt=0;
	}
}
