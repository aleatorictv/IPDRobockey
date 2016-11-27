#include "comm.h"
#include "helpers.h"
#include "CONFIG.h"

char buffer[PACKET_LENGTH] = {0,0,0,0,0,0,0,0,0,0};

char commtest = 0xA0;
char play = 0xA1;
char pause = 0xA4;
char halftime = 0xA6;
char gameover = 0xA7;

int canPlay = FALSE;

int playing(){
	if(NEED_COMM){
		return canPlay;
	}else return TRUE;
}
void parseComm(){
	m_rf_read(buffer,PACKET_LENGTH);
	m_green(TOGGLE);

	if(buffer[0]==commtest){
		canPlay=FALSE;
		//make LED blink
	}

	else if(buffer[0]==play){
		canPlay = TRUE;
	}

	// else if(buffer[0]==goalr[0] && buffer[1]==goalr[1] && buffer[2]==goalr[2]){
	// 	//adjust strategy depending on score
	// }

	// else if(buffer[0]==goalb[0] && buffer[1]==goalb[1] && buffer[2]==goalb[2]){
	// 	//adjust strategy depending on score
	// }

	else if(buffer[0]==pause){
		canPlay = FALSE;
		
	}

	else if(buffer[0]==halftime){
		//turn motor off or cut power
		canPlay = FALSE;
	}

	else if(buffer[0]==gameover){
		//turn motor off or cut power
		canPlay = FALSE;
	}
}
void initComm(){
	m_bus_init(); //enable mBUS
	m_rf_open(CHANNEL,RXADDRESS,PACKET_LENGTH); //configure m_rf
	canPlay = FALSE;

	set(DDRB,6); // set pin b6 as output
	set(DDRB,5); //set pinb5 as output
}