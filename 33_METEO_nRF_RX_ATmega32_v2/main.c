#include <avr/io.h>			// obs³uga portów wejœcia/wyjœcia
#include <util/delay.h>		// obs³uga opóŸnieñ
#include <avr/interrupt.h>	// obs³uga przerwañ
#include <stdlib.h>			// do funkcji itoa
#include <avr/pgmspace.h>	// obs³uga pamiêci flash

#include "MKUART/mkuart.h"
#include "LCD/lcd44780.h"
#include "I2C_TWI/i2c_twi.h"
#include "BMP180/bmp180.h"
#include "HTU21/htu21.h"
#include "nRF24L01/nRF24L01.h"

// Wys³anie danych przez UART
void transmit_uart ( void * nRF_RX_buff , uint8_t len );
// Odbiór danych ze stacji zew. i wyœwietlenie
void receive_and_display();
// Wyœwietla na LCD temp/wilg/cisn ze stacji g³ównej
void ShowOnLCD(void);

// Zmienne dla czujnika BMP180
int32_t bmp180_temp, bmp180_press;
// wzór znaku termometru w pamiêci FLASH
const uint8_t degree[] PROGMEM = {14,17,17,17,14,32,32,32};

// Zmienne na potrzeby czujnika HTU21D
uint8_t htu21_test[3];			// Tablica na odebrane 3 bajty wilgotnoœci

uint16_t htu21_h;				// Wilgotnosc odczytana
uint32_t htu21_humid;			// Wilgotnosc po konwersji

// przerwanie co 10ms
volatile uint16_t prog_timer1;
// flaga do zmiany wyœwietlanych danych
uint8_t flaga = 1;

int main (void)
{
	lcd_init();						// inicjalizacja LCD
	lcd_defchar_P(0x80, degree);	// za³adowanie do pamiêci wyœwietlacza znaku stopnia
	i2cSetBitrate(100);				// inicjalizacja I2C
	BMP180_init();					// inicjalizacja BMP180 - pobranie danych kalibracyjnych
	HTU21_init();					// inicjalizacja HTU21 - soft reset
	USART_Init(__UBRR);				// inicjalizacja UART
    nRF_init();						// inicjalizacja nRF

    //rejestracja funkcji
    register_nRF_RX_Event_Callback(transmit_uart);

    //inicjalizacja przerwania co 10ms
    TCCR0 |= (1<<WGM01);				// tryb CTC
    TCCR0 |= (1<<CS01) | (1<<CS00);		// preskaler 1024
    TIMSK |= (1<<OCIE0);
   	OCR0 = 107;							//11059200/1024/107 = 100Hz(10ms)

    // globalne zezwolenie na przerwania
    sei();

    nRF_RX_Power_Up(); // w³¹czenie modu³u nRF w trybie odbiorczym

	while(1)
	{

		nRF_RX_EVENT();

		if(!prog_timer1)
		{
			prog_timer1 = 10000;		//zmiana wyswietlania co 10s
			flaga ^= 0x1;
		}
		if(flaga == 1)
		{
			// ODCZYT TEMPERATURY I WILGOTNOŒCI
			bmp180_temp = BMP180_gett();
			bmp180_press = BMP180_getp();

	        //ODCZYT WILGOTNOŒCI
	        HTU21_read_humid(3,htu21_test);
	        htu21_h= ((uint8_t)htu21_test[0]<<8)|((uint8_t)htu21_test[1]>>2);

	        // konwersja wilgotnosci
	        htu21_humid = (uint32_t)htu21_h*125;
	        htu21_humid >>= 16;
	        htu21_humid -= 6;

			ShowOnLCD();
			_delay_ms(1000);
		}
		else
		{
			receive_and_display();
			_delay_ms(1000);
		}
	}
}
///////////////////////////////////////////////////////////

ISR(TIMER0_COMP_vect)
{
	uint16_t x;
	x = prog_timer1;
	if(x) prog_timer1 = --x;
}

void transmit_uart(void * nRF_RX_buff, uint8_t len )
{
	// oblicznie dlugosci odebranego ciagu (w bajtach)
	char buffer_for_itoa[4] = {0, 0, 0, 0};
	itoa( len, buffer_for_itoa, 10 );

//	uint8_t data[13] = {0};
//	uint8_t i;
//	for(i=0; i<13; i++)
//		{
//		data[i] = nRF_RX_bufffer[i];
//		}

	// wyœwietlenie: odebrane dane [dlugosc]
	uart_puts((char *) nRF_RX_buff);
	uart_puts("[");
	uart_puts(buffer_for_itoa);
	uart_puts("]\r\n");
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

void ShowOnLCD(void){
	lcd_cls();
	lcd_locate(0,0);
	lcd_str("T: ");
	lcd_int(bmp180_temp/10);
	lcd_str(".");
	if(bmp180_temp > 0)
		lcd_int(bmp180_temp%10);
	else
		lcd_int((bmp180_temp%10)*-1);
	lcd_str("\x80");			// w³asny znak - stopien
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
