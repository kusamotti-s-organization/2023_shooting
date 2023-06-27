#include"boss.h"
#include<DxLib.h>
#include<assert.h>
#include"config.h"
#include"common.h"
#include<math.h>
#include"player.h"
#include"switchControl.h"
#include"effect.h"
#include"bossenemy.h"

#define PI 3.14159265359

static const int VELOCITY=4;
static const int DAINIVELOCITY=5;//第二形態スピード
static const int BOSSHP=100;
static const float BOSSSIZE= 64 * 3;
static const int BOSSNUMS = 1;//ボスの数
namespace {
	float L = 0;//Rotate(kari
	int white = GetColor(255,150,150);
	struct BOSS {
		bool active = false;
		POS pos= { -100,-100 };
		double angle = 0.0f;
		int deadcount = 0;
		int timg = -1;
		int simg = -1;
		int alphanum=255;
		int hp=0;
		int speed=VELOCITY;
	};
	BOSS boss[BOSSNUMS];
	int size = BOSSSIZE;
	int spawncount = 0;//30
	int nowdeadnum=0;

	//float nazocount = 1;
	int handle = 0;
	OnOff debugkey;

	int dainikeitai=0;
	int dainicolorBright=255;
	int cobuncount= 0;
}


void BossInit() {
	for (int i = 0; i < BOSSNUMS; i++) {
		boss[i]={};
		boss[i].hp= BOSSHP;
		size = BOSSSIZE;
		/*boss[i].pos={};
		boss[i].angle={};
		boss[i].active = false;
		boss[i].aphpanum=255;
		*/boss[i].timg = MakeScreen(20, 20, TRUE);
		SetDrawScreen(boss[i].timg);
		DrawFormatString(0, 0, white, "敵");
		//DrawBox(0,0,size,size,white,false);
		assert(boss[i].timg > 0);
	SetDrawScreen(DX_SCREEN_BACK);
	boss[i].simg = MakeScreen(20, 20, TRUE);
	SetDrawScreen(boss[i].simg);
	DrawBox(0, 0, 20, 20, white, false);
	assert(boss[i].simg > 0);
	SetDrawScreen(DX_SCREEN_BACK);
	}
	spawncount = 30;//30
	nowdeadnum = 0;
	dainikeitai=1;

	//SetDrawScreen();
	handle = MakeScreen(20, 20, TRUE);
	SetDrawScreen(handle);
	DrawFormatString(0, 0, white, "あ");
	SetDrawScreen(DX_SCREEN_BACK);
	
	
	//kaniimg=MakeScreen(20,20,TRUE);
	//SetDrawScreen(kaniimg);
	DrawBox(0,0,20,20,white,false);
	SetDrawScreen(DX_SCREEN_BACK);
	//DrawExtendGraph(0,0,SCREEN_WIDTH,SCREEN_HEIGHT, handle,false);
	ClearDrawScreen();
	//nazocount=1;

	debugkey.ResetControl();
}
void BossCreate() {
	for (int i = 0; i < BOSSNUMS; i++) {
		if (boss[i].active)continue;
		int spownangle=-130+GetRand(0);
		boss[i].pos.x=sin(PI/180*spownangle)*1000;
		boss[i].pos.y=cos(PI/180*spownangle)*1000;
		boss[i].angle=0;
		boss[i].deadcount=0;
		boss[i].alphanum=255;
		boss[i].active=true;
		//nazocount++;
		return;
	}
}
void BossUpdate() {
	L = L < 60 ? L + 1 : 0;

	//debug用
	if (CheckHitKey(KEY_INPUT_RETURN)) {
		spawncount = 0;
		printfDx("瞬間沸き：ON\n");
	}

	//bossの生成
	if (--spawncount <= 0) {
		BossCreate();
	
		spawncount=5;
	}
	
	//bossの行動
	for (int i = 0; i < BOSSNUMS; i++) {

		if (boss[i].hp < 20) {//第二形態
			L = L < 60 ? L + 2 : 0;
			dainikeitai=-1;
			boss[i].speed=DAINIVELOCITY;
			dainicolorBright=0;

			//ボス子分
			if (cobuncount++ > 30) {
#if  true
				POS _p = GetPlayerPosition();
				double _angle = atan2(_p.x - boss[i].pos.x, _p.y - boss[i].pos.y);
				POS v = {
					cos(DX_PI / 180 * (_angle)) * 0.3,
					sin(DX_PI / 180 * (_angle)) * 0.3
				};
				//3方向へ生成
				BossEnemyCreate(boss[i].pos, v);
#else
				POS _p = GetPlayerPosition();
				for (int j = -1; j < 2; j++) {
					//ちゃんとした方向へ
				double _angle=atan2(_p.x-boss[i].pos.x,_p.y-boss[i].pos.y);
				double radi=j*30/PI*180;
				double num = _angle+radi;
				POS v = {
					cos(DX_PI/180*(_angle+num))*1,
					sin(DX_PI/180*(_angle+num))*1
				};
				//3方向へ生成
				BossEnemyCreate(boss[i].pos,v);
				}
#endif
				cobuncount=0;
			}
		}

		//playerに合わせた動き
		boss[i].pos = PosAdd(boss[i].pos,GetPlayerVX());

			//if (!boss[i].active)continue;
			if (boss[i].deadcount == 0) {//生きとし生ける
				POS m;
				POS _p=GetPlayerPosition();
				m.x =_p.x-boss[i].pos.x;
				m.y =_p.y-boss[i].pos.y;
				float num = sqrtf(m.x * m.x + m.y * m.y);
				m.x = boss[i].speed*(m.x/num)*dainikeitai;
				m.y = boss[i].speed*(m.y/num)*dainikeitai;
				boss[i].pos=PosAdd(boss[i].pos,m);

				boss[i].angle = (2 * PI / 60) * L;
			}
			else if (++boss[i].deadcount < 20) {//死のアニメーション
				int a= L < 60 ? L + 30 : 0;
				boss[i].angle = (2 * PI / 30) * a;

				if (boss[i].deadcount > 10) {
				boss[i].alphanum-=255/10;
				if(boss[i].alphanum<=0)boss[i].alphanum=0;
				}
			}
			else {
				if (++boss[i].deadcount > 60)
					boss[i].active = false;
				
			}

	}

	float n = 1.0f;
	if (CheckHitKey(KEY_INPUT_RETURN))n = 2.0;
	//DrawRotaGraph(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 1.0, (2 * PI / 60) * L, handle, FALSE);
	DrawRotaGraph3 (SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2,8,8,
					n,n, (2 * PI / 60) * L,
					handle, true);
	/*for(int i=0;i<BOSSNUMS;i++)
	DrawRotaGraph3 (boss[i].pos.x, boss[i].pos.y,8,8,
					n+1,n+1, boss[i].angle,
					boss[i].img, true);*/
	printfDx("\n");
	printfDx("倒したbossmyの数：%d\n",nowdeadnum);
	printfDx("\n");

	//Debug用
	if (debugkey.SwitchControl(CheckHitKey(KEY_INPUT_2))) {
		printfDx("KillAll:ON\n");
		for (int i = 0; i < BOSSNUMS; i++) {
			if (!boss[i].active)
				continue;
			boss[i].active=false;
			nowdeadnum++;
		}
		printfDx("\n");
	}

	//for (int i = 0; i < BOSSNUMS; i++) {
	//	if (!boss[i].active) {
	//		return true;
	//	}
	//}
	//return false;
}
void BossDraw() {
	int num = size / 2;
	for (int i = 0; i < BOSSNUMS; i++) {
		if (boss[i].active)
		{
			if (boss[i].deadcount > 0) {
			}
				SetDrawBlendMode(DX_BLENDMODE_ALPHA, boss[i].alphanum);
				SetDrawBright(255,dainicolorBright, dainicolorBright);
				DrawBox(boss[i].pos.x-num,boss[i].pos.y-num, 
						boss[i].pos.x+num,boss[i].pos.y+num, GetColor(255, 255, 255), false);
				//DrawRotaGraph(boss[i].pos.x,boss[i].pos.y,1.0f,boss[i].angle,boss[i].img,TRUE);
				DrawRotaGraph3(boss[i].pos.x, boss[i].pos.y,
					8,8,
					7,7, boss[i].angle,
					boss[i].timg, true);

				int anum=360/BOSSNUMS;
				DrawRotaGraph3(boss[i].pos.x, boss[i].pos.y,
					10,10,
					8,8, boss[i].angle+(PI/180*(45+(i*anum))),
					boss[i].simg, true);

			
		}
	}
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND,0);
	SetDrawBright(255,255,255);
}
void BossDelete() {
	for (int i = 0; i < BOSSNUMS; i++) {
		DeleteGraph(boss[i].timg);
		boss[i].timg= - 1;
		DeleteGraph(boss[i].simg);
		boss[i].simg=-1;
	}
}

bool BossCollisions(POS _pos,int _size, bool _playerflag) {
	for (int i=0; i < BOSSNUMS; i++) {
		if (boss[i].active) {
			if (boss[i].deadcount == 0) {
				SQUAREPOS mob;
				int mobnum = _size / 2;
				mob.tl.x = _pos.x - mobnum;
				mob.tl.y = _pos.y - mobnum;
				mob.br.x = _pos.x + mobnum;
				mob.br.y = _pos.y + mobnum;
				SQUAREPOS _boss;
				int _bossnum = size / 2;
				_boss.tl.x = boss[i].pos.x - _bossnum;
				_boss.tl.y = boss[i].pos.y - _bossnum;
				_boss.br.x = boss[i].pos.x + _bossnum;
				_boss.br.y = boss[i].pos.y + _bossnum;
				if (SquareCollision(mob, _boss)) {
					if (!_playerflag) {
						//boss[i].hp--;
						if (boss[i].hp-- <= 0) {
							boss[i].deadcount = 1;
							nowdeadnum++;
							EffectCreate(boss[i].pos);
						}
					}
					return true;
				}
			}
		}
	}
	return false;
}
int GetBossHp() {
	for (int i = 0; i < BOSSNUMS; i++) 
		return boss[i].hp;
}
POS GetBossPos() {
	for (int i = 0; i < BOSSNUMS; i++) {
		return boss[i].pos;
	}
}