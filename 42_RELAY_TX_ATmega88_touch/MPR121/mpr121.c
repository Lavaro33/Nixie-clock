/*
 * mpr121.c
 *
 *  Created on: 18 kwi 2017
 *      Author: Daniel
 */

#include "../I2C_TWI/i2c_twi.h"
#include "mpr121.h"

void MPR121_init(void) {
	MPR121_write(GPIO_CTRL0, 0x00);
	MPR121_write(GPIO_CTRL1, 0x00);
	MPR121_write(GPIO_DIR, 0x00);
	MPR121_write(GPIO_EN, 0x00);
	MPR121_write(MHD_R, 0x01);
	MPR121_write(NHD_R, 0x01);
	MPR121_write(NCL_R, 0x00);
	MPR121_write(FDL_R, 0x00);
	MPR121_write(MHD_F, 0x01);
	MPR121_write(NHD_F, 0x01);
	MPR121_write(NCL_F, 0x7F);
	MPR121_write(FDL_F, 0x09);
	MPR121_write(ELE0_T, TOU_THRESH);
	MPR121_write(ELE0_R, REL_THRESH);
	MPR121_write(ELE1_T, TOU_THRESH);
	MPR121_write(ELE1_R, REL_THRESH);
	MPR121_write(ELE2_T, TOU_THRESH);
	MPR121_write(ELE2_R, REL_THRESH);
	MPR121_write(ELE3_T, TOU_THRESH);
	MPR121_write(ELE3_R, REL_THRESH);
	MPR121_write(ELE4_T, TOU_THRESH);
	MPR121_write(ELE4_R, REL_THRESH);
	MPR121_write(ELE5_T, TOU_THRESH);
	MPR121_write(ELE5_R, REL_THRESH);
	MPR121_write(ELE6_T, TOU_THRESH);
	MPR121_write(ELE6_R, REL_THRESH);
	MPR121_write(ELE7_T, TOU_THRESH);
	MPR121_write(ELE7_R, REL_THRESH);
	MPR121_write(ELE8_T, TOU_THRESH);
	MPR121_write(ELE8_R, REL_THRESH);

	MPR121_write(AUTO_CFG0, 0x1B);
	MPR121_write(AUTO_CFGU, 201);		//C9
	MPR121_write(AUTO_CFGT, 161);		//B5
	MPR121_write(AUTO_CFGL, 130);		//82

	MPR121_write(ELE_CFG, 0x89);	// odblokowanie elektrod (0-8)!!!
}

unsigned char MPR121_read(unsigned char addr) {
	unsigned char value = 0;

	TWI_start();
	TWI_write(Write_MPR121_addr);
	TWI_write(addr);
	TWI_start();
	TWI_write(Read_MPR121_addr);
	value = TWI_read(0);
	TWI_stop();

	return value;
}

void MPR121_write(unsigned char addr, unsigned char value) {
	TWI_start();
	TWI_write(Write_MPR121_addr);
	TWI_write(addr);
	TWI_write(value);
	TWI_stop();
}
