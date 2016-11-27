#include "helpers.h"
#include "CONFIG.h"
#include "targeting.h"
POINT *motorPT = NULL;

//INPUT goal position, robot position, puck location
//OUTPUT "POINT" variable with motor speeds and directions
POINT *setTarget(POINT *g, POINT *r, int puck){	
	if(motorPT == NULL) motorPT = initPoint(0,0);
	
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
		float targetTh = angleBtwn(g, r);
		float targetD = distance(g->x,g->y,r->x,r->y);
		if(abs(targetTh) > 0.1) {
			if(targetTh>0){
				 motorPT->x = 50;	//slowly speed turn in place 
				 motorPT->y =-100;	//big wheel differential
			}else{
				motorPT->x = 50;	//slowly speed turn in place
				motorPT->y = 100;	//opposite turn direction (hopefully closer direction)
			}
		}else{	//once aligned travel towards goal
			motorPT->y=0;
			motorPT->x = scale(targetD,5,1000,0,255); //run fast then slow as dist to goal shrinks, goes to 0 at 5px from goal
		}
		
		
	}
	return motorPT;
}