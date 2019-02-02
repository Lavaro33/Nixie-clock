#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdlib.h>
#include <string.h>
#include <avr/pgmspace.h>

#include "nRF24L01/nRF24L01.h"
#include "DEBOUNCE/debounce.h"

void sw1_serv(void);
void sw2_serv(void);
void sw3_serv(void);
void sw4_serv(void);
void sw5_serv(void);

// tablica do przeslania
char transmit[2];

int main (void)
{
	//inicjalizacja nRFa
    nRF_init();
    program_timer_init();
    switch_init();

   	//zezwolenie na przerwania
    sei();

	while(1)
	{
		SuperDebounce(&SW1_PIN, SW1, 100, 200, sw1_serv, sw1_serv);
		SuperDebounce(&SW2_PIN, SW2, 100, 200, sw2_serv, sw2_serv);
		SuperDebounce(&SW3_PIN, SW3, 100, 200, sw3_serv, sw3_serv);
		SuperDebounce(&SW4_PIN, SW4, 100, 200, sw4_serv, sw4_serv);
		SuperDebounce(&SW5_PIN, SW5, 100, 200, sw5_serv, sw5_serv);
	}
}

void sw1_serv(void)
{
	transmit[0] = '1';
	transmit[1] = '\0';
	nRF_SendDataToAir(transmit); // do dlugosci wlicza sie jeszcze '0' na koniec stringa
}

void sw2_serv()
{
	transmit[0] = '2';
	transmit[1] = '\0';
	nRF_SendDataToAir(transmit); // do dlugosci wlicza sie jeszcze '0' na koniec stringa
}

void sw3_serv()
{
	transmit[0] = '3';
	transmit[1] = '\0';
	nRF_SendDataToAir(transmit); // do dlugosci wlicza sie jeszcze '0' na koniec stringa
}

void sw4_serv()
{
	transmit[0] = '4';
	transmit[1] = '\0';
	nRF_SendDataToAir(transmit); // do dlugosci wlicza sie jeszcze '0' na koniec stringa
}

void sw5_serv()
{
	transmit[0] = '5';
	transmit[1] = '\0';
	nRF_SendDataToAir(transmit); // do dlugosci wlicza sie jeszcze '0' na koniec stringa
}
