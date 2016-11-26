#ifndef motorcontrol__
#define motorcontrol__
#include "helpers.h"

void initMotors();
void moveBots(POINT *p);
void stop();
void setMotors(int L, int R);
#endif