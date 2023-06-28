#include"item.h"
#include<DxLib.h>
#include"common.h"
#include"switchControl.h"
#include"config.h"

namespace {

	enum ITEMTYPE {
		noitem = -1,
		heal = 0,//‰ñ•œ
		inv,//–³“G

		maxitemtype
	};
	struct ITEM {
		POS pos = {};
		int typeimg[maxitemtype] = {};//-1
		int mytype = -1;
		bool active=false;
	};
	const int maxitem = 20;
	ITEM item[maxitem];


	bool keystop=false;

}
#include<cassert>
void ItemInit() {
	for (int i = 0; i < maxitem; i++) {
		item[i]={};
		item[i].mytype=noitem;

		for (int j = 0; j < maxitemtype; j++) {
		item[i].typeimg[j]=MakeScreen(20,20,TRUE);
		SetDrawScreen(item[i].typeimg[j]);
		DrawBox(0,0,20,20,GetColor(255,255,255),true);
		assert(item[i].typeimg[j]>0);
		SetDrawScreen(DX_SCREEN_BACK);

		}
	}

}
void ItemCreate(POS _pos, int _type) {
	for (int i = 0; i < maxitem; i++) {
		if (!item[i].active)
			continue;
		item[i].active = true;
		if (_type = -1) {
			item[i].mytype = GetRand(maxitemtype);
		}
		item[i].mytype = _type;
		item[i].pos = _pos;
	}
}
void ItemUpdate() {
	bool key=CheckHitKey(KEY_INPUT_SPACE);
	if (key) {
		POS p = { SCREEN_WIDTH / 2,SCREEN_HEIGHT/2};
		ItemCreate(p);
	}

	for (int i = 0; i < maxitem; i++) {
		if (!item[i].active)
			continue;


	}
}
void ItemDraw() {
	for (int i = 0; i < maxitem; i++) {
		if (!item[i].active)
			continue;
		DrawGraph(item[i].pos.x,item[i].pos.y,item[i].typeimg[item[i].mytype],true);
	}
}
void ItemDelete() {
	for (int i = 0; i < maxitem; i++) {
		DeleteGraph(item[i].typeimg[i]);
		item[i].typeimg[i] = -1;
	}
}

