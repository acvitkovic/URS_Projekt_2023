#define F_CPU 7372800UL

#include <avr/io.h>
#include <util/delay.h>
#include "lcd.h"

int main(void)
{
	DDRB = 0x00;
	PORTB = 0x0f;
	
   	DDRD = _BV(4);

   	TCCR1A = _BV(COM1B1) | _BV(WGM10);
   	TCCR1B = _BV(WGM12) | _BV(CS11);
   	OCR1B = 128;

   	lcd_init(LCD_DISP_ON);
   	lcd_clrscr();
   	
   	lcd_puts("Choose game");
}

