#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#define F_CPU 8000000UL
#define yellow_time_big 6
#define yellow_time_little 3
#define time_big 28
#define time_little 14


int main(void)
{
	char time = 0;
	char i;
	cli();
	DDRB = 0b11111100;
	DDRD = 0b0000000;
	PORTD |= 1 << PD2;
	char greentime = 0;
	char yellowtime = 0;
	
	while(1) {
		i = PIND;
		if(i & (1<<PD2)) {
			time = time_big;
			yellowtime = yellow_time_big; 
		}
		else {
			time = time_little;
			yellowtime = yellow_time_little; 
		}
		greentime = time - 2 * yellowtime;

		PORTB |= 1 << PB2; //зажечь 1 красный

		PORTB |= 1 << PB7; //зажечь 2 зеленый

		for(i = 0; i < greentime; i++) {
			_delay_ms(250);
			_delay_ms(250);
		}

		for(i=0; i < 3; i++) { //мигаем 2 зел 3 с
			PORTB |= 1 << PB7;
			_delay_ms(250);
			_delay_ms(250);	
			PORTB &= ~(1<< PB7);
			_delay_ms(250);	
			_delay_ms(250);			
		}

		PORTB |= 1 << PB6; //зажечь 2 желтый
		for(i = 0; i < yellowtime; i++) {
			_delay_ms(250);
			_delay_ms(250);
		}

		PORTB &= ~(1<< PB2); //гасим 1 красный

		PORTB &= ~(1<< PB6); //гасим 2 желтый

		PORTB |= 1 << PB5; //зажечь 2 красный

		PORTB |= 1 << PB4; //зажечь 1 зеленый
		for(i = 0; i < greentime; i++) {
			_delay_ms(250);
			_delay_ms(250);
		}

		for(i=0; i < 3; i++) { //мигаем 3 с
			PORTB |= 1 << PB4;
			_delay_ms(250);
			_delay_ms(250);	
			PORTB &= ~(1<< PB4);
			_delay_ms(250);	
			_delay_ms(250);			
		}

		PORTB |= 1 << PB3; //зажечь 1 желтый
		for(i = 0; i < yellowtime; i++) {
			_delay_ms(250);
			_delay_ms(250);
		}

		PORTB &= ~(1<< PB3); //гасим 1 желтый

		PORTB &= ~(1<< PB5); //гасим 2 красный
	}

}
