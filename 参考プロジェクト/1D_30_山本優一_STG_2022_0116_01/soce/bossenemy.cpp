#include"bossenemy.h"
#include<DxLib.h>
#include<assert.h>
#include"config.h"
#include"common.h"
#include<math.h>
#include"player.h"
#include"switchControl.h"
#include"effect.h"

#define PI 3.14159265359

static const float VELOCITY=2.7f;
static const int ENEMYHP = 1;
static const int ENENUMS = 50;
static const int ENESIZE = 64/2;
namespace {
	float L = 0;//Rotate(kari
	int white = GetColor(255, 255, 255);
	struct ENES {
		bool active = false;
		POS pos= { -100,-100 };
		POS vec = {};
		double angle = 0.0f;
		int hp = ENEMYHP;
		int deadcount = 0;
		int timg = -1;
		int simg = -1;
		int alphanum=255;
	};
	
	ENES ene[ENENUMS];
	int size = ENESIZE;
	int spawncount = 0;//30
	int activecount = 0;

	OnOff debugkey;
	int deadse = -1;
}


void BossEnemyInit() {
	deadse = LoadSoundMem("data/sound/ツッコミ・仕切り音.mp3");
	assert(deadse > 0);
	
	for (int i = 0; i < ENENUMS; i++) {
		ene[i]={};
		ene[i].timg = MakeScreen(20, 20, TRUE);
		SetDrawScreen(ene[i].timg);
		SetFontSize(8);
		DrawFormatString(0, 0, white, "子分");
		assert(ene[i].timg > 0);
	ene[i].simg = MakeScreen(20, 20, TRUE);
	SetDrawScreen(ene[i].simg);
	DrawBox(0, 0, 20, 20, white, false);
	assert(ene[i].simg > 0);
	}
	SetDrawScreen(DX_SCREEN_BACK);
	SetFontSize(16);

	spawncount = 30;
	debugkey.ResetControl();
	activecount = 0;

}
void BossEnemyCreate(POS _pos,POS _vec) {
	for (int i = 0; i < ENENUMS; i++) {
		if (ene[i].active)continue;
		int spownangle=-130+GetRand(360);
		ene[i].pos=_pos;
		ene[i].vec=_vec;
		ene[i].angle=0;
		ene[i].deadcount=0;
		ene[i].hp=ENEMYHP;
		ene[i].alphanum=255;
		ene[i].active=true;
		activecount++;
		return;
	}
}
void BossEnemyUpdate() {
	L = L < 60 ? L +0.5f : 0;

	//debug用
	if (CheckHitKey(KEY_INPUT_RETURN)) {
		spawncount = 0;
		printfDx("瞬間沸き：ON\n");
	}

	//eneの生成
	
	
	//eneの行動
	for (int i = 0; i < ENENUMS; i++) {
		if (!ene[i].active)continue;

		//playerに合わせた動き
		ene[i].pos = PosAdd(ene[i].pos,GetPlayerVX());

		

			//if (!ene[i].active)continue;
			if (ene[i].deadcount == 0) {//生きとし生ける行動
				ene[i].pos=PosAdd(ene[i].pos,ene[i].vec);
				ene[i].angle = (2 * PI / 60) * L;
			}
			else if (++ene[i].deadcount < 20) {//死のアニメーション
				int a= L < 60 ? L + 25 : 0;
				ene[i].angle = (2 * PI / 30) * a;

				if (ene[i].deadcount > 10) {
				ene[i].alphanum-=255/10;
				if(ene[i].alphanum<=0)ene[i].alphanum=0;
				}
			}
			else {
				if (++ene[i].deadcount > 30)
				activecount--;
					ene[i].active = false;
			}

	}
	float n = 1.0f;
	if (CheckHitKey(KEY_INPUT_RETURN))n = 2.0;

	//Debug用
	if (debugkey.SwitchControl(CheckHitKey(KEY_INPUT_2))) {
		printfDx("KillAll:ON\n");
		for (int i = 0; i < ENENUMS; i++) {
			if (!ene[i].active)
				continue;
			ene[i].active=false;
		}
		printfDx("\n");
	}
}
void BossEnemyDraw() {
	int num = size / 2;
	for (int i = 0; i < ENENUMS; i++) {
		if (ene[i].active)
		{
			if (ene[i].deadcount > 0) {
			}
				SetDrawBlendMode(DX_BLENDMODE_ALPHA, ene[i].alphanum);
				DrawBox(ene[i].pos.x-num,ene[i].pos.y-num, 
						ene[i].pos.x+num,ene[i].pos.y+num, GetColor(255, 255, 255), false);
				//DrawRotaGraph(ene[i].pos.x,ene[i].pos.y,1.0f,ene[i].angle,ene[i].img,TRUE);
				DrawRotaGraph3(ene[i].pos.x, ene[i].pos.y,
					8,8,
					2.0, 2.0, ene[i].angle,
					ene[i].timg, true);

				int anum=360/ENENUMS;
				DrawRotaGraph3(ene[i].pos.x, ene[i].pos.y,
					10,10,
					3,3, ene[i].angle+(PI/180*(45+(i*anum))),
					ene[i].simg, true);

			
		}
	}
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND,0);
}
void BossEnemyDelete() {
	DeleteSoundMem(deadse);
	for (int i = 0; i < ENENUMS; i++) {
		DeleteGraph(ene[i].timg);
		ene[i].timg= - 1;
		DeleteGraph(ene[i].simg);
		ene[i].simg=-1;
	}
}

bool BossEnemyCollisions(POS _pos,int _size,bool _playerflag) {
	for (int i=0; i < ENENUMS; i++) {
		if (ene[i].active) {
			if (ene[i].deadcount == 0) {
				SQUAREPOS mob;
				int mobnum = _size / 2;
				mob.tl.x = _pos.x - mobnum;
				mob.tl.y = _pos.y - mobnum;
				mob.br.x = _pos.x + mobnum;
				mob.br.y = _pos.y + mobnum;
				SQUAREPOS _ene;
				int _enenum = size / 2;
				_ene.tl.x = ene[i].pos.x - _enenum;
				_ene.tl.y = ene[i].pos.y - _enenum;
				_ene.br.x = ene[i].pos.x + _enenum;
				_ene.br.y = ene[i].pos.y + _enenum;
				if (SquareCollision(mob, _ene)) {
					if (!_playerflag) {
						//ene[i].hp--;
						//enemyのHpが０になったら死亡
						if (ene[i].hp-- <  0) {
							ene[i].deadcount = 1;
						}
						ene[i].active=false;
						
						//ene[i].deadcount = 1;
						EffectCreate(ene[i].pos);
						PlaySoundMem(deadse, DX_PLAYTYPE_BACK);

					}else {
						ene[i].active = false;
					}
					return true;
				}
			}
		}
	}
	return false;
}
