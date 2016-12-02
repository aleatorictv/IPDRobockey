
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "m_general.h"
#include "helpers.h"
#define MINDIFF 2.25e-308                   // use for convergence check

char buff[100];

POINT *initPoint(int x,int y){
	POINT *pt = (POINT *) malloc(sizeof(POINT));
	pt->x = x;
	pt->y = y;
	return pt;
}
double sqroot(double square)
{
	double root=square/3, last, diff=1;
	if (square <= 0) return 0;
	do {
		last = root;
		root = (root + square / root) / 2;
		diff = root - last;
	} while (diff > MINDIFF || diff < -MINDIFF);
	return root;
}
float distancePT(POINT *p1, POINT *p2) {
	//sprintf(buff,"Px Py %d %d %d ;\n",p1->x,p2->x,(p1->x-p2->x));
	//sendBuffer(buff);
	return sqrt(pow(p1->x-p2->x,2)+ pow(p1->y-p2->y,2));
}
float distance(int x1, int y1, int x2, int y2){
	//	sprintf(buff,"%d %d \n",x1,y12 );//,sqrt((x2-x1)*(x2-x1) +(y2-y1)*(y2-y1) ));
	//	sendBuffer(buff);
	return sqrt(pow(x2-x1,2) + pow(y2-y1,2) );
}
float distanceF(float x1,float y1,float x2,float y2){
	return sqrt(pow(x2-x1,2) + pow(y2-y1,2));
}
float scale(float x, float in_min, float in_max, float out_min, float out_max){
	return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}
float angleBtwn(int v1[], int v2[]){
	long v1L[2] = { v1[0] , v1[1]};
	long v2L[2] = { v2[0] , v2[1]};
	float th = acos(dotprodF(v1L,v2L)/sqrt(dotprodF(v1L,v1L) * dotprodF(v2L,v2L)));
	if(v1[0]>v2[0]) th = -th;
	//sprintf(buff,"dot prod  %.1f %.1f\n", dotprodF(v1L,v1L),dotprodF(v2L,v2L));
	//sendBuffer(buff);
	return th;
}

float smallestTh(float th1, float th2) {
	float theta = th1 - th2;
	if (theta > PI) {
		theta = -2*PI + theta;
		} else if (theta < -PI) {
		theta = 2*PI + theta;
	}
	sprintf(buff,"small %.2f %.2f %.2f\n",th1,th2,theta);
	sendBuffer(buff);
	return theta;
}
long dotprod(long v1[], long v2[]){
	return v1[0]*v2[0] + v1[1]*v2[1];
}
float dotprodF(long f1[], long f2[]){
	return f1[0]*f2[0]*1.f + f1[1]*f2[1]*1.f;
}
//void sendBuffer(char *buff){
//for(int i=0;i<strlen(buff);i++) m_usb_tx_char(*(buff+1));
//}
void sendBuffer(char *buf) {
	int i;
	for (i=0; i< strlen(buf); i++) {
		m_usb_tx_char(*(buf+i));
	}
}
void sendFloat(float f){
	sprintf(buff,"%.3f\n",f);
	sendBuffer(buff);
}