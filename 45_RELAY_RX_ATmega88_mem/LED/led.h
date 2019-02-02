/*
 * led.h
 *
 *  Created on: 1 kwi 2017
 *      Author: ThinkPad
 */

#ifndef LED_LED_H_
#define LED_LED_H_

void led_init(void);

#define LED1 (1<<PB0)
#define LED2 (1<<PD7)
#define LED3 (1<<PD6)
#define LED4 (1<<PD5)
#define LED5 (1<<PB7)
#define LED6 (1<<PB6)
#define LED7 (1<<PD4)
#define LED8 (1<<PD3)
#define LED9 (1<<PD1)
#define LED10 (1<<PD0)
#define LED_DEBUG (1<<PC0)		//dioda do transmisji

#define LED1_PORT PORTB
#define LED2_PORT PORTD
#define LED3_PORT PORTD
#define LED4_PORT PORTD
#define LED5_PORT PORTB
#define LED6_PORT PORTB
#define LED7_PORT PORTD
#define LED8_PORT PORTD
#define LED9_PORT PORTD
#define LED10_PORT PORTD
#define LED_DEBUG_PORT PORTC

#define LED1_DDR DDRB
#define LED2_DDR DDRD
#define LED3_DDR DDRD
#define LED4_DDR DDRD
#define LED5_DDR DDRB
#define LED6_DDR DDRB
#define LED7_DDR DDRD
#define LED8_DDR DDRD
#define LED9_DDR DDRD
#define LED10_DDR DDRD
#define LED_DEBUG_DDR DDRC

#define LED1_ON LED1_PORT |= LED1
#define LED2_ON LED2_PORT |= LED2
#define LED3_ON LED3_PORT |= LED3
#define LED4_ON LED4_PORT |= LED4
#define LED5_ON LED5_PORT |= LED5
#define LED6_ON LED6_PORT |= LED6
#define LED7_ON LED7_PORT |= LED7
#define LED8_ON LED8_PORT |= LED8
#define LED9_ON LED9_PORT |= LED9
#define LED10_ON LED10_PORT |= LED10
#define LED_DEBUG_ON LED_DEBUG_PORT |= LED_DEBUG

#define LED1_OFF LED1_PORT &= ~LED1
#define LED2_OFF LED2_PORT &= ~LED2
#define LED3_OFF LED3_PORT &= ~LED3
#define LED4_OFF LED4_PORT &= ~LED4
#define LED5_OFF LED5_PORT &= ~LED5
#define LED6_OFF LED6_PORT &= ~LED6
#define LED7_OFF LED7_PORT &= ~LED7
#define LED8_OFF LED8_PORT &= ~LED8
#define LED9_OFF LED9_PORT &= ~LED9
#define LED10_OFF LED10_PORT &= ~LED10
#define LED_DEBUG_OFF LED_DEBUG_PORT &= ~LED_DEBUG

#define LED1_TOG LED1_PORT ^= LED1
#define LED2_TOG LED2_PORT ^= LED2
#define LED3_TOG LED3_PORT ^= LED3
#define LED4_TOG LED4_PORT ^= LED4
#define LED5_TOG LED5_PORT ^= LED5
#define LED6_TOG LED6_PORT ^= LED6
#define LED7_TOG LED7_PORT ^= LED7
#define LED8_TOG LED8_PORT ^= LED8
#define LED9_TOG LED9_PORT ^= LED9
#define LED10_TOG LED10_PORT ^= LED10
#define LED_DEBUG_TOG LED_DEBUG_PORT ^= LED_DEBUG


#endif /* LED_LED_H_ */
