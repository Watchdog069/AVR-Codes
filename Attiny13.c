/*
 * AVRGCC7_Attiny13.c
 *
 * Created: 08-09-2020 19:11:46
 *  Author: user
 */ 

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

void setPin(int pin,int state){  //portB pin 0-7. state 0 or 1.
	if(state)
		DDRB |= (1<<pin);
	else 
		DDRB &=	~(1<<pin);
}

void digitalWrite(int pin,int state){  //portB pin 0-7. state 0 or 1.
	if(state)
		PORTB |= (1<<pin);
	else 
		PORTB &= ~(1<<pin);
		
}

void setupADC(int x){
	ADCSRA |= (1<<ADEN)|(1<<ADATE)|(1<<ADIE)|(1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0); //free running, 128 PRESCALAR
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
		default:
			ADMUX=0x40;				
	}
	ADCSRA |= 1<<ADSC; //START CONVERSION
	sei();  //enable interrupts
}

ISR(ADC_vect){
	if(calculateADC()<500)
		digitalWrite(1,1);
}	

int calculateADC(){
  int ADCval = ADCL;
  ADCval = (ADCH << 8) + ADCval;  // ADCH is read so ADC can be updated again
  return ADCval;
}

ISR(INT0_vect){
	
}


void pwm(int pin,int num){
	TCCR0B |= (1<<CS01)|(1<<CS00);//prescalar /64
	switch(pin){
		case 0:
			TCCR0A |= (1<<WGM01)|(1<<WGM00)|(1<<COM0A1);//fast pwm, non inverted
			setPin(0,1);
			OCR0A=num;
			break;
		case 1:
			TCCR0A |= (1<<WGM01)|(1<<WGM00)|(1<<COM0B1);//fast pwm, non inverted
			setPin(1,1);
			OCR0B=num;		
			break;		
	}				
}

int main(void)
{
	setupADC(2);
	setPin(1,1);
    while(1)
    {
		digitalWrite(1,0);
		pwm(0,(255-calculateADC()/4));
		_delay_ms(10);
			//TODO:: Please write your application code 
    }	
}
