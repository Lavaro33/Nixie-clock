/*
 * main.c
 *
 *  Created on: 7 gru 2015
 *      Author: Daniel Janczak
 */

#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include <util/delay.h>

#include "LCD/lcd44780.h"
#include "I2C_TWI/i2c_twi.h"

#include "BMP180/bmp180.h"
#include "HTU21/htu21.h"

void ShowOnLCD(void);				// Wswietla na LCD

// Zmienne dla czujnika BMP180
long bmp180_temp, bmp180_press;

// Zmienne na potrzeby czujnika HTU21
uint8_t htu21_test[3];					// Tablica na odebrane 3 bajty temperatury/wigotnosci

//uint16_t htu21_t;						// Temperatura odczytana
//int32_t htu21_temp;						// Temperatura po konwersji

uint16_t htu21_h;						// Wilgotnosc odczytana
uint32_t htu21_humid;					// Wilgotnosc po konwersji

const uint8_t degree[] PROGMEM = {14,17,17,17,14,32,32,32};	// wzór znaku termometru w pamiêci FLASH

int main(void) {

	_delay_ms(15);					// czas potrzebny na wyjœcie ze sleep mode HTU21
	lcd_init();
	lcd_cls();

	i2cSetBitrate(100);				// inicjalizacja I2C
	sei();							// globalne odblokowanie przerwañ

	lcd_defchar_P(0x80, degree);	//za³adowanie do pamiêci wyœwietlacza znaku stopnia

	BMP180_init();					// inicjalizacja BMP180 - pobranie danych calibracyjnych
	HTU21_init();					// inicjalizacja HTU21 - soft reset

	while(1){
		bmp180_temp = BMP180_gett();
		bmp180_press = BMP180_getp();
		ShowOnLCD();

        //ODCZYT WILGOTNOŒCI
        HTU21_read_humid(3,htu21_test);
        htu21_h= ((uint8_t)htu21_test[0]<<8)|((uint8_t)htu21_test[1]>>2);

        // kowersja wilgotnosci
        htu21_humid = (uint32_t)htu21_h*125;
        htu21_humid >>= 16;
        htu21_humid -= 6;

        _delay_ms(500);
	}
}

void ShowOnLCD(void){
	lcd_locate(0,0);
	lcd_str("T: ");
	lcd_int(bmp180_temp/10);
	lcd_str(".");
	lcd_int(bmp180_temp%10);
	lcd_str("\x80");					// w³asny znak - stopien
	lcd_str("C");
	lcd_locate(1,0);
	lcd_str("C: ");
	lcd_int(bmp180_press/100);
	lcd_str(".");
	if (bmp180_press%100<10) lcd_str("0");
	lcd_int(bmp180_press%100);
	lcd_str("hPa");

	lcd_locate(0, 10);
	lcd_str("W: ");
	lcd_int(htu21_humid);
	lcd_str("%");
}
