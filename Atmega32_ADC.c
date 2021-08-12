/*
 * AVRGCC4.c
 *
 * Created: 03-07-2020 14:47:17
 *  Author: user
 */ 
#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

int calculateADC();
void setupADC(int x);
void setPin(char port,int pin,int state);
void digitalWrite(char port,int pin,int state);

void setupADC(int x){
	ADCSRA |= (1<<ADEN)|(1<<ADATE)|(1<<ADIE)|(1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0); //free running, 128 PRESCALAR
	ADMUX |= (1<<REFS0); //ADC0,LEFT JUSTIFIED,REF 5V
	switch (x)
	{
		case 0:
			ADMUX=0x40;
			break;
		case 1:
			ADMUX=0x41;
			break;
		case 2:
			ADMUX=0x42;
			break;
		case 3:
			ADMUX=0x43;
			break;
		case 4:
			ADMUX=0x44;
			break;
		case 5:
			ADMUX=0x45;
			break;
		case 6:
			ADMUX=0x46;
			break;
		case 7:
			ADMUX=0x47;
			break;	
		default:
			ADMUX=0x40;				
	}
	ADCSRA |= 1<<ADSC; //START CONVERSION
	sei();
//	while(ADCSRA & (1<<ADSC)); //Wait for A/D Conversion to complete;
}

int calculateADC(){
  int ADCval = ADCL;
  ADCval = (ADCH << 8) + ADCval;  // ADCH is read so ADC can be updated again
  return ADCval;
}

ISR(ADC_vect){
	if(calculateADC() > 700){
		digitalWrite('B',7,1); 
		_delay_ms(1000);
		digitalWrite('B',7,0);	
	}			
}

void setPin(char port,int pin,int state) //port=A,B,C,D. pin 0-7. state 0 or 1.
{  
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

void digitalWrite(char port,int pin,int state) //port=A,B,C,D. pin 0-7. state 0 or 1.
{ 
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
	setupADC(0);
	while(1)
	{
		digitalWrite('B',7,0);	
	}	
}
