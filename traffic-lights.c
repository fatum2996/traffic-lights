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

		PORTB |= 1 << PB2; //������ 1 �������

		PORTB |= 1 << PB7; //������ 2 �������

		for(i = 0; i < greentime; i++) {
			_delay_ms(250);
			_delay_ms(250);
		}

		for(i=0; i < 3; i++) { //������ 2 ��� 3 �
			PORTB |= 1 << PB7;
			_delay_ms(250);
			_delay_ms(250);	
			PORTB &= ~(1<< PB7);
			_delay_ms(250);	
			_delay_ms(250);			
		}

		PORTB |= 1 << PB6; //������ 2 ������
		for(i = 0; i < yellowtime; i++) {
			_delay_ms(250);
			_delay_ms(250);
		}

		PORTB &= ~(1<< PB2); //����� 1 �������

		PORTB &= ~(1<< PB6); //����� 2 ������

		PORTB |= 1 << PB5; //������ 2 �������

		PORTB |= 1 << PB4; //������ 1 �������
		for(i = 0; i < greentime; i++) {
			_delay_ms(250);
			_delay_ms(250);
		}

		for(i=0; i < 3; i++) { //������ 3 �
			PORTB |= 1 << PB4;
			_delay_ms(250);
			_delay_ms(250);	
			PORTB &= ~(1<< PB4);
			_delay_ms(250);	
			_delay_ms(250);			
		}

		PORTB |= 1 << PB3; //������ 1 ������
		for(i = 0; i < yellowtime; i++) {
			_delay_ms(250);
			_delay_ms(250);
		}

		PORTB &= ~(1<< PB3); //����� 1 ������

		PORTB &= ~(1<< PB5); //����� 2 �������
	}

}
