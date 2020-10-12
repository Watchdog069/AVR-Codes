/*
 * AVRGCC7_ATTINY_ServoMotor.c
 *
 * Created: 29-09-2020 21:41:56
 *  Author: user
 */ 

#include <avr/io.h>
#include <util/delay.h>
#define F_CPU 9600000

void setPin(int pin,int state){  //port=A,B,C,D. pin 0-7. state 0(input) or 1(output).	
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

void pwm(int pin,int num){
	TCCR0B |= (1<<CS00)|(1<<CS01);//prescalar /64
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

void servo(int pin, int angle){      //prescalar was 64, so pwm freq is 9.6MHz/(256*64)=58.6hz.
	pwm(pin,(int)angle*0.2);  //180deg -> 36, so 36/180=0.2
}	
	
int main(void)
{
    while(1)
    {
		for(int i=0;i<=180;i++){
			servo(0,i);
			_delay_ms(20);
		}			
		for(int i=180;i>=0;i--){
			servo(0,i);
			_delay_ms(20);		
		}			
		//TODO:: Please write your application code 
    }
}
