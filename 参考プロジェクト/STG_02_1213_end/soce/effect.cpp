#include"effect.h"
#include<DxLib.h>
#include"common.h"
#include"config.h"
#include<math.h>
static const float PI = 3.1415653;
static const int ALPHANUMRADIUS = 40;

namespace {
	struct GLOW {
		int alphanum=0;
		int radius=0;
		int color=0;
	POS pos = {};
	VEC vec = {};
	};
	const int glownum = 20;
	GLOW glows[glownum] = {};


	bool keystop = false;
}

void EffectInit() {
	for (int i = 0; i < glownum; i++) {
	glows[i].pos = {};
	glows[i].vec = {};
	glows[i].alphanum=0;
	glows[i].radius=0;
	glows[i].color=0;
	}

}
void EffectCreate(POS _pos) {
	for (int i = 0; i < glownum; i++) {
		glows[i].pos = _pos;
		glows[i].alphanum=255;
		glows[i].radius=GetRand(3)+2;
		glows[i].color=GetColor(GetRand(255),GetRand(80),GetRand(100));
		int angle = PI / 180 * (i * 360 / glownum);
		glows[i].vec.vx = cos(angle) * GetRand(7);
		glows[i].vec.vy = sin(angle) * GetRand(7);
	}
}
void EffectUpdate() {
	for (int i = 0; i< glownum; i++) {

	
	glows[i].pos.x+=glows[i].vec.vx;
	glows[i].pos.y+=glows[i].vec.vy;
	glows[i].alphanum+=-(255/ALPHANUMRADIUS);
	if(glows[i].alphanum<=0)
		glows[i].alphanum=0;
	}
	
	POS p={SCREEN_WIDTH/2,SCREEN_HEIGHT/2};
	bool key=CheckHitKey(KEY_INPUT_3);
	if (key&&!keystop) {
		
		EffectCreate(p);
		keystop=true;
	}
	else {
		keystop=false;
	}
}
void EffectDraw() {
	for (int i = 0; i < glownum; i++) {
		//SetDrawBlendMode(DX_BLENDMODE_ALPHA,glows[i].alphanum);
		DrawCircle(glows[i].pos.x,glows[i].pos.y,glows[i].radius,glows[i].color,true);
	}
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND,0);
}
void EffectDelete() {

}