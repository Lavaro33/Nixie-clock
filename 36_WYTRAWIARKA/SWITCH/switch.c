/*
 * switch.c
 *
 *  Created on: 29 sie 2016
 *      Author: Daniel
 */

#include <avr/io.h>
#include <avr/interrupt.h>

#include "switch.h"

void switch_init(void)
{
	SW_PORT |= (SW_MENU | SW_SUB | SW_UP | SW_DOWN);	// pullup
	SW_DDR &= ~(SW_MENU | SW_SUB | SW_UP | SW_DOWN);	// kierunek wejœciowy
}


