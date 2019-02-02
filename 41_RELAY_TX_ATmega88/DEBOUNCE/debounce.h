/*
 * debounce.h
 *
 *  Created on: 20 sie 2015
 *      Author: Daniel
 */

#ifndef DEBOUNCE_DEBOUNCE_H_
#define DEBOUNCE_DEBOUNCE_H_

extern volatile uint16_t timer_debounce;		// timery programowe - przerwanie co 10ms (100Hz)

void switch_init(void);					//inicjalizacja przyciskow
void program_timer_init(void);			//inicjalizacja timerow programowych

// obsluga przyciskow z mozliwoscia innej funkcji przy przytrzymaniu
void SuperDebounce(volatile uint8_t *KPIN, uint8_t key_mask, uint16_t rep_time, uint16_t rep_wait,
		void (*push_proc)(void), void (*rep_proc)(void));

#define SW1_PORT PORTC
#define SW1_DDR DDRC
#define SW1_PIN PINC

#define SW2_PORT PORTC
#define SW2_DDR DDRC
#define SW2_PIN PINC

#define SW3_PORT PORTC
#define SW3_DDR DDRC
#define SW3_PIN PINC

#define SW4_PORT PORTC
#define SW4_DDR DDRC
#define SW4_PIN PINC

#define SW5_PORT PORTC
#define SW5_DDR DDRC
#define SW5_PIN PINC

#define SW1 (1<<PC0)
#define SW2 (1<<PC1)
#define SW3 (1<<PC2)
#define SW4 (1<<PC3)
#define SW5 (1<<PC4)


#endif /* DEBOUNCE_DEBOUNCE_H_ */
