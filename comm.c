#include "CONFIG.h"
#include "helpers.h"
#include "comm.h"

char commtest = 0xA0;
char play = 0xA1;
char pause = 0xA4;
char halftime = 0xA6;
char gameover = 0xA7;

char buffer[PACKET_LENGTH] = {0,0,0,0,0,0,0,0,0,0};
int canPlay = FALSE;

int playing(){
	if(NEED_COMM){	//if RF is needed then its a real test otherwise just run
		return canPlay;
	}else return TRUE;
}
void parseComm(){
	m_rf_read(buffer,PACKET_LENGTH);
	
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
	}else{
		canPlay=FALSE;
	}
	
	if(canPlay){
		m_red(OFF);
		m_green(ON);
	}else{
		m_green(OFF);
		m_red(ON);
	}
}
void initComm(){
	m_rf_open(CHANNEL,RXADDRESS,PACKET_LENGTH); //configure m_rf
	canPlay = FALSE;
}