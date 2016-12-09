#include "helpers.h"
#include "wiicontrol.h"
#include "CONFIG.h"

unsigned int blobs[12] ={0,0,0,0,0,0,0,0,0,0,0,0};
POINT *currentPos=NULL;
POINT *newPos = NULL;
char buff[100];
	
POINT *locateBot(){
	
	if (m_wii_read(blobs)) {
		if(newPos!=NULL) free(newPos);
		//sprintf(buff,"blobs %d %d %d %d %d %d %d %d\n", blobs[0],blobs[1], blobs[3],blobs[4], blobs[6],blobs[7], blobs[9],blobs[10]);
		//sendBuffer(buff);
		//unsigned int blorbs[12] = {201,	366,0,	164,	312,	0,130,	391,	0,169	,408,0};
		
		POINT *newPos = initPoint(0,0);
		newPos = findPos(blobs);
		
		//sprintf(buff, "new x: %d, y: %d th: %.3f\n", newPos->x, newPos->y,newPos->theta);
		//sendBuffer(buff);
		
		if(currentPos==NULL){ 
			currentPos = initPoint(0,0);
		}
		if (newPos != NULL){
			currentPos = newPos;
		}
		sprintf(buff, "curr x: %d, y: %d ;\n", currentPos->x, currentPos->y);
		sendBuffer(buff);
		
		//if(abs(newPos->x - currentPos->x) >0){
			//if(currentPos != NULL) currentPos = NULL;
			//currentPos = initPoint(0,0);
			//currentPos->x = newPos->x;
			//currentPos->y=newPos->y;
			//if(DEBUG_POINT && DEBUG_ON){
				//sprintf(buff, "curr x: %d, y: %d ;\n", currentPos->x, currentPos->y);
				//sendBuffer(buff);
			//}
			//
		//}
		return currentPos;
	}	
	else return NULL;
}