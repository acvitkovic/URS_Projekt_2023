#include "game.h"

#define F_CPU 7372800UL

#include<util/delay.h>
#include<stdlib.h>

#include "lcd.h"

void writeADCtoLCD(uint16_t adcvalue){
	char adcstring[16];
	itoa(adcvalue, adcstring, 10);
	lcd_clrscr();
	lcd_puts(adcstring);
}

int game1(){
	// this game uses muscle sensor for 2 players competing
	lcd_clrscr();
	lcd_puts("Muscle Test");
	_delay_ms(5000);
	
	int score = 0;
	int player1 = 100;
	int player2 = 100;
	
	uint16_t max1 = 0;
	uint16_t max2 = 0;
	
	ADMUX = _BV(REFS0);
	ADCSRA = _BV(ADEN) | _BV(ADPS1) | _BV(ADPS2);
	
	lcd_clrscr();
	lcd_puts("Player 1 Ready");
	_delay_ms(10000);
	
	while(player1){
		player1--;
		ADCSRA |= _BV(ADSC);
		while(!(ADCSRA & _BV(ADIF)));
		if(ADC > max1){
			max1 = ADC;
		}
		writeADCtoLCD(ADC);
		_delay_ms(100);
	}
	
	lcd_clrscr();
	lcd_puts("Player 2 Ready");
	_delay_ms(10000);
	
	while(player2){
		player2--;
		ADCSRA |= _BV(ADSC);
		while(!(ADCSRA & _BV(ADIF)));
		if(ADC > max2){
			max2 = ADC;
		}
		writeADCtoLCD(ADC);
		_delay_ms(100);
	}
	
	lcd_clrscr();
	
	if(max1 > max2){
		score++;
		lcd_puts("Point for P1");
	}else if(max2 > max1){
		score--;
		lcd_puts("Point for P2");
	}else{
		lcd_puts("No points");
	}
	
	_delay_ms(2000);
	lcd_clrscr();
	lcd_puts("Choose game");
	
	return score;
}

int game2(){
	int score = 0;
	return score;
}
