#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#define F_CPU 8000000UL
#define yellow_time 2
#define seconds_big 14
#define seconds_little 7
#define blink_time 3

int main(void)
{
	char seconds = 0;
	char i;
	cli();
	DDRB = 0b00011100;
	DDRD = 0b0000000;
	PORTD |= 1 << PD2;
	
	i = PIND;
	if(i & (1<<PD2))
		seconds = seconds_little;
	else
		seconds = seconds_big;
	while(1) {
		i = PIND;
		if(i & (1<<PD2))
			seconds = seconds_little;
		else
			seconds = seconds_big;
		PORTB |= 1 << PB2; //зажечь красный
		for(i = 0; i < seconds; i++) {
			_delay_ms(250);
			_delay_ms(250);
			_delay_ms(250);
			_delay_ms(250);
		}
		PORTB &= ~(1<< PB2); //гасим красный
		PORTB |= 1 << PB3; //зажечь желтый
		for(i = 0; i < yellow_time; i++) {
			_delay_ms(250);
			_delay_ms(250);
			_delay_ms(250);
			_delay_ms(250);
		}
		PORTB &= ~(1<< PB3); //гасим желтый

		PORTB |= 1 << PB4; //зажечь зеленый
		for(i = 0; i < seconds-blink_time; i++) {
			_delay_ms(250);
			_delay_ms(250);
			_delay_ms(250);
			_delay_ms(250);
		}
		for(i=0; i < blink_time; i++) { //мигаем 3 с
			PORTB |= 1 << PB4;
			_delay_ms(250);
			_delay_ms(250);	
			PORTB &= ~(1<< PB4);
			_delay_ms(250);	
			_delay_ms(250);			
		}
		PORTB |= 1 << PB3; //зажечь желтый
		for(i = 0; i < yellow_time; i++) {
			_delay_ms(250);
			_delay_ms(250);
			_delay_ms(250);
			_delay_ms(250);
		}
		PORTB &= ~(1<< PB3); //гасим желтый
	}

}
