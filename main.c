/*

ROBOCOKEY GO CODE WIN ! 

James = Software
Gaute = Build
Michael = Wildcard

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
#include "gameday.h"

#include "localization.c"
#include "helpers.c"
#include "timers.c"
#include "wiicontrol.c"
#include "targeting.c"
#include "comm.c"
#include "motorcontrol.c"
#include "puckfinding.c"
#include "gameday.c"

POINT *goalPos = NULL;
POINT *robotPos = NULL;
POINT *gotoPos = NULL;
int *puck=NULL;
volatile int wii_flag = 0;
volatile int comm_flag = 0;
volatile int puck_flag = 0;
int c = 0; //count a bunch of times of wii timer to reopen comm interval
int rotate = 0;
char buff[100];
int ct =0;
int start =0;
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
			m_green(TOGGLE);
			if(NEED_WII) robotPos = locateBot();
			wii_flag = 0;
		}
		if(puck_flag){
			puck = findPuck();
			puck_flag = 0;
		}
		
		
		if(gotoPos!=NULL) free(gotoPos);
		gotoPos = initPoint(0,0);
		//gotoPos = setTarget(goalPos,robotPos,puck);
		gotoPos = dance(goalPos,robotPos,puck);
		if(playing()){
			if(!start)start=1;
			moveBots(gotoPos);	//repurpose POINT struct for dist/rotation variable
			if(TEST_FWD) setMotors(255,255);
			if(TEST_BKD) setMotors(-255,-255);
			if(TEST_TURN) setMotors(255,-255);
		}
		else stop();
	}
}
void reset(){
	POINT *rob = initPoint(0,0);
	rob = locateBot();
	if(rob!= NULL) robotPos = rob;
	else stop();
	
	if(robotPos->x < 0){
		goalPos = initPoint(300,0);
		m_usb_tx_string("initialize L\n");
		}else{
		goalPos = initPoint(-300,0);
		m_usb_tx_string("initialize R\n");
	}
}
void init(){
	m_clockdivide(0);
	sei();
	m_green(ON);
	if(DEBUG_ON){
		m_usb_init();
		//m_usb_tx_string("USB connected.\n");
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
	initComm();
	
	m_wait(800);
	m_green(OFF);
	robotPos = initPoint(0,0);
	gotoPos= initPoint(0,0);
	
	initLEDs();
	if(GAMETIME){
		if(AIM_EAST) goalPos = initPoint(0,300);
		else goalPos = initPoint(0,-300);
		if(TEAM_SW) {
			//sprintf(buff,"%d \n",check(PINB,0));
			//sendBuffer(buff);
			if(check(PINB,0)) {
				goalPos=initPoint(0,300);
				blueteam();
			}else{
				goalPos=initPoint(0,-300);
				//redteam();
				red(1);
			}
		}
	}else if(FIND_CTR){
		goalPos = initPoint(0,0);  //debug to go to center ice
	}
	else if(QUALIFYING){
		reset();
	}
	
}

ISR( TIMER0_COMPA_vect){  //check puck at timer0
	puck_flag=1;
}
ISR(TIMER3_COMPA_vect){ //check wii at timer3
	 wii_flag=1;	
		
	c++;
	if(c==100) {
		c=0;
		reopenComm();
		if(playing()) setT();
		else green(0);
		m_green(TOGGLE);
		if( isCommTest()&& ct<7){
			ct++;
			toggle(PORTB,2);//blink blue
			if(ct==4){
				ct=0;
				commtestoff();
			}
		}	//reopen mRF less often 
	}
}
ISR(INT2_vect){	//mRF flag
	if(NEED_COMM) comm_flag=1;
}
ISR(ADC_vect){  //clear ADIF flag automatically
	//updateADC() handles values of ADC
}
