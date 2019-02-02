/*                  e-gadget.header
 * main.c
 *
 *  Created on: 2015-04-07
 *    Modyfied: 2015-04-07 19:45:16
 *      Author: Nefarious19
 *
 * Project name: "NRF24"
 *
 *
 *          MCU: ATmega32
 *        F_CPU: 16 000 000 Hz
 *
 *    Flash: 2 992 bytes   [ 9,1 % ]
 *      RAM:  189 bytes   [ 9,2 % ]
 *   EEPROM:  0 bytes   [ 0,0 % ]
 *
 */


#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdlib.h>
#include <string.h>
#include <avr/pgmspace.h>

#include "nRF24L01.h"

#include "I2C_TWI/i2c_twi.h"
#include "LCD/lcd44780.h"
#include "BMP180/bmp180.h"
#include "HTU21/htu21.h"

// Zmienne dla czujnika BMP180
int32_t bmp180_temp, bmp180_press;
const uint8_t degree[] PROGMEM = {14,17,17,17,14,32,32,32};	// wzór znaku termometru w pamiêci FLASH
void ShowOnLCD(void);				// Wswietla na LCD temp/wilg


// Zmienne na potrzeby czujnika HTU21
uint8_t htu21_test[3];					// Tablica na odebrane 3 bajty temperatury/wigotnosci

//uint16_t htu21_t;						// Temperatura odczytana
//int32_t htu21_temp;						// Temperatura po konwersji

uint16_t htu21_h;						// Wilgotnosc odczytana
uint32_t htu21_humid;					// Wilgotnosc po konwersji

int main (void)
{
	//lcd_init();
	//lcd_defchar_P(0x80, degree);	//za³adowanie do pamiêci wyœwietlacza znaku stopnia

	i2cSetBitrate(100);				// inicjalizacja I2C

	//inicjalizacja nRFa
    nRF_init();

	BMP180_init();					// inicjalizacja BMP180 - pobranie danych calibracyjnych
	HTU21_init();					// inicjalizacja HTU21 - soft reset

   	//zezwolenie na przerwania
    sei();

	while(1)
	{
		bmp180_temp = BMP180_gett();
		bmp180_press = BMP180_getp();

        //ODCZYT WILGOTNOŒCI
        HTU21_read_humid(3,htu21_test);
        htu21_h= ((uint8_t)htu21_test[0]<<8)|((uint8_t)htu21_test[1]>>2);

        // kowersja wilgotnosci
        htu21_humid = (uint32_t)htu21_h*125;
        htu21_humid >>= 16;
        htu21_humid -= 6;

		//ShowOnLCD();

        // tablica do przeslania
		char transmit[12];

    	uint16_t press_100 = bmp180_press/100;	//setki
    	uint16_t press_10 = bmp180_press%100;	//czesc po przecinku

//    	lcd_locate(0,0);
//    	lcd_int(bmp180_press/100);
//    	lcd_locate(1,0);
//    	lcd_int(bmp180_press%100);

    	int16_t temp = (int16_t) bmp180_temp;

    	itoa(temp, transmit, 10);

    	//		lcd_locate(0, 14);
    	//		lcd_int(sizeof(temp));

    	if((press_100/1000) == 1)
    	{
        	char p0[1];
        	itoa(press_100/1000, p0, 10);
        	transmit[3] = *p0;
    	}
    	else
    		transmit[3] = ' ';

//    	char p0[1];
//    	itoa(press_100/1000, p0, 10);
//    	transmit[3] = *p0;

    	char p1[1];
    	itoa((press_100/100)%10, p1, 10);
    	transmit[4] = *p1;

    	char p2[1];
    	itoa(((press_100/10)%10), p2, 10);
    	transmit[5] = *p2;

    	char p3[1];
    	itoa(press_100%10, p3, 10);
    	transmit[6] = *p3;


    	char p4[1];
    	itoa(press_10/10, p4, 10);
    	transmit[7] = *p4;

    	char p5[1];
    	itoa(press_10%10, p5, 10);
    	transmit[8] = *p5;

    	char p6[1];
    	itoa(htu21_humid/10, p6, 10);
    	transmit[9] = *p6;

    	char p7[1];
    	itoa(htu21_humid%10, p7, 10);
    	transmit[10] = *p7;

    	transmit[11] = '\0';
//
//    	//		lcd_locate(0, 14);
//    	//		lcd_int(sizeof(temp));


		nRF_SendDataToAir(transmit); // do dlugosci wlicza sie jeszcze '0' na koniec stringa
		_delay_ms(1000);
	}
}

void ShowOnLCD(void){
	lcd_locate(0,0);
	lcd_str("T: ");
	lcd_int(bmp180_temp/10);
	lcd_str(".");
	if(bmp180_temp > 0)
		lcd_int(bmp180_temp%10);
	else
		lcd_int((bmp180_temp%10)*-1);
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

