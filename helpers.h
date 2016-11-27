#ifndef helpers__
#define helpers__
#include <stdlib.h>
#include <stdio.h>
#include "m_usb.h"


typedef struct POINT {
	int x;
	int y;
	float theta;
} POINT;

typedef struct POINTF {
	float x;
	float y;
	float theta;
} POINTF;
POINT *initPoint(int x, int y);
float distance(float x1,float y1,float x2,float y2);
float scale(float x, float in_min, float in_max, float out_min, float out_max);
int dotprod(int *v1, int *v2);
float dotprodF(float *f1, float *f2);
float angleBtwn(POINT *p1, POINT *p2);
float angleBtwnF(float *pf1, float *pf2);
void sendBuffer(char *buff);
void sendFloat(float f);

#endif