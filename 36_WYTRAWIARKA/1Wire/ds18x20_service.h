/*
 * ds18x20_service.h
 *
 *  Created on: 1 wrz 2016
 *      Author: Daniel
 */

#ifndef DS18X20_SERVICE_H_
#define DS18X20_SERVICE_H_

typedef struct
{
	uint8_t subzero;
	uint8_t cel;
	uint8_t cel_fract_bits;
}temp;

void ds18x20_timer_init();
temp ds18x20_get_temp();

#endif /* DS18X20_SERVICE_H_ */
