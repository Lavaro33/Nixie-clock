#include <avr/io.h>			// obs³uga portów wejœcia/wyjœcia
#include <util/delay.h>		// obs³uga opóŸnieñ
#include <avr/interrupt.h>	// obs³uga przerwañ
#include <stdlib.h>			// do funkcji itoa
#include <avr/pgmspace.h>	// obs³uga pamiêci flash

#include "LCD/lcd44780.h"
#include "I2C_TWI/i2c_twi.h"
#include "BMP180/bmp180.h"
#include "HTU21/htu21.h"
#include "nRF24L01/nRF24L01.h"

// Odbiór danych ze stacji zew. i wyœwietlenie
void receive_and_display();

// wzór znaku termometru w pamiêci FLASH
const uint8_t degree[] PROGMEM = {14,17,17,17,14,32,32,32};

int main (void)
{
	lcd_init();						// inicjalizacja LCD
	lcd_defchar_P(0x80, degree);	// za³adowanie do pamiêci wyœwietlacza znaku stopnia
	i2cSetBitrate(100);				// inicjalizacja I2C
    nRF_init();						// inicjalizacja nRF

    //inicjalizacja przerwania co 10ms
    TCCR0A |= (1<<WGM01);				// tryb CTC
    TCCR0B |= (1<<CS02) | (1<<CS01);		// preskaler 1024
    TIMSK0 |= (1<<OCIE0A);
   	OCR0A = 107;							//11059200/1024/107 = 100Hz(10ms)

    // globalne zezwolenie na przerwania
    sei();

    nRF_RX_Power_Up(); // w³¹czenie modu³u nRF w trybie odbiorczym

	while(1)
	{

		nRF_RX_EVENT();

		receive_and_display();
		_delay_ms(1000);
	}
}
///////////////////////////////////////////////////////////

ISR(TIMER0_COMPA_vect)
{
	uint16_t x;
	x = prog_timer1;
	if(x) prog_timer1 = --x;
}

void receive_and_display()
{

	lcd_cls();
	uint8_t data[13] = {0};
	uint8_t i;
	for(i=0; i<13; i++)
		{
		data[i] = nRF_RX_bufffer[i];
		}

	//wyswietlenie temperatury
	lcd_locate(0, 0);
	lcd_char(data[0]);
	lcd_char(data[1]);
	lcd_char('.');
	lcd_char(data[2]);
	lcd_char('\x80');
	lcd_char('C');

	lcd_locate(0, 11);
	lcd_char(data[9]);
	lcd_char(data[10]);
	lcd_str("%RH");

	lcd_locate(1,3);
	lcd_char(data[3]);
	lcd_char(data[4]);
	lcd_char(data[5]);
	lcd_char(data[6]);
	lcd_char('.');
	lcd_char(data[7]);
	lcd_char(data[8]);
	lcd_str("hPa");
}

//void ShowOnLCD(void){
//	lcd_cls();
//	lcd_locate(0,0);
//	lcd_str("T: ");
//	lcd_int(bmp180_temp/10);
//	lcd_str(".");
//	if(bmp180_temp > 0)
//		lcd_int(bmp180_temp%10);
//	else
//		lcd_int((bmp180_temp%10)*-1);
//	lcd_str("\x80");			// w³asny znak - stopien
//	lcd_str("C");
//	lcd_locate(1,0);
//	lcd_str("C: ");
//	lcd_int(bmp180_press/100);
//	lcd_str(".");
//	if (bmp180_press%100<10) lcd_str("0");
//	lcd_int(bmp180_press%100);
//	lcd_str("hPa");
//
//	lcd_locate(0, 10);
//	lcd_str("W: ");
//	lcd_int(htu21_humid);
//	lcd_str("%");
//}
