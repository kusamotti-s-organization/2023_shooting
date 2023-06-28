#include"health.h"
#include<DxLib.h>
#include"config.h"
namespace {
	VECTOR pos = {};
	int num = 0;
	bool keystop = false;
	int xsize = 0;
	int color = -1;

}

void HealthInit() {
	pos = {125,70,0};
	num = 3;
	keystop = false;
	xsize = 16 / 3;
	color = GetColor(255, 255, 255);
}
void HealthSetNum(int _num) {
	num = _num;
}
void HealthUpdate() {
	//bool key = CheckHitKey(KEY_INPUT_RETURN);
	//if (key&&!keystop) {
	//	num--;
	//	keystop = true;
	//}
	//else if (!key)keystop = false;
	switch (num) {
		case 1:
			color = GetColor(255,10,10);
			break;
		case 2:
			color = GetColor(255,255,20);
			break;
		case 3:
			color = GetColor(50,50,220);
			break;
		default:
			color = GetColor(255, 255, 255);
			break;
		}
}
void HealthDraw() {
	for (int i = 0; i < num; i++) {
		int range = 5;
		int ysize = 12;
	DrawOval(pos.x+i*(xsize*2+range),pos.y,xsize,ysize,color,true);
	}

}
void HealthDelete() {

}