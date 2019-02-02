/*
 * rtc.h
 *
 *  Created on: 14 sty 2019
 *      Author: Daniel
 */

#ifndef RTC_RTC_H_
#define RTC_RTC_H_

// **** UWAGA - wybierz w³aciwy adres jak ni¿ej **************
//#define PCF8583_ADDR 0xA0		// gdy A1 --> GND
#define PCF8583_ADDR 0xA2		// gdy A1 --> VCC

uint8_t godz;
uint8_t min;
uint8_t sek;

void inc_godz();
void inc_min();

void rtc_isr_init();

volatile uint8_t int0_flag;	// flaga zmieniana w przerwaniu i sprawdzana w pêtli g³ównej

enum {ss=1, mm, hh};
uint8_t bufor[4];		// rezerwacja bufora 4 bajty


// konwersja liczby dziesiêtnej na BCD
uint8_t dec2bcd(uint8_t dec);
// konwersja liczby BCD na dziesiêtn¹
uint8_t bcd2dec(uint8_t bcd);

#endif /* RTC_RTC_H_ */
