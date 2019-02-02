#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include <util/delay.h>

#include "LCD/lcd44780.h"
#include "I2C_TWI/i2c_twi.h"
#include "MKUART/mkuart.h"
#include "TERM_VT100/term_vt100.h"

#include "BMP180/bmp180.h"
#include "HTU21/htu21.h"

void ShowOnLCD(void);				// Wswietla na LCD
void SendToUart(void);				// Wysy³a do RS

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
	USART_Init(__UBRR);				// inicjalizacja UART

	lcd_defchar_P(0x80, degree);	//za³adowanie do pamiêci wyœwietlacza znaku stopnia

	BMP180_init();					// inicjalizacja BMP180 - pobranie danych calibracyjnych
	HTU21_init();					// inicjalizacja HTU21 - soft reset

	while(1){
		bmp180_temp = BMP180_gett();
		bmp180_press = BMP180_getp();
		ShowOnLCD();
		SendToUart();

//		//ODCZYT TEMPERATURY
//        HTU21_read_temp(3,htu21_test);
//        htu21_t = ((uint8_t)htu21_test[0]<<8)|((uint8_t)htu21_test[1]>>2);
//
//        // Konwersja temperatury
//        htu21_temp=(175*((uint32_t)htu21_t*100000>>16));
//        htu21_temp=-46+(t/100000);

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
void SendToUart(void){
	//VT100 Sequences
	tr_cls(0);		// clear window, hide cursor
	tr_attr(0, BLUE, YELLOW);
	tr_locate(1, 0);
	uart_puts("             M E T E O             ");

	tr_attr(0, RED, BLACK);
	tr_locate(2, 7);
	//uart_puts("************** T ******************\r\n");
	uart_puts("Temperatura:");
	tr_locate(2, 20);
	uart_putint(bmp180_temp/10, 10 );
	uart_puts(".");
	uart_putint(bmp180_temp%10, 10 );
	uart_putc(0xb0);			// znak stopnia
	uart_putc('C');
	uart_puts(" \t");
	//uart_puts("************** P ******************\r\n");
	tr_attr(0, GREEN, BLACK);
	tr_locate(3,7);
	uart_puts("Cisnienie:");
	tr_locate(3, 20);
	uart_putint(bmp180_press/100, 10 );
	uart_puts(".");
	if (bmp180_press%100<10) uart_puts("0");
	uart_putint(bmp180_press%100, 10 );
	uart_puts("hPa");


	tr_attr(0, BLUE, BLACK);
	tr_locate(4,7);
	uart_puts("Wilgotnosc: ");
	tr_locate(4, 20);
	uart_putint(htu21_humid, 10);
	uart_putc(0x25);			// znak procenta
	tr_attr(0, BLUE, YELLOW);
	tr_locate(5, 0);
	uart_puts("                                   ");
	uart_puts("\r\n");

	tr_create_win();
}
