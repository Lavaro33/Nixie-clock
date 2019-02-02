#include <avr/io.h>		// do³¹czenie g³ównego systemowego  pliku nag³ówkowego
#include <avr/interrupt.h>
#include <util/delay.h>


#include "d_led.h"		// do³¹czenie naszego pliku nag³ówkowego (obs³uga LED)
#include "DEBOUNCE/debounce.h"
#include "I2C_TWI/i2c_twi.h"

// **** UWAGA - wybierz w³aciwy adres jak ni¿ej **************
//#define PCF8583_ADDR 0xA0		// gdy A1 --> GND
#define PCF8583_ADDR 0xA2		// gdy A1 --> VCC

#define SW1 (1<<PD0)
#define SW2 (1<<PD1)

#define SW_PORT PORTD
#define SW_DDR DDRD
#define SW_PIN PIND

uint8_t godz = 17;
uint8_t min = 05;
uint8_t sek = 0;

void inc_godz(void);
void inc_min(void);

volatile uint8_t int0_flag=1;	// flaga zmieniana w przerwaniu i sprawdzana w pêtli g³ównej

enum {ss=1, mm, hh};
uint8_t bufor[4];		// rezerwacja bufora 4 bajty


// konwersja liczby dziesiêtnej na BCD
uint8_t dec2bcd(uint8_t dec);
// konwersja liczby BCD na dziesiêtn¹
uint8_t bcd2dec(uint8_t bcd);

int main(void)
{
	// Przerwanie INT0
	EICRA |= (1<<ISC01);	// wyzwalanie zboczem opadaj¹cym
	EIMSK |= (1<<INT0);		// odblokowanie przerwania
	PORTD |= (1<<PD2);		// podci¹gniêcie pinu INT0 do VCC


	// ****** inicjalizacja *********
	led_disp_init();
	program_timer_init();
	i2cSetBitrate( 100 ); // USTAWIAMY prêdkoœæ 100 kHz na magistrali I2C

	SW_PORT |= (SW1 | SW2);
	SW_DDR &= ~(SW1 | SW2);		// kierunek wejsciowy

	sei();			// w³¹czenie globalnego zezwolenia na przerwania


//	bufor[0] = 0;			// setne czêœci sekundy
//	bufor[1] = dec2bcd(0);	// sekundy
//	bufor[2] = dec2bcd(0);	// minuty
//	bufor[3] = dec2bcd(0);	// godziny
//	// zapis 4 bajtów z bufora pod adres 0x01 w pamiêci RAM naszego RTC
//	TWI_write_buf( PCF8583_ADDR, 0x01, 4, bufor );


	//timer1  = 100;				// odmierzanie 1 sekundy

	CLN_ON;
		//**********************  pêtla g³ówna
		while(1)
		{
			digit1 = (godz > 9)? godz/10 : NIC;
			digit2 = godz%10;
			digit3 = min/10;
			digit4 = min%10;

			SuperDebounce(&SW_PIN, SW1, 10, 100, inc_godz, inc_godz);
			SuperDebounce(&SW_PIN, SW2, 10, 100, inc_min, inc_min);

			if ( int0_flag ) {
				//odczyt 4 bajtów do bufora od adresu 0x01 z pamiêci RAM naszego RTC
				TWI_read_buf( PCF8583_ADDR, 0x01, 4, bufor );

				sek = bcd2dec( bufor[ss] );
				min = bcd2dec( bufor[mm] );
				godz = bcd2dec( bufor[hh] );

				CLN_TOGGLE;
				int0_flag=0;
			}

//			if(!timer1)
//			{
//				sek++;
//				CLN_TOGGLE;
//				timer1 = 100;
//			}

		}
}
///////////////////////////////////////////////////////////////

// procedura obs³ugi przerwania INT 0
ISR( INT0_vect ) {
	int0_flag = 1;
}


// konwersja liczby dziesiêtnej na BCD
uint8_t dec2bcd(uint8_t dec) {
return ((dec / 10)<<4) | (dec % 10);
}

// konwersja liczby BCD na dziesiêtn¹
uint8_t bcd2dec(uint8_t bcd) {
    return ((((bcd) >> 4) & 0x0F) * 10) + ((bcd) & 0x0F);
}

void inc_godz(void)
{
	sek = bcd2dec( bufor[ss] );
	min = bcd2dec( bufor[mm] );
	godz = bcd2dec( bufor[hh] );

	godz = (godz < 23)? godz+1 : 0;

	bufor[0] = 0;			// setne czêœci sekundy
	bufor[1] = dec2bcd(0);	// sekundy
	bufor[2] = dec2bcd(min);	// minuty
	bufor[3] = dec2bcd(godz);	// godziny
	// zapis 4 bajtów z bufora pod adres 0x01 w pamiêci RAM naszego RTC
	TWI_write_buf( PCF8583_ADDR, 0x01, 4, bufor );
}

void inc_min(void)
{
	sek = bcd2dec( bufor[ss] );
	min = bcd2dec( bufor[mm] );
	godz = bcd2dec( bufor[hh] );

	min = (min < 59)? min+1 : 0;

	bufor[0] = 0;			// setne czêœci sekundy
	bufor[1] = dec2bcd(0);	// sekundy
	bufor[2] = dec2bcd(min);	// minuty
	bufor[3] = dec2bcd(godz);	// godziny
	// zapis 4 bajtów z bufora pod adres 0x01 w pamiêci RAM naszego RTC
	TWI_write_buf( PCF8583_ADDR, 0x01, 4, bufor );
}
