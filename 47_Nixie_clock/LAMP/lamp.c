/*
 * lamp.c
 *
 *  Created on: 1 gru 2018
 *      Author: Daniel
 */

#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>

#include "lamp.h"			// do³¹czenie naszego pliku nag³ówkowego
// w nim znajduj¹ siê potrzebne tu m.in. definicje preprocesora
volatile uint8_t digit1;
volatile uint8_t digit2;
volatile uint8_t digit3;
volatile uint8_t digit4;

// inicjalizacja przyciskow
void sw_init() {
	SW_PORT |= (SW1 | SW2);
	SW_DDR &= ~(SW1 | SW2);		// kierunek wejsciowy
}

// inicjalizacja portow i kierunkow wyswietlaczy
void lamp_disp_init() {
	// wyzerowanie wszystkich cyfr i ustawienie kierunkow jako wyjsciowe
	DATA1_PORT &= ~(K0 | K1 | K2 | K3 | K4 | K5 | K6 | K7);
	DATA2_PORT &= ~(K8 | K9);

	// wylaczenie wszystkich anod
	ANODE_PORT &= ~(A_L1 | A_L2 | A_L3 | A_L4);
	ANODE_DDR |= (A_L1 | A_L2 | A_L3 | A_L4);

	CLN_OFF; 			//wygaszenie dwukropka
	CLN_DDR |= CLN; 	//kierunek dwukropka wyjsciowy

	//Ustawienie timera0
	TCCR0 |= (1 << WGM01);				//tryb CTC
	TCCR0 |= (1 << CS02) | (1 << CS00);		//preskaler 1024
	OCR0 = 19;	//podzial przez dodatkowe 38 daje 200Hz (50Hz na jedna cyfre)
	TIMSK |= (1 << OCIE0);
}

// Wygasza jedna lampe
void disp_null() {
	DATA1_PORT = 0x00;
	DATA2_PORT &= ~(K8 | K9);
}

// Wyswietlenie jednej cyfry
void disp(uint8_t digit) {
	// Wygasza jedna lampe
	disp_null();
	switch (digit) {
	case 0:
		DATA1_PORT |= K0;
		break;
	case 1:
		DATA1_PORT |= K1;
		break;
	case 2:
		DATA1_PORT |= K2;
		break;
	case 3:
		DATA1_PORT |= K3;
		break;
	case 4:
		DATA1_PORT |= K4;
		break;
	case 5:
		DATA1_PORT |= K5;
		break;
	case 6:
		DATA1_PORT |= K6;
		break;
	case 7:
		DATA1_PORT |= K7;
		break;
	case 8:
		DATA2_PORT |= K8;
		break;
	case 9:
		DATA2_PORT |= K9;
		break;
	default:
		DATA1_PORT |= K0;
		break;
	}
}

ISR(TIMER0_COMP_vect) {
	static uint8_t cnt = 128;		// zmienna do przelaczania kolejnych cyfr

	if (cnt == 128) {
		disp(digit1);	//zapalona pierwsza cyfra
		ANODE_PORT = (ANODE_PORT & 0X0F) | 0X80;
	}
	if (cnt == 64)
		disp_null();	//zapalona druga cyfra
	if (cnt == 32) {
		disp(digit2);	//zapalona trzecia cyfra
		ANODE_PORT = (ANODE_PORT & 0X0F) | 0X40;
	}
	if (cnt == 16)
		disp_null();	//zapalona czwarta cyfra
	if (cnt == 8) {
		disp(digit3);	//zapalona pierwsza cyfra
		ANODE_PORT = (ANODE_PORT & 0X0F) | 0X20;
	}
	if (cnt == 4)
		disp_null();	//zapalona druga cyfra
	if (cnt == 2) {
		disp(digit4);	//zapalona trzecia cyfra
		ANODE_PORT = (ANODE_PORT & 0X0F) | 0X10;
	}
	if (cnt == 1)
		disp_null();	//zapalona czwarta cyfra

	//cykliczne przelaczanie
	cnt >>= 1;
	if (cnt < 1)
		cnt = 128;
}


