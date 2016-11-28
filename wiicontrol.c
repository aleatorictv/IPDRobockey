#include "helpers.h"
#include "wiicontrol.h"
#include "CONFIG.h"

int blobs[12] ={0,0,0,0,0,0,0,0,0,0,0,0};
POINT *currentPos=NULL;
char buff[100];
	
POINT *locateBot(){
	if (m_wii_read(blobs)) {
		sprintf(buff, "%d %d %d %d %d %d %d %d\n", blobs[0], blobs[1],blobs[3],blobs[4],blobs[6],blobs[7],blobs[9],blobs[10]);
		sendBuffer(buff);
		POINT *newPos = findPos(blobs);
		//sprintf(buff, "x: %d, y: %d\n", newPos->x, newPos->y);
		//sendBuffer(buff);
		//if(newPos != NULL){
			if(currentPos != NULL) free(currentPos);
			currentPos = initPoint(newPos->x, newPos->y);
			//currentPos = newPos;
			if(DEBUG_POINT && DEBUG_ON){
				sprintf(buff, "x: %d, y: %d\n", currentPos->x, currentPos->y);
				sendBuffer(buff);
				
			}
			
		//}
	}
	return currentPos;
}