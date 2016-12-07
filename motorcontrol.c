#include "motorcontrol.h"
#include "helpers.h"
#include "CONFIG.h"

void initMotors(){
	set(DDRB,5); //pwm output pins
	set(DDRB,6);

	set(DDRB,4);  //direction pins, just outside pwm pins
	set(DDRC,6);
	set(PORTB, 4);	//Left motor dir pin
	set(PORTC, 6);	//right motor dir pin
}
void moveBots(POINT *p){
	//Point -> X = average power between motor
	//Point -> Y = difference between wheel speeds (speed of turn) 
	//					-Y =  L back/ R fwd  = CCW turn
	//					0 = L / R same dir
	//					+Y = L fwd / R back = CW turn
	int L = p->x ;
	int R = p->y;
	setMotors(L,R);

		
}
void stop()	{
	setMotors(0,0);
}

void setMotors(int L, int R){	//input duty cycles as signed ints
	if(L < 0) clear(PORTB , 4);	//left motor dir and duty cycle
	else set(PORTB,4);
	if(abs(L)>255) L=255;
	OCR1A = abs(L);
	
	if(R > 0) set(PORTC , 6); //right motor dir and duty cycle
	else clear(PORTC,6);
	if(abs(R)>255) R=255;
	OCR1B = abs(R);
}