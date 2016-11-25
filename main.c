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
#include "localization.h"
#include "localization.c"
#include "helpers.h"
#include "helpers.c"
#include "parameters.h"
#include "timers.h"
#include "timers.c"
#include "wiicontrol.h"
#include "wiicontrol.c"
#include "targeting.h"
#include "targeting.c"
#include "comm.h"
#include "comm.c"

POINT *robotPos = NULL;
int wii_flag=0;
int comm_flag =0;

void init();

int main(void)
{
	init();
	while(!m_usb_rx_available()){}
	m_usb_init();
	while(!m_wii_open()){}
	while (1)
	{
		if(comm_flag){
			parseComm();
		}
		if(wii_flag){
			robotPos = locateBot();
			wii_flag=0;
		}
		setTarget();
		if(playing()){
		//moveBots();
		}
	}
}
void init(){
	m_clockdivide(0);
	sei();
	initTimer3();
	initComm();
}
ISR(TIMER3_COMPA_vect){
	wii_flag=1;
}
ISR(INT2_vect){
	comm_flag = 1;
}