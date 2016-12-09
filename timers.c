#include "m_general.h"
#include "timers.h"
#include "CONFIG.h"

void initTimer0(){ //puck finding timer 750Hz
	float freq = SYSCLOCK/1024.;
	set(TCCR0B,CS02);//timer 1 /1024 = 16kHz
	clear(TCCR0B,CS01);
	set(TCCR0B,CS00);
	
	clear(TCCR0B,WGM02); // Up to OCR0A
	set(TCCR0A,WGM01);
	clear(TCCR0A,WGM00);
	
	OCR0A = freq/PUCKFREQ; //PUCKFREQ = 5 > polls at 750Hz
	
	set(TIMSK0,OCIE0A ); //comparison interrupt up
	
}
void initTimer1(){	//motor PWM timer uses built in compare pins B5/B6
	set(TCCR1B,CS12);//timer 1 /256 = 62.5kHz
	clear(TCCR1B,CS11);
	clear(TCCR1B,CS10);
	clear(TCCR1B,	WGM13); //set mode 5 Up to 0x00FF, PWM freq = /256 > 244Hz
	set (TCCR1B,	WGM12);
	clear(TCCR1A,	WGM11);
	set (TCCR1A,	WGM10);
	
	//OCR1X = 0 > 0% duty, =255 > 100% duty
	set(TCCR1A,COM1A1);	//B5 sets at OCR1A, clear at rollover
	clear(TCCR1A,COM1A0);
	set(TCCR1A,COM1B1);//B6 sets at OCR1B, clear at rollover
	clear(TCCR1A,COM1B0);	
}
void initTimer3() {
	float freq;

	// set prescaler to /1024
	set(TCCR3B,CS32);
	clear(TCCR3B,CS31);
	set(TCCR3B,CS30);
	freq = SYSCLOCK/1024.;  //timer at 15.625kHz

	// set timer mode 4 up to OCR3A 
	clear(TCCR3B,WGM33);
	set(TCCR3B,WGM32);
	clear(TCCR3A,WGM31);
	clear(TCCR3A, WGM30);

	OCR3A =  freq/WIIFREQ;  //WIIFREQ =200 > poll at 75Hz

	set(TIMSK3,OCIE3A);//compare to OCR3A
}

void initTimer4(){
	
}