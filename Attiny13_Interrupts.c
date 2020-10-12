/*
 * AVRGCC8_attiny13Interrupt.c
 *
 * Created: 08-10-2020 22:31:09
 *  Author: user
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#define F_CPU 9600000

void setPin(int pin,int state){  //port=A,B,C,D. pin 0-7. state 0 or 1.	
	if(state==1)
		DDRB |= (1<<pin);
	else 
		DDRB &=	~(1<<pin);
}

void digitalWrite(int pin,int state){  //port=A,B,C,D. pin 0-7. state 0 or 1.	
	if(state==1)
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


int calculateADC(){
  int ADCval = ADCL;
  ADCval = (ADCH << 8) + ADCval;  // ADCH is read so ADC can be updated again
  return ADCval;
}

ISR(INT0_vect){  //ISR
	digitalWrite(3,1);	//turn pump on, on fire
	digitalWrite(2,1);	//on off the buzzer 
	_delay_ms(500);
	digitalWrite(2,0);
	_delay_ms(200);
}

int main(void)
{
	setPin(3,1);  //pump as output(pb3)
	setPin(2,1);  //buzzer as o/p (pb2)
	setPin(0,1);  //led lights as o/p (pb0)
	setupADC(2);  //ldr to adc2(pb4) 
	//MQ2 out connected to INT0 (pb1)
	GIMSK |= (1<<INT0); //enable interrupt0 , NOTE that MCUCR is not used here since on power-on default is low level of INT0 is set.
	//Gas sensor generates low level output on detection, so low level triggered interrupts
	
	while(1)
    {
		digitalWrite(2,0); //turn off buzzer and pump at normal conditions
		digitalWrite(3,0); 
		if(calculateADC()<900) //on sunlight, turn on relay (basically turning on or off relay is decided by whether you connect load to NC or NO of relay)
			digitalWrite(0,1);
		else
			digitalWrite(0,0);	
        //TODO:: Please write your application code 
    }
}
