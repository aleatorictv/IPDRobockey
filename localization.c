#include "m_general.h"
#include "localization.h"
#include "CONFIG.h"

POINT *pos_wii, *pos;
float th;
int axisL=0;
int pairs[12]={1,2,1,3,1,4,2,3,2,4,3,4};
POINT *pts[4];
POINT *v1, *v2;
int dists[6];
int n;

POINT *findPos(int* blobs){
	memset(&dists[0], 0, sizeof(dists));  //clear distance array
	for(int i=0;i<4;i++) free(pts[i]);	//clear POINT pointers
	
	if(!parseBlobs(blobs))return NULL;  //if anything goes wrong, no position reported
	if(!findDists()) return NULL;
	if(findNS()) return NULL;
	if(rinkTransform()) return pos;  //if 3 or 4 points visible, position reported
	else return NULL;
}
int parseBlobs(int* blobs){
	n=4;
	for(int i=0;i<4;i++){
		if(blobs[i*3]==1023 && blobs[i*3+1]==1023)	n--;
		else{
			if(pts[i]==NULL){
				pts[i]=initPoint(blobs[i*3],blobs[i*3+1]);
			}
			else {
				pts[i]->x = blobs[i*3];
				pts[i]->y = blobs[i*3+1];
			}
		}
	}
	if(n<3) return 0;
	return 1;
}

int findDists(){ //find unique distances between points
	if(n==4){
		int k=0;
		for(int i=0;i<3;i++){
			for(int j=i+1;j<4 ;j++ ){
				dists[k]=distance(pts[i]->x,pts[i]->y,pts[j]->x,pts[j]->y);
				k++;
			}
		}
	}else if(n==3){
		dists[0]=distance(pts[0]->x,pts[0]->y,pts[1]->x,pts[1]->y);
		dists[1]=distance(pts[0]->x,pts[0]->y,pts[2]->x,pts[2]->y);
		dists[2]=distance(pts[1]->x,pts[1]->y,pts[2]->x,pts[2]->y);
	}else{
		return 0;
	}
	return 1;
}

int rinkTransform(){
	return 1;
}
int findNS(){
	int dmax, di_max, di_min;
	int dmin=1280;
	int pair_max[2], pair_min[2];
	for (int i=0;i<n*(n-3)/2+n;i++){	//num of diagonals + num sides
		if(dists[i] > dmax){
			dmax = dists[i];
			di_max=i;
		}
		if(dists[i] < dmin){
			dmax = dists[i];
			di_min=i;
		}
	}
	pair_max[1] = pairs[di_max*2];		//should use pointers here
	pair_max[2] = pairs[di_max*2+1];
	pair_min[1] = pairs[di_min*2];
	pair_min[2] = pairs[di_min*2+1];
	
	int possA, possB, trueA, trueB;	//could also be pointers
	
	possA = pair_max[1];
	possB = pair_max[2];
	if(n==4){
		if(possA == pair_min[1] || possA == pair_min[2]){
			trueB = possA;
			trueA = possB;
		}else if(possB == pair_min[1] || possB == pair_min[2]){
			trueB=possB;
			trueA=possA;
		}
		axisL = dmax;
	}
	else if(n<=3){  //implement 3 star determination later
		return 0;
	}
	
	if(trueA && trueB){
		pos_wii->x = (pts[trueB]->x + pts[trueA]->x)/2 ; //position is center of axis
		pos_wii->y = (pts[trueB]->y + pts[trueA]->y)/2 ;
		
		float vect1[] = {pts[trueB]->x- pts[trueA]->x, pts[trueB]->y- pts[trueA]->y };	//vector of constellation axis in camera view
		float vect2[] = {0, 1};//vector of camera frame vertical
		//float th = angleBtwnF(vect1,vect2); // maybe faster not to worry about 2 dot prods
		float th = acos(dotprod(vect1,vect2)/sqrt(dotprod(vect1,vect1)));  //angle between frame and true North
		if(pts[trueB]->x > pts[trueA]->x) th = -th;	//flip sign if in quadrant 3/4
		pos->x = (pos_wii->x - CENTER_X) * cos(th) + (pos_wii->y-CENTER_Y) *-sin(th)+CENTER_X; //homogeneous transform pi about y to get view from above
		pos->y = (pos_wii->y - CENTER_Y) * sin(th) + (pos_wii->y-CENTER_Y) * cos(th)+CENTER_Y;
		}
	return 1;
}