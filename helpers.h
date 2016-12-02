#ifndef helpers__
#define helpers__
#include <stdlib.h>
#include <stdio.h>


typedef struct POINT {
	int x;
	int y;
	float theta;
} POINT;
double sqroot(double square);
POINT *initPoint(int x, int y);
float distancePT(POINT *p1, POINT *p2);
float distance(int x1, int y1, int x2, int y2);
float distanceF(float x1,float y1,float x2,float y2);
float scale(float x, float in_min, float in_max, float out_min, float out_max);
long dotprod(long v1[], long v2[]);
float dotprodF(long f1[], long f2[]);
float angleBtwn(int v1[], int v2[]);
//float angleBtwn(POINT* p1, POINT* p2);
float angleBtwnF(float *pf1, float *pf2);
float smallestTh(float th1, float th2);
void sendBuffer(char *buff);
void sendFloat(float f);

#endif