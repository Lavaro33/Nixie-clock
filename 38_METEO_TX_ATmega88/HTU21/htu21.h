/*
 * HTU21.h
 *
 *  Created on: 4 lis 2015
 *      Author: Daniel
 */

#ifndef HTU21_HTU21_H_
#define HTU21_HTU21_H_

void HTU21_init();

void HTU21_read_temp(uint8_t len, uint8_t *buf);
void HTU21_read_humid(uint8_t len, uint8_t *buf);

#endif /* HTU21_HTU21_H_ */
