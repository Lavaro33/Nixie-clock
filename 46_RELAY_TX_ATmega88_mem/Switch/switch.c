/*
 * switch.c
 *
 *  Created on: 16 paü 2017
 *      Author: Daniel
 */

#include <avr/io.h>
#include <util/delay.h>

#include "switch.h"

void sw_init(void){
	SW1_DDR &= ~SW1;
	SW2_DDR &= ~SW2;
	SW3_DDR &= ~SW3;
	SW4_DDR &= ~SW4;
	SW5_DDR &= ~SW5;
	SW6_DDR &= ~SW6;
	SW7_DDR &= ~SW7;
	SW8_DDR &= ~SW8;
	SW9_DDR &= ~SW9;
	SW10_DDR &= ~SW10;
	SW11_DDR &= ~SW11;

	SW1_PORT |= SW1;
	SW2_PORT |= SW2;
	SW3_PORT |= SW3;
	SW4_PORT |= SW4;
	SW5_PORT |= SW5;
	SW6_PORT |= SW6;
	SW7_PORT |= SW7;
	SW8_PORT |= SW8;
	SW9_PORT |= SW9;
	SW10_PORT |= SW10;
	SW11_PORT |= SW11;
}
