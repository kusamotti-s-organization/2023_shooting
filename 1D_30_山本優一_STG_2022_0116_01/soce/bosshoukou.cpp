#include"bosshoukou.h"
#include<DxLib.h>
#include"common.h"
#include"config.h"
#include"boss.h"
#include<math.h>
#include"player.h"
namespace {
	bool keystop=false;
	double angle=0.0f;
	int img = -1;
	bool dispflag=false;
	int alpha = 254;
	int one = 1;
}

void BossHoukouInit() {
	angle=0.0f;
	dispflag=false;
	alpha = 254;
	one = 1;
	img=MakeScreen(256,256,true);
	SetDrawScreen(img);
	DrawCircle(128,128, 128, GetColor(255, 255, 255), true);
	SetDrawBlendMode(DX_BLENDMODE_SUB, 255);
	DrawCircle(128,128+1,128, GetColor(255, 255, 255), true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	SetDrawScreen(DX_SCREEN_BACK);
}
void BossHoukouUpdate() {
	POS bpos = GetBossPos();
	POS ppos = GetPlayerPosition();
	angle = -atan2(ppos.x-bpos.x,ppos.y-bpos.y);
	int bsize =64*3/2;
	if (bpos.x<0-bsize||
		bpos.y<0-bsize||
		bpos.x>SCREEN_WIDTH+bsize||
		bpos.y>SCREEN_HEIGHT+bsize
		) {
		dispflag=true;
	}
	else {
		dispflag=false;
	}


	POS p = {};
	p.x = bpos.x-ppos.x;
	p.y = bpos.y-ppos.y;
	int kyori = sqrt(p.x*p.x+p.y*p.y);
	int num255=kyori/255;
	if(num255<1)num255=1;
	int num=255/num255;
	alpha+=one*num;
	if(alpha>255)alpha=255;
	if(alpha<0)alpha=0;
	if (alpha<=0||
		alpha>=255
		) {
		one=-one;
	}
	//printfDx("num=%d\n",num);
}
void BossHoukouDraw() {
	//DrawGraph(100,100,img,true);
	if (dispflag) {
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
		DrawRotaGraph(SCREEN_WIDTH/2,SCREEN_HEIGHT/2,1.0f,angle,img,true);
	}
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND,0);
}
void BossHoukouDelete() {

}

