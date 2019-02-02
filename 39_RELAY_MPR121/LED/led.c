/*
 * led.c
 *
 *  Created on: 20 kwi 2017
 *      Author: Daniel
 */

#include <avr/io.h>

#include "led.h"

void led_init(void)
{
	// wyjscie
	LED1_DDR |= (1<<LED1);
	LED2_DDR |= (1<<LED2);
	LED3_DDR |= (1<<LED3);

	// zalaczamy jedynka - domyslnie OFF
	LED1_PORT &= ~(1<<LED1);
	LED2_PORT &= ~(1<<LED2);
	LED3_PORT &= ~(1<<LED3);
}

