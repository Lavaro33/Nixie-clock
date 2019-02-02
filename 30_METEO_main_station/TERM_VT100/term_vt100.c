/*
 * term_vt100.c
 *
 *  Created on: 14 paŸ 2015
 *      Author: Daniel
 */

#include <avr/io.h>
#include <avr/pgmspace.h>

#include "../MKUART/mkuart.h"
#include "term_vt100.h"

// aby mieæ polskie ogonki w PUTTY ----> ustawiæ WINDOW / Translation / Win1250

const char UCLS[] PROGMEM = { "\x1b""[2J" };

const char UHOME[] PROGMEM = { "\x1b""[;H" };

const char UCUR_HIDE[] PROGMEM = { "\x1b""[?25l" };
const char UCUR_SHOW[] PROGMEM = { "\x1b""[?25h" };

const char U_ATTR_OFF[] PROGMEM = { "\x1b""[m" };



void tr_cursor_show( uint8_t show ) {
	if(show) uart_puts_P( UCUR_SHOW );
	else uart_puts_P( UCUR_HIDE );
}


void tr_cls(uint8_t cur_onoff) {

	uart_puts_P( U_ATTR_OFF );
	tr_cursor_show(cur_onoff);
	uart_puts_P( UCLS );

	uart_puts_P( UHOME );

}


void fill_line( char ascii, uint8_t cnt ) {
	for(uint8_t i=0; i<cnt; i++) uart_putc( ascii );
}


void tr_attr( uint8_t atr, uint8_t fg, uint8_t bg ) {
	uart_putc( 0x1b );		// <ESC>[0;32;44m
	uart_putc( '[' );
	uart_putc( atr+'0' );
	uart_putc( ';' );
	uart_putc( '3' );
	uart_putc( fg+'0' );
	uart_putc( ';' );
	uart_putc( '4' );
	uart_putc( bg+'0' );
	uart_putc( 'm' );
}


void tr_pen_color( uint8_t cl ) {
	uart_putc( 0x1b );		// <ESC>[34m
	uart_putc( '[' );
	uart_putc( '3' );
	uart_putc( cl+'0' );		//sklejanie ASCII
	uart_putc( 'm' );
}

void tr_brush_color( uint8_t cl ) {
	uart_putc( 0x1b );		// <ESC>[44m
	uart_putc( '[' );
	uart_putc( '4' );
	uart_putc( cl+'0' );
	uart_putc( 'm' );
}


void tr_locate( uint8_t y, uint8_t x ) {

	uart_putc( 0x1b );	// <ESC>[y;xH
	uart_putc( '[' );
	uart_putint( y, 10 );
	uart_putc( ';' );
	uart_putint( x, 10 );
	uart_putc( 'H' );
}

void tr_create_win() {
	tr_attr(0, BLUE, YELLOW);
	//lewa ramka
	tr_locate(2, 0);
	uart_puts("  ");
	tr_locate(3, 0);
	uart_puts("  ");
	tr_locate(4, 0);
	uart_puts("  ");
	//prawa ramka
	tr_locate(2, 34);
	uart_puts("  ");
	tr_locate(3, 34);
	uart_puts("  ");
	tr_locate(4, 34);
	uart_puts("  ");

}
