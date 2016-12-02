#include "helpers.h"
#include "CONFIG.h"
#include "targeting.h"
POINT *motorPT = NULL;
int fwd=0;
//INPUT goal position, robot position, puck location
//OUTPUT "POINT" variable with motor speeds and directions
POINT *setTarget(POINT *g, POINT *r, int puck){
	if(motorPT != NULL) free(motorPT);
	motorPT=initPoint(0,0);
	
	if(puck>0){  //target puck
		switch(puck){
			case 1:	//straight ahead (all 3 lit up)
			break;
			case 2: //ahead (<3 lit up)
			break;
			case 3: //left lit up
			break;
			case 4: //right lit up
			break;
			case 5: // behind
			break;
			default: //spin?
			break;
		}	
	}else{//has puck, go to goal
		
	}
	if(QUALIFYING){
		int r2g[2] = {(int)(r->x - g->x), (int)(r->y - g->y)};
		int vert[2] = {0,1};
		float targetTh = angleBtwn(r2g, vert);
		float targetD = distance(g->x,g->y,r->x,r->y);
		float errTh = smallestTh(r->theta , targetTh) +PI;
		if(DEBUG_ON) {
			char buff[100];
			//sprintf(buff,"Gx %d Gy %d Rx %d Ry %d\n",g->x,g->y,r->x,r->y);
			//sendBuffer(buff);
			//sprintf(buff,"th to target %.2f\n", targetTh);
			//sendBuffer(buff);
			sprintf(buff,"target %.0f at %.2f\n",targetD, errTh);
			sendBuffer(buff);
		}
		if(!fwd && abs(errTh) < 0.1) fwd = TRUE;
		
		if(!fwd) {
			if(errTh>0){
				 motorPT->x = 0;	//slowly speed turn in place 
				 motorPT->y =-100;	//big wheel differential
			}else{
				motorPT->x = 0;	//slowly speed turn in place
				motorPT->y = 100;	//opposite turn direction (hopefully closer direction)
			}
		}else{	//once aligned travel towards goal
			//setMotors(255,255);
			//m_red(TOGGLE);
			motorPT->x=200;
			motorPT->y = 0;//scale(targetD,5,800,0,255); //run fast then slow as dist to goal shrinks, goes to 0 at 5px from goal
			
		}
		
		
		
	}
	return motorPT;
}
int isFwd(){
	return fwd;
}