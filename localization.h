#ifndef localization__
#define localization__
#include "helpers.h"

POINT *findPos (unsigned int* blobs);
void parsePoints(unsigned int *blobs, POINT **pts);
int parseBlobs(unsigned int*blobs);
int findDists();
int findNS();
int rinkTransform();
float distanceI(int x1, int y1, int x2, int y2);
POINT *initPoint(int x, int y);

#endif