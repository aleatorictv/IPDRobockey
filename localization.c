#include "m_general.h"
#include "localization.h"
#include "helpers.h"
#include "CONFIG.h"

POINT *pos_wii, *pos;
float th;
int axisL=0;
int pairs[12]={0,1,0,2,0,3,1,2,1,3,2,3};
POINT *pts[4];
POINT *v1, *v2;
float dists[6];
int n=4;
int initialized =0;

char buff[100];
POINT *findPos(unsigned int* blobs){
	if (!initialized) {
		int i;
		v1=NULL;
		v2=NULL;
		for (i=0; i<4; i++) {
			pts[i] = NULL;
		}
		initialized = 1;
	}
	//memset(&dists[0], 0, sizeof(dists));  //clear distance array
	//for(int i=0;i<4;i++) {
	////clear POINT pointers
	//if(pts[i]!=NULL)free(pts[i]);
	//}
	parsePoints(blobs,pts);
	//if(!parseBlobs(blobs))return NULL;  //if anything goes wrong, no position reported
	if(!findDists()) return NULL;
	if(!findNS()) return NULL;		//if 3 or 4 points visible, position reported
	else {
		sprintf(buff,"det: %d %d %.2f\n",pos->x,pos->y,pos->theta);
		sendBuffer(buff);
		return pos;
	}
}
void parsePoints(unsigned int *blobs, POINT **pts) {
	n=3;
	int i;
	int p_idx = 0;
	for (i=0; i<12; i=i+3) {
		if (blobs[i] != 1023) {
			if (pts[p_idx] == NULL) {
				pts[p_idx] = initPoint(blobs[i], blobs[i+1]);
				} else {
				pts[p_idx]->x = blobs[i];
				pts[p_idx]->y = blobs[i+1];
			}
			p_idx++;
			}else{n--;}
		}
		for (; p_idx < 4; p_idx++) {
			if (pts[p_idx] != NULL) {
				free(pts[p_idx]);
			}
			pts[p_idx] = NULL;
		}
	}
	int parseBlobs(unsigned int* blobs){
		n=4;
		for(int i=0;i<4;i++){
			if(blobs[i*3]==1023 && blobs[i*3+1]==1023){
				n--;
				continue;
				}else{
				if(pts[i]==NULL){
					pts[i]=initPoint(blobs[i*3],blobs[i*3+1]);
					}else {
					pts[i]->x = blobs[i*3];
					pts[i]->y = blobs[i*3+1];
				}
				//sprintf(buff,"pt: %d %d \n", pts[i]->x, pts[i]->y);
				//sendBuffer(buff);
			}
		}
		
		if(n<3) return 0;
		return 1;
	}
	int findDists(){ //find unique distances between points
		if(n==3){
			dists[0]=distancePT(pts[0],pts[1]);
			dists[1]=distancePT(pts[0],pts[2]);
			dists[2]=distancePT(pts[0],pts[3]);
			dists[3]=distancePT(pts[1],pts[2]);
			dists[4]=distancePT(pts[1],pts[3]);
			dists[5]=distancePT(pts[2],pts[3]);
			//int k=0;
			//for(int i=0;i<3;i++){
			//for(int j=i+1;j<4 ;j++ ){
			//sprintf(buff,"pt: %d %d %d %d \n", pts[i]->x, pts[i]->y,pts[j]->x, pts[j]->y);
			//sendBuffer(buff);
			//dists[k] = distancePT(pts[i],pts[j]);
			//dists[k]=distanceI(pts[i]->x,pts[i]->y,pts[j]->x,pts[j]->y);
			//k++;
			//}
			//	}
			//sprintf(buff,"dists: %d %d %d %d %d %d\n",dists[0],dists[1],dists[2],dists[3],dists[4],dists[5]);
			//sendBuffer(buff);
			}else if(n==2){
			dists[0]=distance(pts[0]->x,pts[0]->y,pts[1]->x,pts[1]->y);
			dists[1]=distance(pts[0]->x,pts[0]->y,pts[2]->x,pts[2]->y);
			dists[2]=distance(pts[1]->x,pts[1]->y,pts[2]->x,pts[2]->y);
			}else{
			return 0;
		}
		
		return 1;
	}

	int findNS(){
		float dmax=0;
		int di_max=0;
		int di_min=0;
		float dmin=1280;
		int pair_max[2], pair_min[2];
		int ind = 6;
		//i<n*(n-3)/2+n
		for (int i=0;i<ind;i++){	//num of diagonals + num sides
			if(dists[i] > dmax){
				dmax = dists[i];
				di_max=i;
			}
			if(dists[i] < dmin){
				dmin = dists[i];
				di_min=i;
			}
		}
		//sprintf(buff,"dmax %.2f %d dmin %.2f %d\n",dmax,di_max,dmin,di_min);
		//sendBuffer(buff);
		pair_max[0] = pairs[di_max*2];		//should use pointers here
		pair_max[1] = pairs[di_max*2+1];
		pair_min[0] = pairs[di_min*2];
		pair_min[1] = pairs[di_min*2+1];
		
		int possA, possB;
		int trueA =0;
		 int trueB =0;	//could also be pointers
		
		possA = pair_max[0];
		possB = pair_max[1];
		if(n==3){
			if(possA == pair_min[0] || possA == pair_min[1]){
				trueB = possA;
				trueA = possB;
				}else if(possB == pair_min[0] || possB == pair_min[1]){
				trueB=possB;
				trueA=possA;
		}
		//sprintf(buff,"trueA %d trueB %d \n",trueA, trueB);
		//sendBuffer(buff);
			axisL = dmax;
		}
		else if(n<=2){  //implement 3 star determination later
			return 0;
		}
		
		if(trueA != trueB){
			//for(int i=0;i<4;i++){
				//sprintf(buff,"pt %d: %d %d ;", i, (*(pts+i))->x, pts[trueB]->x);
				//sendBuffer(buff);
			//}
			//m_usb_tx_char(0x0A);
			int Ax = pts[trueA]->x;
			int Ay = pts[trueA]->y;
			int Bx = pts[trueB]->x;
			int By = pts[trueB]->y;
			sprintf(buff,"Ax %d Ay %d Bx %d By %d", Ax, Ay, Bx, By);
			pos_wii->x = (Ax + Bx)/2 ; //position is center of axis
			pos_wii->y = (Ay + By)/2 ;
			float vect1[] = {pts[trueB]->x- pts[trueA]->x, pts[trueB]->y- pts[trueA]->y };	//vector of constellation axis in camera view
			float vect2[] = {0.f, 1.f};//vector of camera frame vertical
			//float th = angleBtwnF(vect1,vect2); // maybe faster not to worry about 2 dot prods
			float th = acos(dotprodF(vect1,vect2)/sqrt(dotprodF(vect1,vect1)));  //angle between frame and true North
			if(pts[trueB]->x > pts[trueA]->x) th = -th;	//flip sign if in quadrant 3/4
			sprintf(buff,"frame XY %d %d %.2f\n", pos_wii->x,pos_wii->y,th);
			sendBuffer(buff);
			pos->x=cos(th)*(pos_wii->x - CENTER_X) + sin(th)*(pos_wii->y-CENTER_Y);
			pos->y=sin(th)*(pos_wii->x - CENTER_X) - cos(th)*(pos_wii->y-CENTER_Y);
			pos->theta = th;
		}
		return 1;
	}