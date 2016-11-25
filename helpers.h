#ifndef helpers__
#define helpers__
#include <stdlib.h>
#include <stdio.h>
#include "m_usb.h"

float distance(float x1,float y1,float x2,float y2);
void sendBuffer(char *buff);
void sendFloat(float f);

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

#endif