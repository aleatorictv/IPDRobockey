#include "m_general.h"
#include "timers.h"
#include "CONFIG.h"

void initTimer1(){
	
}
void initTimer3() {
	float timer_freq;

	// set prescaler to /1024
	set(TCCR3B,CS32);
	clear(TCCR3B,CS31);
	set(TCCR3B,CS30);
	timer_freq = SYSCLOCK/1024;  //timer at 15.625kHz

	// set timer mode 4 up to OCR3A 
	clear(TCCR3B,WGM33);
	set(TCCR3B,WGM32);
	clear(TCCR3A,WGM31);
	clear(TCCR3A, WGM30);

	OCR3A =  timer_freq/WIIFREQ;  //WIIFREQ =10 > poll at 1.5kHz

	set(TIMSK3,OCIE3A);//compare to OCR3A
}