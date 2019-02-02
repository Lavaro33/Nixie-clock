/*
 * switch.h
 *
 *  Created on: 16 paü 2017
 *      Author: Daniel
 */

#ifndef SWITCH_SWITCH_H_
#define SWITCH_SWITCH_H_

#define SW1 (1<<PB0)
#define SW2 (1<<PD7)
#define SW3 (1<<PD6)
#define SW4 (1<<PD5)
#define SW5 (1<<PB7)
#define SW6 (1<<PC0)
#define SW7 (1<<PC1)
#define SW8 (1<<PC2)
#define SW9 (1<<PC3)
#define SW10 (1<<PC4)
#define SW11 (1<<PC5)

#define SW1_DDR DDRB
#define SW2_DDR DDRD
#define SW3_DDR DDRD
#define SW4_DDR DDRD
#define SW5_DDR DDRB
#define SW6_DDR DDRC
#define SW7_DDR DDRC
#define SW8_DDR DDRC
#define SW9_DDR DDRC
#define SW10_DDR DDRC
#define SW11_DDR DDRC

#define SW1_PORT PORTB
#define SW2_PORT PORTD
#define SW3_PORT PORTD
#define SW4_PORT PORTD
#define SW5_PORT PORTB
#define SW6_PORT PORTC
#define SW7_PORT PORTC
#define SW8_PORT PORTC
#define SW9_PORT PORTC
#define SW10_PORT PORTC
#define SW11_PORT PORTC

#define SW1_PIN PINB
#define SW2_PIN PIND
#define SW3_PIN PIND
#define SW4_PIN PIND
#define SW5_PIN PINB
#define SW6_PIN PINC
#define SW7_PIN PINC
#define SW8_PIN PINC
#define SW9_PIN PINC
#define SW10_PIN PINC
#define SW11_PIN PINC

void sw_init(void);


#endif /* SWITCH_SWITCH_H_ */
