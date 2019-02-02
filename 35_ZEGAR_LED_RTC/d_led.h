#ifndef _d_led_h
#define _d_led_h

// DEFINICJA PORTOW SEGMENTOW
#define DATA_PORT PORTB
#define DATA_DDR DDRB
//DEFINICJA POSZCZEGOLNYCH SEGMENTOW
#define SEG_A (1<<PB0)
#define SEG_B (1<<PB1)
#define SEG_C (1<<PB2)
#define SEG_D (1<<PB3)
#define SEG_E (1<<PB4)
#define SEG_F (1<<PB5)
#define SEG_G (1<<PB6)
#define SEG_DP (1<<PB7)

#define NIC 10

//DEFINICJA PORTOW ANOD
#define ANODE_PORT PORTC
#define ANODE_DDR DDRC
//DEFNICJA POSZCZEGOLNYCH ANOD
#define A_D1 (1<<PC0)
#define A_D2 (1<<PC1)
#define A_D3 (1<<PC2)
#define A_D4 (1<<PC3)

//DEFINICJE DLA DWUKROPKA
#define CLN_PORT PORTD
#define CLN_DDR DDRD

#define A_CLN (1<<PD3)
#define CLN (1<<PD4)

#define CLN_ON CLN_PORT &= ~(CLN | A_CLN)
#define CLN_TOGGLE CLN_PORT ^= A_CLN
#define CLN_OFF CLN_PORT |= A_CLN


//DEKLARACJE (DEFINICJE W PLIKU .C) ZMIENNYCH DOSTEPNYCH W GLOWNYM PLIKU
extern volatile uint8_t digit1;
extern volatile uint8_t digit2;
extern volatile uint8_t digit3;
extern volatile uint8_t digit4;

void led_disp_init();

#endif	// koniec _d_led_h

