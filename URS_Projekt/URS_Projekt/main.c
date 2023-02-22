#define F_CPU 7372800UL

#include <avr/io.h>
#include <util/delay.h>

#include "lcd.h"

#include "game.h"

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
	   
	int totalScore = 0;
	int score;
	
	   
	while(1){
		
		
		
		if(bit_is_clear(PINB, 0)){
			score = game1();
			totalScore = totalScore + score;
		}else if(bit_is_clear(PINB, 1)){
			score = game2();
			totalScore = totalScore + score;
		}else if(bit_is_clear(PINB, 2)){
			lcd_clrscr();
			if(totalScore > 0){
				lcd_puts("Player 1 wins");
			}else if(totalScore == 0){
				lcd_puts("Draw");
			}else{
				lcd_puts("Player 2 wins");
			}
			totalScore = 0;
			score = 0;
			_delay_ms(1000);
			lcd_clrscr();
			lcd_puts("Choose game");
		}
	}
}

