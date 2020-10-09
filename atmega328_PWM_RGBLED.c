/*
 * AVRGCC7_RGBLED.c
 *
 * Created: 05-10-2020 21:33:29
 *  Author: user
 */ 

#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
#define F_CPU 16000000
#define RAND_MAX 255

void setPin(char port,int pin,int state){  //port=A,B,C,D. pin 0-7. state 0 or 1.
	switch(port){
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


void pwm(int pin,int num){
	TCCR0B |= (1<<CS00)|(1<<CS01);//prescalar /64
	TCCR2B |= (1<<CS20)|(1<<CS21);//prescalar /64
	switch(pin){
		case 0:
			TCCR0A |= (1<<WGM01)|(1<<WGM00)|(1<<COM0A1);//fast pwm, non inverted
			setPin('D',6,1);
			OCR0A=num;
			break;
		case 1:
			TCCR0A |= (1<<WGM01)|(1<<WGM00)|(1<<COM0B1);//fast pwm, non inverted
			setPin('D',5,1);
			OCR0B=num;		
			break;	
		case 2:
			TCCR2A |= (1<<WGM21)|(1<<WGM20)|(1<<COM2A1);//fast pwm, non inverted
			setPin('B',3,1);
			OCR2A=num;
			break;
		case 3:
			TCCR2A |= (1<<WGM21)|(1<<WGM20)|(1<<COM2B1);//fast pwm, non inverted
			setPin('D',3,1);
			OCR2B=num;		
			break;			
	}				
}
int main(void)
{
    int i=0;
    while(1)
    {
		int x=rand();
		int y=rand();
		int z=rand();
		pwm(0,x);
		pwm(1,y);
		pwm(2,z);
		_delay_ms(1000);
		//TODO:: Please write your application code 
    }
    return 0;
}
