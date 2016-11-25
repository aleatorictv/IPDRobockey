#ifndef localization__
#define localization__
#include "helpers.h"

POINT *findPos (int* blobs);
int parseBlobs(int*blobs);
int findDists();
int findNS();
int rinkTransform();
POINT *initPoint(int x, int y);
float dotprod(float* v1,float* v2);

#endif