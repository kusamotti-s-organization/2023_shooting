#include"destroyEffect.h"

#include<DxLib.h>
#include<cmath>
#include"../common.h"

namespace {
	//enum STATE {
	//	instance=0

	//	,max
	//};


	float radiusChange;
	int counter;
	Circle position;
	bool active;
}

void destroyEffectInit(){
	counter = 0;
	radiusChange = 0;
	active = false;
	position = { 0,0,0 };
}

void destroyEffectUpdate(){
	++counter;
	if (CheckHitKey(KEY_INPUT_SPACE)) {
		EffectOn(450, 450, 20);
	}

}

//
//void FourCircleDraw1(float x, float y, float r);
//void FourCircleDraw2(float x, float y, float r);
//void StarCricleDraw(float x, float y, float r);
void DestroyEffectMob(float x, float y, float r);
void DestroyEffectMob(Circle pos);

void destroyEffectDraw(){

	if (active)
		DestroyEffectMob(position);

	////test
	//StarCricleDraw(200,200,20);
	//FourCircleDraw2(200,200,20);
	//FourCircleDraw1(200,200,20);

	////FourCircleDraw1(300,300,20);
	////FourCircleDraw2(400,400,20);
	////StarCricleDraw(500,500,20);

	//DestroyEffectMob(450,450,20);
	////test--
}

void destroyEffectDelete(){
}

void EffectOn(float x, float y, float r){
	active = true;
	counter = 0;
	radiusChange = 0;
	position = {x,y,r};
}

void FourCircleDraw1(float x,float y,float r) {
	//0xffffff 白
	float harfHarfRadius = r / 2.f/2.f;
	DrawCircleAA(x - harfHarfRadius, y, harfHarfRadius,22, 0xffffff);
	DrawCircleAA(x + harfHarfRadius, y, harfHarfRadius,22, 0xffffff);
	DrawCircleAA(x, y - harfHarfRadius, harfHarfRadius,22, 0xffffff);
	DrawCircleAA(x, y + harfHarfRadius, harfHarfRadius,22, 0xffffff);

}

void FourCircleDraw2(float x,float y, float r) {
	//0xdd5555 オレンジ
	float harfRadius = r / 2;
	DrawCircleAA(x-harfRadius,y,harfRadius,22, 0xdd5555);
	DrawCircleAA(x+harfRadius,y,harfRadius,22, 0xdd5555);
	DrawCircleAA(x,y-harfRadius,harfRadius,22, 0xdd5555);
	DrawCircleAA(x,y+harfRadius,harfRadius,22, 0xdd5555);
}

void StarCricleDraw(float x,float y,float r) {
	//0xff0000 真っ赤
	DrawOvalAA(x,y,r/2,r*2,22, 0xff0000,TRUE);
	DrawOvalAA(x,y,r*2,r/2,22, 0xff0000,TRUE);
}

void DestroyEffectMob(float x,float y,float r) {
	//高エネルギーなほど白くする。
	//だんだん赤く
	//最後は赤　半透明で小さく
	//円をかぶせて小さくする

	if (counter < 5) 
	{
		FourCircleDraw1(x, y, r);
	}
	else if(counter<10)
	{
		SetDrawBlendMode(DX_BLENDMODE_ADD, 255*2/3);
		FourCircleDraw2(x, y, r);
	}
	else if(counter<20)
	{
		SetDrawBlendMode(DX_BLENDMODE_ADD, 255*1/3);
		StarCricleDraw(x, y, r);
	}
	else if(radiusChange <90){
		++radiusChange;
		SetDrawBlendMode(DX_BLENDMODE_ADD, 255 * 1 / 3);
		DrawCircleAA(x, y, r*2 * cos((radiusChange+90)*DX_PI_F / 180), 22, 0xffffff);

		SetDrawBlendMode(DX_BLENDMODE_ADD, 255 * 2 / 3);
		StarCricleDraw(x, y, r);
	}
	else if(radiusChange<180-1)
	{
		radiusChange += (180.f - radiusChange)/15.f;
		SetDrawBlendMode(DX_BLENDMODE_ADD, 255 * 1 / 3);
		DrawCircleAA(x, y, r*2 * cos((radiusChange + 90) * DX_PI_F / 180), 22, 0xffffff);
	}
	else {
		radiusChange = 180;
		active = false;
	}

	SetDrawBlendMode(DX_BLENDMODE_NOBLEND,0);
}
void DestroyEffectMob(Circle _pos) {
	DestroyEffectMob(_pos.m_position.x,_pos.m_position.y,_pos.radius);
}
