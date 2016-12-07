#include "helpers.h"
#include "CONFIG.h"
#include "targeting.h"
POINT *motorPT = NULL;
int fwd=0;
int t=0;
//INPUT goal position, robot position, puck location
//OUTPUT "POINT" variable with motor speeds and directions

void trigger(int _t){
	t=_t;
}
POINT *setTarget(POINT *g, POINT *r, int *puck){
	if(motorPT != NULL) free(motorPT);
	motorPT=initPoint(0,0);
	
	if(*puck>0){  //target puck
		switch(*puck){
			case 1:	//forward
			if(*(puck+1)){ //far
				motorPT->x=255;
				motorPT->y=0;
				}else {
				motorPT->x = 180;
				motorPT->y=0;
			}
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
	if(TEST_SENSORS){
		if(*(puck+1)){
		switch(*puck){
			case 0:	//captured, go!
			motorPT->x = 0;
			motorPT->y = 0;
			green(ON);
			break;
			case 1:	//forward	dead reckoned
			motorPT->x =0;
			motorPT->y =0;
			break;
			case 2: //+60 deg //turn slow to left
			motorPT->x=-30;
			motorPT->y=30;
			green(OFF);
			break;
			case 3: //+90
			motorPT->x=-90;
			motorPT->y=90;
			green(OFF);
			break;
			case 4: //+150
			motorPT->x=-150;
			motorPT->y=150;
			break;
			case 5: // -150
			motorPT->x=150;
			motorPT->y=-150;
			break;
			case 6: // -90
			motorPT->x=100;
			motorPT->y=-100;
			green(OFF);
			break;
			case 7: // -60
			motorPT->x=30;
			motorPT->y=-30;
			break;
			default: //spin?
			motorPT->x=100;
			motorPT->y=-100;
			break;
		}
		}
		//sprintf(buff,"send %d %d\n",motorPT->x,motorPT->y);
		//sendBuffer(buff);
	}
	if(TEST_RUN){
		if(t==0){
			m_red(OFF);
			motorPT->x = 0;
			motorPT->y =-100;
		}
		if(t==1){
			m_red(ON);
			motorPT->x = 50;
			motorPT->y = 0;
			
		}
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
		if(!fwd && abs(errTh) < 0.1) 	fwd = FALSE;
		
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
			m_red(TOGGLE);
			motorPT->x=100;
			motorPT->y = 0;//scale(targetD,5,800,0,255); //run fast then slow as dist to goal shrinks, goes to 0 at 5px from goal
			
		}
		
		
		
	}
	return motorPT;
}