/*
 * HTU21.c
 *
 *  Created on: 4 lis 2015
 *      Author: Daniel
 */

#include <avr/io.h>
#include <util/delay.h>

#include"../I2C_TWI/i2c_twi.h"

void HTU21_init(){
    TWI_start();
    TWI_write(0x80);	//WRITE htu21 address
    TWI_write(0xFE);	//soft reset
    TWI_stop();
}

void HTU21_read_temp(uint8_t len, uint8_t *buf) {

	TWI_start();
    TWI_write(0x80);		//WRITE htu21 address
    TWI_write(0xE3);		//hold master mode
    TWI_stop();
    TWI_start();
    TWI_write(0x81);		//READ htu21 address
    _delay_ms(55);
    while (len--) *buf++ = TWI_read( len ? ACK : NACK );
    TWI_stop();
}

void HTU21_read_humid(uint8_t len, uint8_t *buf) {

	TWI_start();
    TWI_write(0x80);		//WRITE htu21 address
    TWI_write(0xE5);		//hold master mode
    TWI_stop();
    TWI_start();
    TWI_write(0x81);		//READ htu21 address
    _delay_ms(55);
    while (len--) *buf++ = TWI_read( len ? ACK : NACK );
    TWI_stop();
}

