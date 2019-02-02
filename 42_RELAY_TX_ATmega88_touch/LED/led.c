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
	LED1_DDR |= LED1;
	LED2_DDR |= LED2;
	LED3_DDR |= LED3;
	LED4_DDR |= LED4;
	LED5_DDR |= LED5;
	LED6_DDR |= LED6;
	LED7_DDR |= LED7;
	LED8_DDR |= LED8;
	LED9_DDR |= LED9;
	LED_DEBUG_DDR |= LED_DEBUG;

	LED1_OFF;
	LED2_OFF;
	LED3_OFF;
	LED4_OFF;
	LED5_OFF;
	LED6_OFF;
	LED7_OFF;
	LED8_OFF;
	LED9_OFF;
	LED_DEBUG_OFF;
}

