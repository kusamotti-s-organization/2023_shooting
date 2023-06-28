#include"works.h"
#include<DxLib.h>
#include<assert.h>
#include"common.h"
#include"config.h"
#include<math.h>
#include"player.h"
static const float PI = 3.1415653;
static const int ALPHANUMRADIUS = 40;

namespace {
	struct GLOW {
		POS pos = {};
		VEC vec = {};
		int color = 0;
		int alphanum = 0;
		int radius = 0;
	};
	const int glownum = 20;
	
	struct WORKS {
		bool active=false;
		GLOW glows[glownum] = {};
	};
	const int worksnums = 10;
	WORKS works[worksnums];


	bool keystop = false;
	int se = -1;
}

void WorksInit() {
	se = LoadSoundMem("data/sound/â‘âŒñC.mp3");
	assert(se>0);
	ChangeVolumeSoundMem(255*50/100,se);
	for (int i = 0; i < worksnums; i++) {
		works[i] = {};

		for (int j = 0; j < glownum; j++) {
			
			works[i].glows[j].alphanum = 0;
			works[i].glows[j].radius = 0;
			works[i].glows[j].color = 0;
		}
	}

}
void WorksCreate(POS _pos,
	int _colorR,int _colorG,int _colorB,
	int _randColorR,int _randColorG,int _randColorB) {
	for (int i = 0; i < worksnums; i++) {
		if(works[i].active)continue;
		works[i].active=true;

		for (int j = 0; j < glownum; j++) {
			int cr=_colorR,
				cg=_colorG,
				cb=_colorB;
			int rr=GetRand(_randColorR),
				rg=GetRand(_randColorG),
				rb=GetRand(_randColorB);
			int r=cr+rr,g=cg+rg,b=cb+rb;
			if(r>255)r=255;
			if(g>255)g=255;
			if(b>255)b=255;
			works[i].glows[j].pos = _pos;
			works[i].glows[j].alphanum = 255;
			works[i].glows[j].radius = GetRand(3) + 2;
			works[i].glows[j].color = GetColor(r,g,b);
			int angle = PI / 180 * (j * 360 / glownum);
			works[i].glows[j].vec.vx = cos(angle) * (GetRand(6)+0.5);
			works[i].glows[j].vec.vy = sin(angle) * (GetRand(6)+0.5);
		}
		PlaySoundMem(se,DX_PLAYTYPE_BACK);
			break;
	}
}
void WorksUpdate() {
	//çsìÆ
	for (int i = 0; i < worksnums; i++) {
		if (!works[i].active)continue;

		for (int j = 0; j < glownum; j++) {
			POS p = GetPlayerVX();
			//360Ç…çLÇ™ÇÈ
			works[i].glows[j].pos.x += works[i].glows[j].vec.vx+p.x;
			works[i].glows[j].pos.y += works[i].glows[j].vec.vy+p.y;
		
			//â∫Ç™ÇÈ
		
		

			//ìßñæÇ…
			works[i].glows[j].alphanum += -(255 / ALPHANUMRADIUS);
			if (works[i].glows[j].alphanum < 0) {
				works[i].glows[j].alphanum = 0;
				works[i].active=false;
			}
		}
	}
	

	//debugópê∂ê¨
	POS p = { SCREEN_WIDTH / 2,SCREEN_HEIGHT / 2 };
	bool key = CheckHitKey(KEY_INPUT_3);
	if (key && !keystop) {

		WorksCreate(p);
		keystop = true;
	}
	else {
		keystop = false;
	}
}
void WorksDraw() {
	for (int i = 0; i < worksnums; i++) {
		if (!works[i].active)continue;
		for (int j = 0; j < glownum; j++) {
			double x  	=works[i].glows[j].pos.x;
			double y  	=works[i].glows[j].pos.y;
			int	radius	=works[i].glows[j].radius;
			int	color 	=works[i].glows[j].color;

			SetDrawBlendMode(DX_BLENDMODE_ALPHA,works[i].glows[j].alphanum);
			DrawCircle(x, y, radius, color, true);
			SetDrawBlendMode(DX_BLENDMODE_ADD,255);
			int num=5;
			int alphanum = works[i].glows[j].alphanum-50;
			if(alphanum<0)alphanum=0;
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, alphanum);
			DrawCircle(x+num, y, radius, color, true);
			DrawCircle(x-num, y, radius, color, true);
			DrawCircle(x, y+num, radius, color, true);
			DrawCircle(x, y-num, radius, color, true);
			num = 8;
			alphanum = works[i].glows[j].alphanum - 155;
			if (alphanum < 0)alphanum = 0;
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, alphanum);
			DrawCircle(x+num, y+num, radius, color, true);
			DrawCircle(x-num, y-num, radius, color, true);
			DrawCircle(x-num, y+num, radius, color, true);
			DrawCircle(x+num, y-num, radius, color, true);
		}
	}
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}
void WorksDelete() {
	DeleteSoundMem(se);
}