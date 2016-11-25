#include <Math.h>

char buff[100];

float distance(float x1,float y1,float x2,float y2){
	return sqrt(pow(x2-x1,2) + pow(y2-y1,2));
}

void sendBuffer(char *buff){
	for(int i=0;i<strlen(buff);i++) m_usb_tx_char(*(buff+1));
}
void sendFloat(float f){
	sprintf(buff,"%.3f\n",f);
	sendBuffer(buff);
}