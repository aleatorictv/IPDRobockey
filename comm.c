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
int canRotate = FALSE;
int commTest = FALSE;

void commtestoff(){
	commTest=FALSE;
}
int isCommTest(){
	return commTest;
}
int isRotate(){
	return canRotate;
}
int playing(){
	if(NEED_COMM){	//if RF is needed then its a real test otherwise just run
		return canPlay;
	}else return TRUE;
}
void parseComm(){
	m_rf_read(buffer,PACKET_LENGTH);
	for(int i=0;i<PACKET_LENGTH;i++){
		switch(buffer[i]){
			case 0xA0:
				commTest=TRUE;
				canPlay = FALSE;
				break;
			case 0xA1:
				canPlay = TRUE;
				break;
			case 0xA2:
			case 0xA4:
			case 0xA6:
			case 0xA7:
				canPlay=FALSE;
				break;
		}
	}
	if(canPlay){
		m_red(OFF);
	}else{
		m_red(ON);
	}
}
void initComm(){
	m_rf_open(CHANNEL,RXADDRESS,PACKET_LENGTH); //configure m_rf
}
void reopenComm(){
	m_rf_open(1,0x60,PACKET_LENGTH); //configure m_rf
}