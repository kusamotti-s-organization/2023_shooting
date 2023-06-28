#include"fire.h"
#include<DxLib.h>
#include"common.h"
#include"config.h"
#include<math.h>
#include"works.h"
#include"player.h"
static const int SPOWNTIME = 30;//フレーム

namespace {
	const int lognums = 5;
	struct FIRE {
		int img = -1;
		POS pos = { 0,0 };
		POS logs[lognums] = {};
		int movecount = 0;
		bool active = false;
	};
	const int  firenums=10;
	FIRE fire[firenums];

	bool keystop=false;

	int spowncount=0;
}

void FireInit(){
	for (int i = 0; i < firenums; i++) {

		fire[i] = {};
		fire[i].pos.x=SCREEN_WIDTH /1.2;
		fire[i].pos.y=SCREEN_HEIGHT/1.2;
		for (int j = 0; j < lognums; j++) {
		fire[i].logs[j]=fire[0].pos;
		}
		fire[i].movecount = 0;
		fire[i].active = false;
		
		fire[i].img= MakeScreen(20,20,true);
		SetDrawScreen(fire[i].img);
		DrawCircle(10,10,5,GetColor(255,255,255),true);
	}
	
	SetDrawScreen(DX_SCREEN_BACK);
	spowncount=0;
}
void FireDelete(){
	for (int i = 0; i < firenums; i++) {
		DeleteGraph(fire[i].img);
	}
	
}
void FireCreate() {
	for (int i = 0; i < firenums; i++) {
		if(fire[i].active)continue;
		double Lowestxnum =SCREEN_WIDTH / 5;
			fire[i].pos.x = GetRand(SCREEN_WIDTH / 2)+ Lowestxnum;
			fire[i].pos.y = SCREEN_HEIGHT / 1.2;
			for (int j = 0; j < lognums; j++) {
				fire[i].logs[j] = fire[0].pos;
			}
			fire[i].movecount = 0;
			fire[i].active = true;
			break;
	}
	spowncount = 0;
}
void FireUpdate(){

	for (int i = 0; i < firenums; i++) {
		if(!fire[i].active)continue;

		POS pp = GetPlayerVX();

		//行動
		if (fire[i].active) {
			fire[i].pos.y += -5+pp.y;
			fire[i].pos.x += pp.x;
		}

		//残像
		for (int j = lognums-1; j >0 ; j--) {
			POS p = {0,3};
			fire[i].logs[j] = PosAdd( fire[i].logs[j-1],p);
			fire[i].logs[j] = PosAdd( fire[i].logs[j],pp);
		}
		fire[i].logs[0] = fire[i].pos;

		//fireが消えたらworksの出現
		if (fire[i].movecount!=-1)fire[i].movecount++;
		if (fire[i].movecount > 30+GetRand(30)) {
			fire[i].active=false;
			POS wp = { fire[i].pos.x,fire[i].pos.y};
			WorksCreate(wp,100,100,100);
			fire[i].movecount = -1;
		}
	}

	if (spowncount++ > SPOWNTIME) {
		FireCreate();
		spowncount = 0;
	}

	//printfDx("count=%d\n", fire[0].movecount);
	bool key=CheckHitKey(KEY_INPUT_SPACE);
	if (key&&!keystop) {
		FireCreate();
		keystop = true;
	}
	if(!key)keystop=false;
}
void FireDraw() {

	for (int i = 0; i < firenums; i++) {
		if (fire[i].active) {
			for (int j = 0; j < lognums; j++) {//残像
				SetDrawBlendMode(DX_BLENDMODE_ALPHA,150-j*255/ lognums);
				DrawGraph((int)fire[i].logs[j].x, (int)fire[i].logs[j].y, fire[i].img, true);
			}
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND,0);
			//本体
			DrawGraph((int)fire[i].pos.x, (int)fire[i].pos.y, fire[i].img, true);
		}
	}
	
}
