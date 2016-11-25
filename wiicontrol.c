#include "helpers.h"
#include "wiicontrol.h"
#include "parameters.h"

int blobs[12] ={0,0,0,0,0,0,0,0,0,0,0,0};
POINT *currentPos=NULL;
	
POINT *locateBot(){
	if (m_wii_read(blobs)) {
		POINT *newPos = findPos(blobs);
		if(newPos != NULL){
			if(currentPos != NULL) free(currentPos);
			currentPos = newPos;
			if(DEBUG_POINT){
				sprintf(buff, "x: %d, y: %d\n", currentPos->x, currentPos->y);
				sendBuffer(buff);
			}
			return currentPos;
		}
	}
}