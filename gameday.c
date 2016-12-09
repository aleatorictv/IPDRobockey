#include "helpers.h"
#include "CONFIG.h"
#include "gameday.h"
long currTime=0;
POINT *m = NULL;
int state=0;
int gx =0;
int gy =0;
int rx =0;
int ry = 0;
int puckAng = -1; 
int puckVal = -1;
int puckProx = -1;
int puckSw = -1;
int starttime=0;
int prevState=0;
int turnState=0;
char buff[100];

void setT(){
	currTime++;
}
POINT *dance(POINT *g, POINT *r, int *_puck){
	if(m!= NULL) free(m);
	m = initPoint(0,0);
	
	gx= g->x;
	gy = g->y;
	rx=r->x;
	ry = r->y;
	puckAng = *(_puck+0);
	puckVal = *(_puck+1);
	puckProx = *(_puck+2);
	puckSw = *(_puck+3);
	if (!NEED_WII || (!r->x && !r->y)){	//wii disabled or bad position
		state =0;
		if(puckVal > 200 && puckVal <1200) state =1;
		if(!check(PIND,5)) state =2;
	}else{
		state =3;
		if(puckVal > 200 && puckVal <1200) state =4;
		if(!check(PIND,5))  state = 5;
}
sprintf(buff,"puck %d %d %d\n",state,puckAng, puckVal);
sendBuffer(buff);
	if(JUST_ROAM) state=0;
	switch(state){
		case 0: //no wii, no puck = roam
			roam();
		break;
		case 1: // no wii, puck = aim for puck
			aim();
		break;
		case 2: //no wii, has puck = push or die
			pushordie();
		break;
		case 3: // wii, no puck = roam
			roamPos();
		break;
		case 4: //wii, puck = aim for puck
			aimPos();
		break;
		case 5: //wii, has puck  = push or die
			pushordie();
		break;
	}
	if(prevState != state){
		 starttime=0;
		 prevState=state;
	}
	if(currTime<10){ forward();}	//opening move
	//else roam();
	
	return m;
}
void left(){
	m->x = 255;
	m->y= -255;
}
void right(){
	m->x = -255;
	m->y= 255;
}
void forward(){
	m->x=255;
	m->y=255;
}
void die(){
	m->x=0;
	m->y=0;
}
void roam(){
	
	green(0);
	if(!starttime) starttime = currTime;
	int t1 = currTime-starttime;
	int tstep = 10;
	int tturn = 1;
	if(t1 <  tstep ) forward();
	else if(t1 >= tstep &&  t1 < tstep + tturn) right();
	else if(t1 >=  tstep + tturn && t1 <   tstep*2 ) forward(); 
	else if(t1 >=  tstep*2 && t1 <  tstep*2+tturn )left();
	else if(t1 >=   tstep*2+tturn  && t1 <  tstep*3 ) forward(); 
	else if(t1 >=  tstep*3 && t1 <  tstep*3+tturn )right();
	else starttime =0;
}
void aim(){
	green(1);
	if(!starttime){ starttime=currTime;}
	if((puckAng == 0 || puckAng ==1 || puckAng ==2 )&& currTime<starttime+2) left();
	else if((puckAng == 8 || puckAng ==7)&& currTime < starttime+2) right();
	else { forward(); starttime =0;}
	if(currTime-starttime >20) roam();
}
void roamPos(){
	roam();
}
void aimPos(){
	if(puckAng == 0 || puckAng ==1 || puckAng ==2) left();
	else if(puckAng == 8 || puckAng ==7) right();
	else forward();
	
}
void pushordie(){
	if(!starttime) starttime = currTime;
	if(currTime>starttime+30) forward();
	else die();
}