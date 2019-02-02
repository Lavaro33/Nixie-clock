#include <avr/io.h>			// obs³uga portów wejœcia/wyjœcia
#include <util/delay.h>		// obs³uga opóŸnieñ
#include <avr/interrupt.h>	// obs³uga przerwañ
#include <stdlib.h>			// do funkcji itoa
#include <avr/pgmspace.h>	// obs³uga pamiêci flash
#include <avr/wdt.h>

#include "nRF24L01/nRF24L01.h"
#include "LED/led.h"

#define BUFF_SIZE 11

#define DELAY1 1
#define DELAY2 50
#define DELAY3 50
#define DELAY4 50
#define DELAY5 50
#define DELAY6 50

typedef struct {
	uint8_t led1_lock;
	uint8_t led2_lock;
} mono_section;

mono_section sec1, sec2;

typedef struct {
	uint8_t led1_on;
	uint8_t led2_on;
} bi_section;

bi_section sec3;

uint8_t sec4_on;	//flaga wlaczonej sekcji zabezpieczonej

//enum state {
//	idle, sw_first, sw_second, sw_down, sw_no_lock
//} state;
//
//static enum state key_state;

enum state{
	idle, on, turbo
}state;

static enum state turbo_state;

// Odbiór danych ze stacji zew. i wyœwietlenie
void receive_and_display();
// Zapalanie diod zaleznie od przeslanych stanow przyciskow
void led_on_off(uint8_t buff[]);

void prog_timer_init(void);
volatile uint16_t prog_timer1, prog_timer2, prog_timer3, prog_timer4,
		prog_timer5, prog_timer6; //timer programowy na potrzeby wszelakie

int main(void) {
	wdt_disable();
	nRF_init();						// inicjalizacja nRF
	led_init();
	prog_timer_init();

	// globalne zezwolenie na przerwania
	sei();

	nRF_RX_Power_Up(); // w³¹czenie modu³u nRF w trybie odbiorczym

	prog_timer1 = DELAY1;
	prog_timer2 = DELAY2;
	prog_timer3 = DELAY3;
	prog_timer4 = DELAY4;
	prog_timer5 = DELAY5;

	wdt_enable(WDTO_4S);

	while (1) {
		// sprawdzanie ciaglosci dzialania petli glownej
		nRF_RX_EVENT();

		if (!prog_timer1) {
			receive_and_display();
			prog_timer1 = DELAY1;
		}
		wdt_reset();
	}
}
///////////////////////////////////////////////////////////

void receive_and_display() {
	uint8_t data[BUFF_SIZE] = { 0 };
	for (uint8_t i = 0; i < BUFF_SIZE; i++) {
		data[i] = nRF_RX_bufffer[i];
	}
	// kiedy zaden z przyciskow nie jest wcisniety
	// SEKCJA 1
	LED_DEBUG_OFF;

	if (data[0] != '1') {
		LED1_OFF;
		sec1.led2_lock = 0;
	}
	if (data[1] != '1') {
		LED2_OFF;
		sec1.led1_lock = 0;
	}

	// SEKCJA 2
	if (data[2] != '1') {
		LED3_OFF;
		sec2.led2_lock = 0;
	}
	if (data[3] != '1') {
		LED4_OFF;
		sec2.led1_lock = 0;
	}

	led_on_off(data);
}

void led_on_off(uint8_t buff[]) {
	uint8_t rel1 = buff[0];		//sw1
	uint8_t rel2 = buff[1];		//sw2
	uint8_t rel3 = buff[2];		//sw3
	uint8_t rel4 = buff[3];		//sw4
	uint8_t rel5 = buff[4];		//sw5
	uint8_t rel6 = buff[5];		//sw6
	uint8_t rel7 = buff[6];		//sw7 - blokada
	uint8_t rel8 = buff[7];		//sw8
	uint8_t rel9 = buff[8];

	if(rel1 | rel2 | rel3 | rel4 | rel5 | rel6 | rel7 | rel8 | rel9)
		LED_DEBUG_ON;

	//  PRZYCISKI MONOSTABILNE
	// Sekcja 1
	if (rel1 == '1' && !sec1.led1_lock) {
		LED1_ON;
		sec1.led2_lock = 1;
	}
	if (rel2 == '1' && !sec1.led2_lock) {
		LED2_ON;
		sec1.led1_lock = 1;
	}

	// Sekcja 2
	if (rel3 == '1' && !sec2.led1_lock) {
		LED3_ON;
		sec2.led2_lock = 1;
	}
	if (rel4 == '1' && !sec2.led2_lock) {
		LED4_ON;
		sec2.led1_lock = 1;
	}

	// PRZYCISKI BISTABILNE
	// Sekcja 3
	if (rel5 == '1') {
		if (!prog_timer2) {
			if (rel5 == '1' && !sec3.led1_on) {
				if (!sec3.led2_on) {
					LED5_ON;
					sec3.led1_on = 1;
				}
				LED6_OFF;
				sec3.led2_on = 0;
			} else {
				LED5_OFF;
				sec3.led1_on = 0;
			}
			prog_timer2 = DELAY2;
		}
	}

	if (rel6 == '1') {
		if (!prog_timer3) {
			if (rel6 == '1' && !sec3.led2_on) {
				if (!sec3.led1_on) {
					LED6_ON;
					sec3.led2_on = 1;
				}
				LED5_OFF;
				sec3.led1_on = 0;
			} else {
				LED6_OFF;
				sec3.led2_on = 0;
			}
			prog_timer3 = DELAY3;
		}
	}

	//TODO do zmiany!
//	// Sekcja 4 - mechanizm podwojnego wcisniecia
//	if (!sec4_on) {
//		if (rel7 == '1' && rel8 == '1' && !key_state) { // dwa przyciski wcisniete pierwszy raz
//			key_state = sw_first;
//			prog_timer4 = 25;  //po wcisnieciu dwoch przyciskow czekamy 500ms
//			prog_timer5 = 100;		// 2sek na ponowne wcisniecie przycisku
//		} else {
//			if (key_state) {
//				if (rel7 == '1' && !prog_timer4 && key_state >= sw_first) {
//					if (rel8 == '0') {
//						key_state = sw_second;		//drugi przycisk odpuszczony
//					} else if (key_state == sw_second && rel8 == '1'
//							&& prog_timer5) {
//						LED7_ON;
//						sec4_on = 1;
//						key_state = sw_down;
//						prog_timer4 = 50;// to musi byc zeby od razu nie gaslo
//					}
//				} else if (!prog_timer5) {
//					key_state = idle;
//				}
//			}
//		}
//	} else {
//		if (rel7 == '1' && rel8 == '1' && !prog_timer4) {
//			LED7_OFF;
//			sec4_on = 0;
//			key_state = idle;
//		}
//	}
	if (rel7 == '1') {
		// TURBO
		if (rel7 == '1' && rel9 == '1') {
			if (!prog_timer5) {
				if (rel9 == '1' && !(rel8 == '1')) {
					if(turbo_state == idle){
						turbo_state = on;
						LED7_ON;
						LED10_OFF;
					}
					else if(turbo_state == on){
						turbo_state = idle;
						LED7_OFF;
						LED10_OFF;
					}
					else{
						turbo_state = on;
						LED10_OFF;
						LED7_ON;
					}
				}
				prog_timer5 = DELAY5;
			}
		}

		//WYJSCIE
		if (rel7 == '1' && rel8 == '1') {
			if (!prog_timer6) {
				if (rel8 == '1' && !(rel9 == '1')) {
					if(turbo_state == idle){
						turbo_state = turbo;
						LED10_ON;
						LED7_ON;
					}

					else if(turbo_state == on){
						turbo_state = turbo;
						LED10_ON;
						LED7_ON;
					}
					else{
						turbo_state = idle;
						LED10_OFF;
						LED7_OFF;
					}
				}
				prog_timer6 = DELAY6;
			}
		}
	}

//	// Sekcja 4
//	if ((rel7 == '1') && (rel8 == '1')) {
//		if (!prog_timer4) {
//			if ((rel7 == '1') && (rel8 == '1')) {
//				LED7_TOG;
//			}
//			prog_timer4 = DELAY4;
//		}
//	}

// czyszczenie bufora
	for (int i = 0; i < BUFF_SIZE; i++) { // bufor musi byc czyszczony - kontrola poprzedniego stanu jest wylaczna rola odbiornika, nadajnik				// tylko informuje o wcisniecu przyciskow
		nRF_RX_bufffer[i] = 0;
	}
}

void prog_timer_init(void) {
	/* ustawienie TIMER1 dla F_CPU=8MHzMHz */
	TCCR1B |= (1 << WGM12); /* tryb CTC */
	TCCR1B |= (1 << CS12) | (1 << CS10); /* preskaler = 1024 */
	OCR1A = 78; /* dodatkowy podzia³ przez 78 (rej. przepe³nienia) */
	TIMSK1 |= (1 << OCIE1A); /* zezwolenie na przerwanie CompareMatch */
	/* przerwanie wykonywane z czêstotliwoœci¹ ok 10ms (100 razy na sekundê) */
}

ISR(TIMER1_COMPA_vect) {
	uint16_t x;
//timery programowe (100Hz = 10ms):
	x = prog_timer1;
	if (x)
		prog_timer1 = --x;
	x = prog_timer2;
	if (x)
		prog_timer2 = --x;
	x = prog_timer3;
	if (x)
		prog_timer3 = --x;
	x = prog_timer4;
	if (x)
		prog_timer4 = --x;
	x = prog_timer5;
	if (x)
		prog_timer5 = --x;
	x = prog_timer6;
	if (x)
		prog_timer6 = --x;
}
