/*
 * i2c_twi.h
 *
 *  Created on: 2010-09-07
 *       Autor: Miros³aw Kardaœ
 */

#ifndef I2C_TWI_H_
#define I2C_TWI_H_

#define ACK 1
#define NACK 0

// ustawiamy prêdkoœæ na I2C w kHz (standardowa prêdkoœæ to 100 kHz)
void i2cSetBitrate(uint16_t bitrateKHz);


void TWI_start(void);			// uruchomienie magistrali I2C
void TWI_stop(void);			// zatrzymanie magistrali I2C
void TWI_write(uint8_t bajt);	// wys³anie bajtu na magistralê I2C
uint8_t TWI_read(uint8_t ack);	// odebranie danych z magistrali I2C

void TWI_write_buf( uint8_t SLA, uint8_t adr, uint8_t len, uint8_t *buf );	// SLA adres slave do zapisu, adr - pocz¹tkowy adres do zapisu,
//len - liczba bajtów do zapisu, buf - bufor, z którego bêd¹ odczytywane bajty do zapisu
void TWI_read_buf(uint8_t SLA, uint8_t adr, uint8_t len, uint8_t *buf);		// SLA adres slave do odczytu, adr - pocz¹tkowy adres do odczytu,
//len - liczba bajtów do odczytu, buf - bufor, do którego bêd¹ zapisywane odczytane bajty

#endif /* I2C_TWI_H_ */
