/*
 * debounce.h
 *
 *  Created on: 20 sie 2015
 *      Author: Daniel
 */

#ifndef DEBOUNCE_DEBOUNCE_H_
#define DEBOUNCE_DEBOUNCE_H_

extern volatile uint16_t timer_debounce, timer_ds18x20, timer_etching, timer_blink_on, timer_blink_off;		// timery programowe - przerwanie co 10ms (100Hz)

void program_timer_init(void);

// obsluga przyciskow z mozliwoscia innej funkcji przy przytrzymaniu
void SuperDebounce(volatile uint8_t *KPIN, uint8_t key_mask, uint16_t rep_time, uint16_t rep_wait,
		void (*push_proc)(void), void (*rep_proc)(void));

#endif /* DEBOUNCE_DEBOUNCE_H_ */
