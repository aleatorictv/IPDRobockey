/*

qualifying test

*/

#define F_CPU 16000000
#include "m_general.h"
#include "m_bus.h"
#include "m_bus.c"
#include "m_usb.h"
#include "m_usb.c"
#include "m_wii.h"
#include "m_wii.c"
#include "m_rf.h"
#include "m_rf.c"

#include "CONFIG.h"

#include "localization.h"
#include "helpers.h"
#include "timers.h"
#include "wiicontrol.h"
#include "targeting.h"
#include "comm.h"
#include "motorcontrol.h"
#include "puckfinding.h"

#include "localization.c"
#include "helpers.c"
#include "timers.c"
#include "wiicontrol.c"
#include "targeting.c"
#include "comm.c"
#include "motorcontrol.c"
#include "puckfinding.c"

POINT *goalPos = NULL;
POINT *robotPos = NULL;
POINT *gotoPos = NULL;
volatile int wii_flag = 0;
volatile int comm_flag = 0;
volatile int puck_flag = 0;
int puck=0;
int c = 0; //count a bunch of times of wii timer to reopen comm interval

void init();

int main(void)
{
	init();
	while (1)
	{
		if(comm_flag){
			parseComm();
			comm_flag = 0;
			
		}
		if(wii_flag){
			robotPos = locateBot();
			wii_flag = 0;
		}
		if(puck_flag){
			puck = 0;// findPuck();
			puck_flag = 0;
		}
		gotoPos = setTarget(goalPos,robotPos,puck);
		if(playing()){
			moveBots(gotoPos);	//repurpose POINT struct for dist/rotation variable
			if(TEST_FWD) setMotors(100,100);
			if(TEST_BKD) setMotors(-255,-255);
		}
		else stop();
		
	}
}
void init(){
	m_clockdivide(0);
	sei();
	m_green(ON);
	if(DEBUG_ON){
		m_usb_init();
		m_usb_tx_string("USB connected.\n");
	}
	initMotors();
	initTimer0();
	initTimer1();
	initTimer3();
	initADC();
	if(NEED_WII){
		while(!m_wii_open()){
			m_red(ON);
		}
		m_red(OFF);
	}
	if(NEED_COMM)	initComm();
	
	m_wait(800);
	m_green(OFF);
	if(FULLCOURT){
		if(AIM_RIGHT) goalPos = initPoint(1000,CENTER_Y);
		else goalPos = initPoint(0,CENTER_Y);
		}else if(FIND_CTR){
			goalPos = initPoint(CENTER_X,CENTER_Y);  //debug to go to center ice
		}else if(QUALIFYING){
		robotPos = locateBot();
			if(robotPos->x < CENTER_X){
				goalPos = initPoint(950,CENTER_Y);
				}else{
				goalPos = initPoint(50,CENTER_Y);
			}
			m_usb_tx_string("initialize\n");
	}
	
}

ISR( TIMER0_COMPA_vect){  //check puck at timer0
	puck_flag=1;
}
ISR(TIMER3_COMPA_vect){ //check wii at timer3
	 wii_flag=1;	//if comm flag is on, don't run wii check
	c++;
	if(c%100==0) {c=0;reopenComm();}	//reopen mRF less often 
	
}
ISR(INT2_vect){	//mRF flag
	comm_flag=1;
}
ISR(ADC_vect){  //clear ADIF flag automatically
	
}
