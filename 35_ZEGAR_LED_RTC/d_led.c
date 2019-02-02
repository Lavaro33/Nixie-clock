#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>

#include "d_led.h"			// do³¹czenie naszego pliku nag³ówkowego
							// w nim znajduj¹ siê potrzebne tu m.in. definicje preprocesora

volatile uint8_t digit1;
volatile uint8_t digit2;
volatile uint8_t digit3;
volatile uint8_t digit4;



const uint8_t digits[11] PROGMEM = {
		~(SEG_A|SEG_B|SEG_C|SEG_D|SEG_E|SEG_F),			// 0
		~(SEG_B|SEG_C),									// 1
		~(SEG_A|SEG_B|SEG_D|SEG_E|SEG_G),				// 2
		~(SEG_A|SEG_B|SEG_C|SEG_D|SEG_G),				// 3
		~(SEG_B|SEG_C|SEG_F|SEG_G),						// 4
		~(SEG_A|SEG_C|SEG_D|SEG_F|SEG_G),				// 5
		~(SEG_A|SEG_C|SEG_D|SEG_E|SEG_F|SEG_G),			// 6
		~(SEG_A|SEG_B|SEG_C|SEG_F),						// 7
		~(SEG_A|SEG_B|SEG_C|SEG_D|SEG_E|SEG_F|SEG_G),	// 8
		~(SEG_A|SEG_B|SEG_C|SEG_D|SEG_F|SEG_G),			// 9
		(SEG_A|SEG_B|SEG_C|SEG_D|SEG_E|SEG_F|SEG_G|SEG_DP)		// nic
};

void led_disp_init()
{
	DATA_PORT |= 0xFF;		//wszystkie segmenty wygaszone
	DATA_DDR |= 0xFF; 		//kierunek wyjsciowy

	ANODE_PORT |= A_D1 | A_D2 | A_D3 | A_D4;		//wszystkie anody wygaszone
	ANODE_DDR |= A_D1 | A_D2 | A_D3 | A_D4;	// kierunek wyjsciowy

	CLN_PORT |= CLN | A_CLN;
	CLN_DDR |= CLN | A_CLN;

	//Ustawienie timera0
	TCCR0A |= (1<<WGM01);				//tryb CTC
	TCCR0B |= (1<<CS02)|(1<<CS00);		//preskaler 1024
	OCR0A = 19;		//podzial przez dodatkowe 19 daje 400Hz (100Hz na jedna cyfre)
	TIMSK0 |= (1<<OCIE0A);
}

ISR(TIMER0_COMPA_vect)
{
	static uint8_t cnt = 1;		// zmienna do przelaczania kolejnych cyfr

	if(cnt == 1) DATA_PORT = pgm_read_byte(&digits[digit1]);	//zapalona pierwsza cyfra
	if(cnt == 2) DATA_PORT = pgm_read_byte(&digits[digit2]);	//zapalona druga cyfra
	if(cnt == 4) DATA_PORT = pgm_read_byte(&digits[digit3]);	//zapalona trzecia cyfra
	if(cnt == 8) DATA_PORT = pgm_read_byte(&digits[digit4]);	//zapalona czwarta cyfra

	//zapisanie stanu licznika cyfr do portu
	ANODE_PORT = (ANODE_PORT & 0xF0) | (~cnt & 0x0F);
	//cykliczne przelaczanie
	cnt <<= 1;
	if(cnt>8) cnt = 1;
}


