/*
 * i2c_twi.h
 *
 *  Created on: 2010-09-07
 *       Autor: Miros�aw Karda�
 */

#ifndef I2C_TWI_H_
#define I2C_TWI_H_

#define ACK 1
#define NACK 0

// ustawiamy pr�dko�� na I2C w kHz (standardowa pr�dko�� to 100 kHz)
void i2cSetBitrate(uint16_t bitrateKHz);


void TWI_start(void);			// uruchomienie magistrali I2C
void TWI_stop(void);			// zatrzymanie magistrali I2C
void TWI_write(uint8_t bajt);	// wys�anie bajtu na magistral� I2C
uint8_t TWI_read(uint8_t ack);	// odebranie danych z magistrali I2C

void TWI_write_buf( uint8_t SLA, uint8_t adr, uint8_t len, uint8_t *buf );	// SLA adres slave do zapisu, adr - pocz�tkowy adres do zapisu,
//len - liczba bajt�w do zapisu, buf - bufor, z kt�rego b�d� odczytywane bajty do zapisu
void TWI_read_buf(uint8_t SLA, uint8_t adr, uint8_t len, uint8_t *buf);		// SLA adres slave do odczytu, adr - pocz�tkowy adres do odczytu,
//len - liczba bajt�w do odczytu, buf - bufor, do kt�rego b�d� zapisywane odczytane bajty

#endif /* I2C_TWI_H_ */
