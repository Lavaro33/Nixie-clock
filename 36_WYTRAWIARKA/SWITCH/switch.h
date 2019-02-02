/*
 * switch.h
 *
 *  Created on: 29 sie 2016
 *      Author: Daniel
 */

#ifndef SWITCH_SWITCH_H_
#define SWITCH_SWITCH_H_

#define SW_MENU (1<<PC0)
#define SW_SUB (1<<PC1)
#define SW_UP (1<<PC2)
#define SW_DOWN (1<<PC3)

#define SW_PORT PORTC
#define SW_DDR DDRC
#define SW_PIN PINC

extern void switch_init(void);

#endif /* SWITCH_SWITCH_H_ */
