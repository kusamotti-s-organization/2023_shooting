#include"bossSpawnWarning.h"
#include<DxLib.h>
#include<assert.h>
#include"common.h"
#include"config.h"

namespace {
	float radius = 5.0f;
	int xnum = SCREEN_WIDTH  / radius;
	int ynum = SCREEN_HEIGHT / radius;

	int alpha=0;
	float count = 0.0f;
	POS posx = {};
	POS posy = {};
	int mozialpha=0;
	int one=5;

	int endcount=0;
	bool endflag=false;

	int bgm = -1;
}

void WarningInit() {
	bgm=LoadSoundMem("data/sound/ゲーム風アラート音.mp3");
	assert(bgm>0);
	endcount=0;
	endflag=false;

}
bool WarningUpdate() {
	if (CheckSoundMem(bgm)!=1) {
		PlaySoundMem(bgm,DX_PLAYTYPE_BACK);
	}
	count+=0.05f;
	mozialpha+=one;
	if(mozialpha>=255)one=-one;
	if (mozialpha < 0) {
		one = -one;
		endcount++;
	}
	if (endcount >=3) {
		endflag=true;
	}
	//printfDx("%d\n", mozialpha);
	return endflag;
}
void WarningDraw() {
	for (int j = 0; j < 2; j++) {
		for (int i = 0; i < xnum; i++) {
			if((i+(int)count)%2==0)alpha=0;
			else alpha=255;
			SetDrawBlendMode(DX_BLENDMODE_ALPHA,alpha);
			posx.x=i*radius*4;
			posx.y=0+radius*2+j*(SCREEN_HEIGHT-radius*4);
			DrawOval(posx.x, posx.y,radius, radius-2, GetColor(200, 200, 150), true);
		}
		for (int i = 0; i < ynum; i++) {
			if ((i+(int)count)%2== 0)alpha = 0;
			else alpha = 255;
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
			posy.x =0 +radius * 2 + j * (SCREEN_WIDTH - radius * 4);
			posy.y = i * radius * 4;
			DrawOval(posy.x, posy.y, radius-2, radius, GetColor(200, 200, 150), true);
		}
	}
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, mozialpha);
	SetFontSize(128);
	DrawFormatString(100,100,GetColor(255,255,25),"BOSS");
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND,0);
	SetFontSize(16);
}
void WarningDelete() {
	DeleteSoundMem(bgm);
}

