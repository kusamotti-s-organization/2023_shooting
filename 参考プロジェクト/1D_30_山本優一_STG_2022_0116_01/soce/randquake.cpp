#include"randquake.h"
#include<DxLib.h>
#include"config.h"
#include"common.h"
namespace {
	bool active = false;

	VECTOR vx = {};
	VECTOR movemax = {};

	int count = 0;
	int life = 0;
}

void RandQuakeInit() {
	active = false;
	vx = {1,1,1};
	count = 0;
	movemax = {0,0,0};
	life = 0;

	//RandQuakeSwitch();
}
void RandQuakeSwitch(bool _active) {
	life = 0;
	active = _active;
}
bool RandQuakeGetActive(){
	return active;
}
void RandQuakeUpdate() {
	if (!active) {
		vx = { 0.0f,0.0f };
	}
	if (active) {
		count++;
		if (life++>50.0f) {
			active = false;
		}
		if (count > 5) {
			vx.x = GetRand(3);
			vx.y = GetRand(3);
			
			count = 0;
		}
		
		int num = 20;

		if (movemax.x>num) {
			vx.x = -vx.x;
		}
		else if (movemax.x < -num) {
			vx.x = -vx.x;
		}if (movemax.y>num) {
			vx.y = -vx.y;
		}
		else if (movemax.y < -num) {
			vx.y = -vx.y;
		}

	}
	
	VectorAdd(&movemax,&movemax,&vx);
	VectorAdd(&movemax,&movemax,&vx);

}
void RandQuakeDraw() {
	
}
void RandQuakeDelete() {

}
VECTOR RandQuakeMove() {
	return vx;
}