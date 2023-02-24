#define F_CPU 7372800UL

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdio.h>

#include "lcd.h"

#include "game.h"

	int totalScore = 0;
	int score;
	uint8_t p1 = 0;
	uint8_t p2 = 0;

void debounce() {
	_delay_ms(100);
	GIFR = _BV(INTF0) | _BV(INTF1);
}

ISR(INT0_vect) {
	lcd_clrscr();

	char charScore1[2];
	char charScore2[2];
	
	lcd_puts("Player 1: ");
	sprintf(charScore1, "%d", p1);
	lcd_puts(charScore1);
	lcd_gotoxy(0, 1);
	
	lcd_puts("Player 2: ");
	sprintf(charScore2, "%d", p2);
	lcd_puts(charScore2);
	
	lcd_home();
	debounce();
}

ISR(INT1_vect){
	asm("jmp main");
	debounce();
}


int main(void)
{
	DDRB = 0x00;
	PORTB = 0x0f;

   	DDRD = _BV(4);

   	TCCR1A = _BV(COM1B1) | _BV(WGM10);
   	TCCR1B = _BV(WGM12) | _BV(CS11);
   	OCR1B = 128;
	   
	MCUCR = _BV(ISC01) | _BV(ISC11);
	GICR = _BV(INT0) | _BV(INT1);
	sei();

   	lcd_init(LCD_DISP_ON);
   	lcd_clrscr();
   	lcd_puts("Choose game");
	    
	while(1){	
		if(bit_is_clear(PINB, 0)){
			score = game1();
			totalScore = totalScore + score;
				if (score > 0){
					p1++;
				} else if (score < 0){
					p2++;
				}
		}else if(bit_is_clear(PINB, 1)){
			score = game2();
			totalScore = totalScore + score;
				if (score > 0){
					p1++;
				} else if (score < 0){
					p2++;
				}

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
			p1 = 0;
			p2 = 0;
			_delay_ms(1000);
			lcd_clrscr();
			lcd_puts("Choose game");
		}
	}
}

