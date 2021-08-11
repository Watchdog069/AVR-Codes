/*
 * AVRGCC1.c
 *
 * Created: 03-07-2020 14:47:17
 *  Author: user
 */
#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

void setPin(char port,int pin,int state);
void digitalWrite(char port,int pin,int state);

void setPin(char port,int pin,int state){  //port=A,B,C,D. pin 0-7. state 0 or 1.
	switch(port){
		case 'A':
			if(state==1)
				DDRA |= (1<<pin);
			else
				DDRA &= ~(1<<pin);
			break;
		case 'B':
			if(state==1)
				DDRB |= (1<<pin);
			else
				DDRB &=	~(1<<pin);
			break;
		case 'C':
			if(state==1)
				DDRC |= (1<<pin);
			else
				DDRC &=	~(1<<pin);
			break;
		case 'D':
			if(state==1)
				DDRD |= (1<<pin);
			else
				DDRD &=	~(1<<pin);
			break;
		default:
			DDRB=0xFF;
			PORTB=0xFF;
	}
}

void digitalWrite(char port,int pin,int state){  //port=A,B,C,D. pin 0-7. state 0 or 1.
	switch(port){
		case 'A':
			if(state)
				PORTA |= (1<<pin);
			else
				PORTA &= ~(1<<pin);
			break;
		case 'B':
			if(state)
				PORTB |= (1<<pin);
			else
				PORTB &= ~(1<<pin);
			break;
		case 'C':
			if(state)
				PORTC |= (1<<pin);
			else
				PORTC &= ~(1<<pin);
			break;
		case 'D':
			if(state)
				PORTD |= (1<<pin);
			else
				PORTD &= ~(1<<pin);
			break;
		default:
			DDRB=0xFF;
			PORTB=0xFF;
	}
}

int main(void)
{
	setPin('B',7,1);
	int state=0;
    while(1)
    {
		digitalWrite('B',7,state);
		_delay_ms(250);
		state=!state;
    }
}
