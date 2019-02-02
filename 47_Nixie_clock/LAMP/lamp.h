/*
 * lamp.h
 *
 *  Created on: 1 gru 2018
 *      Author: Daniel
 */

#ifndef LAMP_H_
#define LAMP_H_

//DEFINICJA PORTOW I KIERUNKOW CYFR
#define DATA1_PORT PORTA
#define DATA2_PORT PORTC

#define DATA1_DDR DDRA
#define DATA2_DDR DDRC

//DEFINICJA POSZCZEGOLNYCH KATOD
#define K0 (1<<PA0)
#define K1 (1<<PA1)
#define K2 (1<<PA2)
#define K3 (1<<PA3)
#define K4 (1<<PA4)
#define K5 (1<<PA5)
#define K6 (1<<PA6)
#define K7 (1<<PA7)
#define K8 (1<<PC2)
#define K9 (1<<PC3)


//DEFINICJA PORTOW ANOD
#define ANODE_PORT PORTD
#define ANODE_DDR DDRD

//DEFINICJA ANOD
#define A_L1 (1<<PD7)
#define A_L2 (1<<PD6)
#define A_L3 (1<<PD5)
#define A_L4 (1<<PD4)

//DEFINICJA DWUKROPKA
// todo:TO MO¯E SIE ZMIENIC PO WPROWADZENIU NEONEK
#define CLN_PORT PORTC
#define CLN_DDR DDRC
#define CLN (1<<PC4)
#define CLN_OFF CLN_PORT |= CLN
#define CLN_ON COLON_PORT  &= ~COLON
#define CLN_TOG CLN_PORT ^= CLN

//DEFINICJA PRZYCISKOW
#define SW1 (1<<PC6)
#define SW2 (1<<PC7)

#define SW_PORT PORTC
#define SW_DDR DDRC
#define SW_PIN PINC

//DEKLARACJE CYFR DLA GLOWNEGO PLIKU .C
extern volatile uint8_t digit1;
extern volatile uint8_t digit2;
extern volatile uint8_t digit3;
extern volatile uint8_t digit4;

void extern lamp_disp_init();		// inicjalizacja portow i kierunkow wyswietlacza
void extern sw_init();				// inicjalizacja przyciskow
void extern disp(uint8_t digit);	// wyswietlenie pojedynczej cyfry
void extern disp_null();			// wygasza pojedyncza lampe

#endif /* LAMP_H_ */
