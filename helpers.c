#include <Math.h>

char buff[100];

POINT *initPoint(int x,int y){
	POINT *pt = (POINT *) malloc(sizeof(POINT));
	pt->x = x;
	pt->y = y;
	return pt;
}
float distance(float x1,float y1,float x2,float y2){
	return sqrt(pow(x2-x1,2) + pow(y2-y1,2));
}
float scale(float x, float in_min, float in_max, float out_min, float out_max){
	return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}
float angleBtwn(POINT *p1, POINT *p2){
	int v1[] = {p1->x, p1->y};
	int v2[] = {p2->x, p2->y};
	float _th = acos(dotprod(*v1,*v2)/sqrt(dotprod(*v1,*v1) * dotprod(*v2,*v2)));
	if(p2->x > p1->x) _th = -_th; 
	return _th;
}
int dotprod(int *v1, int *v2){
	return v1[0]*v1[0] + v2[1]*v2[1];
}
float dotprodF(float *f1, float *f2){
	return f1[0]*f1[0] + f2[1]*f2[1];
}
void sendBuffer(char *buff){
	for(int i=0;i<strlen(buff);i++) m_usb_tx_char(*(buff+1));
}
void sendFloat(float f){
	sprintf(buff,"%.3f\n",f);
	sendBuffer(buff);
}