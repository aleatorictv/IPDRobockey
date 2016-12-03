#include "puckfinding.h"
#include "helpers.h"
#include "CONFIG.h"

int puckState;
int lastPuck;
int hasPuck =0;
int front = 1;
int nearFront = 2;
int left = 3;
int right = 4;
int behind = 5;

int findPuck(){
	puckState = 0;
	return puckState;
}
void initADC(){
	
}