/*
 * main.c
 *
 *  Created on: 18 kwi 2017
 *      Author: Daniel
 */


#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#include "MPR121/mpr121.h"
#include "I2C_TWI/i2c_twi.h"
#include "LED/led.h"

void led_init(void);


int main(void)
{
	i2cSetBitrate(100);
	MPR121_init();
	led_init();

   unsigned char states = 0;
   uint8_t led1_flag = 0;
   uint8_t led2_flag = 0;
   uint8_t led3_flag = 0;

   sei();		// zezwolenie na przerwania

   while(1)
   {
       states = MPR121_read(ELE_L);
       states &= 0x0F;

       if(states & 0x01)
       {
    	   _delay_ms(80);
    	   if(states & 0x01)
    	   {
        	   if(led1_flag == 0)
        	   {
        		   LED1_ON;
        		   led1_flag = 1;
        	   }
        	   else
        	   {
        		   LED1_OFF;
        		   led1_flag = 0;
        	   }
    	   }
       }
       if(states & 0x02)
       {
    	   _delay_ms(80);
    	   if(states & 0x02)
    	   {
         	   if(led2_flag == 0)
         	   {
         		   LED2_ON;
         		   led2_flag = 1;
         	   }
         	   else
         	   {
         		   LED2_OFF;
         		   led2_flag = 0;
         	   }
    	   }
        }
       if(states & 0x04)
       {
    	   _delay_ms(80);
    	   if(states & 0x04)
    	   {
         	   if(led3_flag == 0)
         	   {
         		   LED3_ON;
         		   led3_flag = 1;
         	   }
         	   else
         	   {
         		   LED3_OFF;
         		   led3_flag = 0;
         	   }
    	   }
        }
       _delay_ms(100);
   };
}

//TODO: obsluga przerwania INT0 -> IRQ. ULEPSZENIE
