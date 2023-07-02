#include"destroyEffect.h"

#include<DxLib.h>
#include<cmath>
#include"../common.h"

namespace {
	constexpr int MAX_EFFECT_NUM = 100 + 1;
	//enum STATE {
	//	instance=0

	//	,max
	//};

	struct EffectParam {
		float radiusChange;
		int counter;
		Circle circle;
		bool active;

	};
	EffectParam effects[MAX_EFFECT_NUM];

}

void DestroyEffectInit() {
	for (int i = 0; i < MAX_EFFECT_NUM; ++i) {
		effects[i].circle = { 0,0,0 };
		effects[i].active = false;
		effects[i].counter = 0;
		effects[i].radiusChange = 0;
	}
}

void DestroyEffectUpdate() {

	/*for (int i = 0; i < MAX_EFFECT_NUM; ++i) {
		if ( !effects[i].active)
			continue;

			++effects[i].counter;
	}*/

	//test
#ifdef _DEBUG
	if (CheckHitKey(KEY_INPUT_SPACE) && CheckHitKey(KEY_INPUT_LSHIFT)) {
		EffectOn(450, 450, 20);
	}
#endif
	//test--

}

//
//void FourCircleDraw1(float x, float y, float r);
//void FourCircleDraw2(float x, float y, float r);
//void StarCricleDraw(float x, float y, float r);
void DestroyEffectMob();

void DestroyEffectDraw() {
	DestroyEffectMob();

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

void DestroyEffectDelete() {
}

void CreateEffect(float x, float y, float r);
void EffectOn(float x, float y, float r) {
	CreateEffect(x, y, r);

	//active = true;
	//counter = 0;
	//radiusChange = 0;
	//position = {x,y,r};
}

void FourCircleDraw1(float x, float y, float r) {
	//0xffffff 白
	float harfHarfRadius = r / 2.f / 2.f;
	DrawCircleAA(x - harfHarfRadius, y, harfHarfRadius, 22, 0xffffff);
	DrawCircleAA(x + harfHarfRadius, y, harfHarfRadius, 22, 0xffffff);
	DrawCircleAA(x, y - harfHarfRadius, harfHarfRadius, 22, 0xffffff);
	DrawCircleAA(x, y + harfHarfRadius, harfHarfRadius, 22, 0xffffff);
}
void FourCircleDraw1(Circle circle) {
	FourCircleDraw1(circle.m_position.x,circle.m_position.y, circle.radius);
}

void FourCircleDraw2(float x, float y, float r) {
	//0xdd5555 オレンジ
	float harfRadius = r / 2;
	DrawCircleAA(x - harfRadius, y, harfRadius, 22, 0xdd5555);
	DrawCircleAA(x + harfRadius, y, harfRadius, 22, 0xdd5555);
	DrawCircleAA(x, y - harfRadius, harfRadius, 22, 0xdd5555);
	DrawCircleAA(x, y + harfRadius, harfRadius, 22, 0xdd5555);
}
void FourCircleDraw2(Circle circle) {
	FourCircleDraw2(circle.m_position.x, circle.m_position.y, circle.radius);
}

void StarCricleDraw(float x, float y, float r) {
	//0xff0000 真っ赤
	DrawOvalAA(x, y, r / 2, r * 2, 22, 0xff0000, TRUE);
	DrawOvalAA(x, y, r * 2, r / 2, 22, 0xff0000, TRUE);
}
void StarCricleDraw(Circle circle) {
	StarCricleDraw(circle.m_position.x, circle.m_position.y, circle.radius);
}

void DestroyEffectMob() {
	//高エネルギーなほど白くする。
	//だんだん赤く
	//最後は赤　半透明で小さく
	//円をかぶせて小さくする
	for (int i = 0; i < MAX_EFFECT_NUM; ++i) {
		if (!effects[i].active)
			continue;

		EffectParam eff = effects[i];

		++effects[i].counter;

		if (effects[i].counter < 5)
		{
			FourCircleDraw1(eff.circle);
		}
		else if (effects[i].counter < 10)
		{
			SetDrawBlendMode(DX_BLENDMODE_ADD, 255 * 2 / 3);
			FourCircleDraw2(eff.circle);
		}
		else if (effects[i].counter < 20)
		{
			SetDrawBlendMode(DX_BLENDMODE_ADD, 255 * 1 / 3);
			StarCricleDraw(eff.circle);
		}
		else if (effects[i].radiusChange < 90) {
			++effects[i].radiusChange;
			SetDrawBlendMode(DX_BLENDMODE_ADD, 255 * 1 / 3);
			DrawCircleAA(eff.circle.m_position.x, eff.circle.m_position.y,eff.circle.radius* 2 * cos((effects[i].radiusChange + 90) * DX_PI_F / 180), 22, 0xffffff);

			SetDrawBlendMode(DX_BLENDMODE_ADD, 255 * 2 / 3);
			StarCricleDraw(eff.circle);
		}
		else if (effects[i].radiusChange < 180 - 1)
		{
			effects[i].radiusChange += (180 - effects[i].radiusChange) / 15;
			SetDrawBlendMode(DX_BLENDMODE_ADD, 255 * 1 / 3);
			DrawCircleAA(eff.circle.m_position.x, eff.circle.m_position.y, eff.circle.radius * 2 * cos((effects[i].radiusChange + 90) * DX_PI_F / 180), 22, 0xffffff);
		}
		else {
			effects[i].counter = 0;
			effects[i].radiusChange = 0;
			effects[i].active = false;
		}

	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}

}
//void DestroyEffectMob(float x, float y, float r) {
//	//高エネルギーなほど白くする。
//	//だんだん赤く
//	//最後は赤　半透明で小さく
//	//円をかぶせて小さくする
//	for (int i = 0; i < MAX_EFFECT_NUM; ++i) {
//		if (!effects[i].active)
//			continue;
//
//		++effects[i].counter;
//
//		if (effects[i].counter < 5)
//		{
//			FourCircleDraw1(x, y, r);
//		}
//		else if (effects[i].counter < 10)
//		{
//			SetDrawBlendMode(DX_BLENDMODE_ADD, 255 * 2 / 3);
//			FourCircleDraw2(x, y, r);
//		}
//		else if (effects[i].counter < 20)
//		{
//			SetDrawBlendMode(DX_BLENDMODE_ADD, 255 * 1 / 3);
//			StarCricleDraw(x, y, r);
//		}
//		else if (effects[i].radiusChange < 90) {
//			++effects[i].radiusChange;
//			SetDrawBlendMode(DX_BLENDMODE_ADD, 255 * 1 / 3);
//			DrawCircleAA(x, y, r * 2 * cos((effects[i].radiusChange + 90) * DX_PI_F / 180), 22, 0xffffff);
//
//			SetDrawBlendMode(DX_BLENDMODE_ADD, 255 * 2 / 3);
//			StarCricleDraw(x, y, r);
//		}
//		else if (effects[i].radiusChange < 180 - 1)
//		{
//			effects[i].radiusChange += (180 - effects[i].radiusChange) / 15;
//			SetDrawBlendMode(DX_BLENDMODE_ADD, 255 * 1 / 3);
//			DrawCircleAA(x, y, r * 2 * cos((effects[i].radiusChange + 90) * DX_PI_F / 180), 22, 0xffffff);
//		}
//		else {
//			effects[i].counter = 0;
//			effects[i].radiusChange = 0;
//			effects[i].active = false;
//		}
//	}
//
//	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
//}
//void DestroyEffectMob(Circle _pos) {
//	DestroyEffectMob(_pos.m_position.x, _pos.m_position.y, _pos.radius);
//}
//void DestroyEffectMob(EffectParam _effect) {
//	DestroyEffectMob(_effect.circle);
//}

void CreateEffect(float x, float y, float r) {

	for (int i = 0; i < MAX_EFFECT_NUM; ++i) {
		if (effects[i].active)
			continue;
		effects[i].active = true;
		effects[i].circle = { x,y,r };
		effects[i].counter = 0;
		effects[i].radiusChange = 0;
		break;
	}
}