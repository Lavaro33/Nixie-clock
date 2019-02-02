#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include <util/delay.h>

#include "LCD/lcd44780.h"
#include "1Wire/ds18x20_service.h"
#include "DEBOUNCE/debounce.h"
#include "SWITCH/switch.h"

#define LED_WORK PC7
#define LED_HEAT PC6
#define LED_AIR PC5

#define LED_PORT PORTC
#define LED_DDR DDRC

typedef struct
{
	uint8_t min;
	uint8_t sec;
}time;

typedef enum
{
	no_work,		// pauza
	work,			// odliczanie w³¹czone
	time_set,		// menu -> ustawienia czasu trawienia
	temp_set,		// menu -> ustawienia temperatur grza³ki
	air_set			// menu -> ustawienia stopnia napowietrzania
}menu_level;

typedef enum
{
	param_zero,
	param_one,
	param_two
}submenu_level;

void time_inc(void);
void time_dec(void);
void work_display(void);
void work_start(void);
void menu_set(void);
void next_level(void);
void next_sub_level(void);
void time_display(uint8_t x, uint8_t y);
void temp_init(void);
void display_set_temp(void);
void temp_inc(void);
void temp_dec(void);
void lcd_blink(submenu_level param);
void led_init(void);
void heater_ctrl (uint8_t heat_on);
uint8_t temp_comp(temp meas_t, temp set_t, temp his_t);
void display_meas_temp(temp t_result, uint8_t x, uint8_t y);

const uint8_t thermo[] PROGMEM = {4,10,10,10,17,31,31,14};		// znak termometru w pamiêci FLASH
const uint8_t degree[] PROGMEM = {14,17,17,17,14,32,32,32}; 	// znak stopnia
const uint8_t clock[] PROGMEM = {32,32,14,21,23,17,14,32};		// znak termometru w pamiêci FLASH
const uint8_t arrow[] PROGMEM = {32,4,2,31,2,4,32,32};			// znak strza³ki w prawo do temperatury zadanej
const uint8_t dual_arrow[] PROGMEM = {4,14,21,32,32,21,14,4};	// znak strza³ki w prawo do temperatury zadanej
const uint8_t fluid[] PROGMEM = {32,8,21,2,8,21,2,32};			// znak roztworu do temperatury aktualnej

time etching_t = {.min = 10, .sec = 0};			// struktura do odmierzania czasu trawienia
menu_level m_level = no_work;				// zmienna przetrzymuj¹ca aktualny poziom w menu
submenu_level sub_level = param_one;		// domyœlnie jako pierwszy ustawiany jest parametr pierwszy w podmenu
temp temp_meas;		// pomierzona temperatura
temp temp_heat;		// ustawiona temperatura docelowa, powy¿ej której grza³ka siê wy³¹czy
temp temp_his;		// Histereza grzania
uint8_t his_on_flag;		// Flaga histerezy, funkcja histerezy jest aktywna dopiero po pierwszym dogrzaniu do zadanej temperatury

int main(void) {

	led_init();		// inicjalizacja kontrolek LED
	lcd_init();		/* inicjalizacja LCD */
	ds18x20_timer_init(); 	// inicjalizacja timerów czujnika
	program_timer_init();
	switch_init();
	temp_init();		// Inicjalizacja domyslnych parametrow temperatury

	sei();

	lcd_defchar_P(0x80, thermo);		// znak termometru za³adowany pod adres 0x80 LCD
	lcd_defchar_P(0x81, degree);		// znak stopnia
	lcd_defchar_P(0x82, clock);			// znak zegara
	lcd_defchar_P(0x83, arrow);
	lcd_defchar_P(0x84, dual_arrow);
	lcd_defchar_P(0x85, fluid);

	timer_etching = 100;
	timer_blink_on = 30;
	timer_blink_off = 60;

	while(1)
	{
		if(m_level == no_work || m_level == work)
			SuperDebounce(&SW_PIN, SW_MENU, 100, 200, work_start, menu_set);	// krótkie - start/pauza; d³ugie - wchodzimy do menu
		else
			SuperDebounce(&SW_PIN, SW_MENU, 100, 200, next_level, menu_set);	// krótkie - kolejny poziom menu; d³ugie - wychodzimy z menu

		switch(m_level)
		{
			case no_work:		// stan po w³¹czeniu lub wciœniêta pauza
			{
				LED_PORT &= ~(1<<LED_WORK);			// LED_WORK œwieci ci¹gle w czasie pauzy
				LED_PORT |= (1<<LED_HEAT);			// grznanie wy³¹czone
				temp_meas = ds18x20_get_temp();
				display_meas_temp(temp_meas, 0, 1);
				work_display();
				break;
			}

			case work:		// odliczanie trwa
			{
				temp_meas = ds18x20_get_temp();
				display_meas_temp(temp_meas, 0, 1);
				work_display();
				heater_ctrl(temp_comp(temp_meas, temp_heat, temp_his));			// Za³¹cz grza³kê jeœli zmierzona temperatura mniejsza od zadanej

				if(!timer_etching)	// minela sekunda
				{
					LED_PORT ^= (1<<LED_WORK);		// LED_WORK miga co sekunde w czasie odliczania
					if(etching_t.min > 0)
					{
						if(etching_t.sec > 0)
						{
							etching_t.sec--;
						}
						else
						{
							etching_t.sec = 59;
							etching_t.min--;
						}
					}
					else
					{
						if(etching_t.sec > 0)
							etching_t.sec--;
					}
					timer_etching = 100;
				}
				work_display();
				break;
			}

			case time_set:		// Tryb ustawieñ czasu trawienia
			{
				lcd_locate(0,0);
				lcd_str("  --TIME SET-- ");
				SuperDebounce(&SW_PIN, SW_UP, 10, 200, time_inc, time_inc);
				SuperDebounce(&SW_PIN, SW_DOWN, 10, 200, time_dec, time_dec);
				if(!timer_blink_on)
				{
					lcd_blink(param_zero);
					timer_blink_on = 30;
				}
				if(!timer_blink_off)
				{
					time_display(1, 6);
					timer_blink_off = 60;
				}
				break;
			}

			case temp_set:		// Tryb ustawieñ
			{
				lcd_locate(0,0);
				lcd_str("  --TEMP SET-- ");
				if(!timer_blink_on)
				{
					lcd_blink(sub_level);
					timer_blink_on = 30;
				}
				if(!timer_blink_off)
				{
					display_set_temp();
					timer_blink_off = 60;
				}
				SuperDebounce(&SW_PIN, SW_SUB, 10, 200, next_sub_level, next_sub_level);
				SuperDebounce(&SW_PIN, SW_UP, 10, 200, temp_inc, temp_inc);
				SuperDebounce(&SW_PIN, SW_DOWN, 10, 200, temp_dec, temp_dec);
				break;
			}
			case air_set:
			{
				lcd_locate(0,0);
				lcd_str("  --AIR SET--  ");
				break;
			}

			default:
			{
				lcd_locate(0,0);
				lcd_str("   ---ERROR---  ");
			}
		}
	}
}

/* Kolejny poziom menu pod wp³ywem wciœniêcia SW_MENU */
void next_level(void)
{
	lcd_cls();
	switch(m_level)
	{
		case time_set: m_level = temp_set; break;
		case temp_set: m_level = air_set; break;
		case air_set: m_level = time_set; break;
		default: {lcd_cls(); lcd_str("   ---ERROR---  ");}
	}
}

void next_sub_level(void)
{
	lcd_cls();
	if(sub_level == param_one)
	{
		sub_level = param_two;
	}
	else
	{
		sub_level = param_one;
	}
}

/* Wejœcie w tryb ustawieñ */
void menu_set(void)
{
	lcd_cls();
	if(m_level == no_work || m_level == work)	// wchodzimy do ustawieñ
	{
		m_level = time_set;

		lcd_locate(0, 4);
		lcd_str("SETTINGS");
		lcd_locate(1, 6);
		lcd_str("MODE");
		_delay_ms(1000);
		lcd_cls();
	}
	else		// wychodzimy z ustawieñ
	{
		m_level = no_work;

		lcd_locate(0, 4);
		lcd_str("SETTINGS");
		lcd_locate(1, 5);
		lcd_str("SAVED");
		_delay_ms(1000);
		lcd_cls();
	}
}

/* Rozpoczêcie pracy lub pauza pod wp³ywem naciœniêcia przycisku SW_MENU */
void work_start(void)
{
	lcd_cls();
	if(m_level == no_work)
		m_level = work;
	else
		m_level = no_work;
	work_display();
}

/* Zwiêkszanie nastawy czasu trawienia (SW_UP) */
void time_inc(void)
{
	etching_t.min++;
	etching_t.sec = 0;
}

/* Zmniejszanie nastawy czasu trawienia (SW_DOWN) */
void time_dec(void)
{
	etching_t.min--;
	etching_t.sec = 0;
}

/* Wyœwietla pozosta³y czas trawnienia */
void work_display(void)
{
	lcd_locate(0,0);
	lcd_str("\x80\x85");		// wyœwietl górny znak termometru
	lcd_locate(0, 10);
	lcd_str("\x82");		// wyœwietl znak zegara

	time_display(0, 11);
	display_set_temp();
}

/* Wyœwietla pozosta³y czas trawienia
 * x - pozycja x do wyœwietlenia
 * y - pozycja y do wyœwietlenia
 */
void time_display(uint8_t x, uint8_t y)
{
	lcd_locate(x, y);
	if(etching_t.min > 9)
		lcd_int(etching_t.min);
	else
	{
		lcd_str(" ");
		lcd_int(etching_t.min);
	}
	lcd_str(":");
	if(etching_t.sec > 9)
		lcd_int(etching_t.sec);
	else
	{
		lcd_int(0);
		lcd_int(etching_t.sec);
	}
}

/* Inicjalizacja domyslnych parametrow temperatury */
void temp_init(void)
{
	his_on_flag = 0;			// pocz¹tkowo histereza wy³¹czona
	temp_heat.cel = 28;
	temp_heat.cel_fract_bits = 0;

	temp_his.cel = 0;
	temp_his.cel_fract_bits = 5;
}

/* Wyœwietlenie temperatury w ustawieniach */
void display_set_temp(void)
{
	lcd_locate(1, 0);
	lcd_str("\x80\x83");
	lcd_int(temp_heat.cel);
	lcd_str(".");
	lcd_int(temp_heat.cel_fract_bits);
	lcd_str("\x81""C");

	lcd_locate(1, 9);
	lcd_str("\x80\x84");
	lcd_int(temp_his.cel);
	lcd_str(".");
	lcd_int(temp_his.cel_fract_bits);
	lcd_str("\x81""C");
}

/* Inkrementacja temperatur. Gorna granica 50 st. */
void temp_inc(void)
{
	if(sub_level == param_one)
	{
		if(temp_heat.cel < 50)
		{
			if(temp_heat.cel_fract_bits < 5)
			{
				temp_heat.cel_fract_bits += 5;
			}
			else
			{
				temp_heat.cel_fract_bits = 0;
				temp_heat.cel++;
			}
		}
	}
	else
	{
		if(temp_his.cel < 5)
		{
			if(temp_his.cel_fract_bits < 5)
			{
				temp_his.cel_fract_bits += 5;
			}
			else
			{
				temp_his.cel_fract_bits = 0;
				temp_his.cel++;
			}
		}
	}
}

/* Dekrementacja temperatur. Dolna granica 30 st. */
void temp_dec(void)
{
	if(sub_level == param_one)
	{
		if(temp_heat.cel >= 20)
		{
			if(temp_heat.cel_fract_bits > 0)
			{
				temp_heat.cel_fract_bits -= 5;
			}
			else
			{
				if(temp_heat.cel > 20)
				{
					temp_heat.cel_fract_bits = 5;
					temp_heat.cel--;
				}
			}
		}
	}
	else
	{
		if(temp_his.cel >= 0 )
		{
			if(temp_his.cel_fract_bits > 0 && temp_his.cel > 0)
			{
				temp_his.cel_fract_bits -= 5;
			}
			else
			{
				if(temp_his.cel > 0)
				{
					temp_his.cel_fract_bits = 5;
					temp_his.cel--;
				}
			}
		}
	}
}

/* Wygaszenie wskazanej pozycji na wyœwietlaczu. Zale¿ne od akutalnego trybu pracy (podmenu) */
void lcd_blink(submenu_level param)
{
	if(param == param_zero)
	{
		lcd_locate(1, 0);
		lcd_str("                ");
	}
	else if(param == param_one)
		lcd_locate(1, 0);
	else
		lcd_locate(1, 8);
	lcd_str("        ");
}

/* Inicjalizacja 3 LEDowych wskaŸników pracy */
void led_init(void)
{
	LED_DDR |= (1<<LED_WORK)|(1<<LED_HEAT)|(1<<LED_AIR);	// Kierunek wyjœciowy
	LED_PORT |= (1<<LED_WORK)|(1<<LED_HEAT)|(1<<LED_AIR);	// Wszystkie LEDy domyœlnie wy³¹czone
}

/* Porównanie temperatur: zmierzonej i zadanej.
 * Zwraca 1, jeœli zadana > zmierzonej,
 * w przeciwnym wypadku zwraca 0.
 */
uint8_t temp_comp(temp meas_t, temp set_t, temp his_t)
{
	int16_t meas_tmp = meas_t.cel*10 + meas_t.cel_fract_bits;
	int16_t set_tmp = set_t.cel*10 + set_t.cel_fract_bits;
	int16_t his_tmp = his_t.cel*10 + his_t.cel_fract_bits;

	if(!his_on_flag)	// Dogrzewanie - histereza wy³¹czona
	{
		if(set_tmp > meas_tmp)
		{
			return 1;
		}
		else
		{
			his_on_flag = 1;
			return 0;
		}
	}
	else
	{
		if(set_tmp - meas_tmp > his_tmp)
		{
			his_on_flag = 0;
			return 1;
		}
		else
		{
			return 0;
		}
	}
}

/* Sterowanie grza³k¹.
 * Jeœli heat_on == 1 -> grzanie. Jeœli 0 -> stop.
 */
void heater_ctrl (uint8_t heat_on)
{
	if(heat_on)		// Dogrzewamy
	{
		PORTC &= ~(1<<LED_HEAT);
	}
	else			// Koniec grzania
	{
		PORTC |= (1<<LED_HEAT);
		// PAMIÊTAC, ¿eby wy³¹czyc grzalke w sekcji no_work !!!
	}
}

/* Wyœwietlenie temperatury zmierzonej (np. 27.6*C)
 * x - pozycja w pionie, y - pozycja w poziomie
 */
void display_meas_temp(temp t_result, uint8_t x, uint8_t y)
{
	lcd_locate(x, y);
	if(t_result.subzero) lcd_str("-");	/* jeœli subzero==1 wyœwietla znak minus (temp. ujemna) */
	else lcd_str(" ");
	lcd_int(t_result.cel);	/* wyœwietl dziesiêtne czêœci temperatury  */
	lcd_str(".");
	lcd_int(t_result.cel_fract_bits); /* wyœwietl dziesiêtne czêœci stopnia */
	lcd_str("\x81");
	lcd_str("C ");
}


