/*
 * led.h
 *
 *  Created on: 20 kwi 2017
 *      Author: Daniel
 */

#ifndef LED_LED_H_
#define LED_LED_H_

#define LED1_PORT PORTD
#define LED2_PORT PORTD
#define LED3_PORT PORTD

#define LED1_DDR DDRD
#define LED2_DDR DDRD
#define LED3_DDR DDRD

#define LED1 PD5
#define LED2 PD6
#define LED3 PD7

#define LED1_ON LED1_PORT |= (1<<LED1)
#define LED2_ON LED2_PORT |= (1<<LED2)
#define LED3_ON LED3_PORT |= (1<<LED3)

#define LED1_OFF LED1_PORT &= ~(1<<LED1)
#define LED2_OFF LED2_PORT &= ~(1<<LED2)
#define LED3_OFF LED3_PORT &= ~(1<<LED3)

#define LED1_TOG LED1_PORT ^= (1<<LED1)
#define LED2_TOG LED2_PORT ^= (1<<LED2)
#define LED3_TOG LED3_PORT ^= (1<<LED3)

#endif /* LED_LED_H_ */
