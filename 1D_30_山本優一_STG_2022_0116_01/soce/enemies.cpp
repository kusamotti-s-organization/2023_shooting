#include"enemies.h"
#include<DxLib.h>
#include<assert.h>
#include"config.h"
#include"common.h"
#include<math.h>
#include"player.h"
#include"switchControl.h"
#include"effect.h"
#include"randquake.h"

#define PI 3.14159265359

static const float VELOCITY=2.7f;
static const int ENEMYHP = 1;
namespace {
	float L = 0;//Rotate(kari
	int white = GetColor(255, 255, 255);
	struct ENES {
		bool active = false;
		POS pos= {0,0};
		double angle = 0.0f;
		int hp = ENEMYHP;
		int deadcount = 0;
		int timg = -1;
		int simg = -1;
		int alphanum=255;
	};
	static const int ENENUMS = 20;
	ENES ene[ENENUMS];
	int size = 64;
	int spawncount = 0;//30
	int nowdeadnum=0;
	int activecount = 0;

	//float nazocount = 1;
	int handle = 0;
	OnOff debugkey;

	int deadse = -1;
}


void EnemiesInit() {
	deadse = LoadSoundMem("data/sound/�c�b�R�~�E�d�؂艹.mp3");
	assert(deadse > 0);
	ChangeVolumeSoundMem(255*80/100,deadse);

	for (int i = 0; i < ENENUMS; i++) {
		ene[i]={};
		/*ene[i].pos={};
		ene[i].angle={};
		ene[i].active = false;
		ene[i].aphpanum=255;
		*/ene[i].timg = MakeScreen(20, 20, TRUE);
		SetDrawScreen(ene[i].timg);
		DrawFormatString(0, 0, white, "�G");
		//DrawBox(0,0,size,size,white,false);
		assert(ene[i].timg > 0);
	SetDrawScreen(DX_SCREEN_BACK);
	ene[i].simg = MakeScreen(20, 20, TRUE);
	SetDrawScreen(ene[i].simg);
	DrawBox(0, 0, 20, 20, white, false);
	assert(ene[i].simg > 0);
	SetDrawScreen(DX_SCREEN_BACK);
	}
	spawncount = 30;//30
	nowdeadnum = 0;

	//SetDrawScreen();
	handle = MakeScreen(20, 20, TRUE);
	SetDrawScreen(handle);
	DrawFormatString(0, 0, white, "��");
	SetDrawScreen(DX_SCREEN_BACK);
	
	
	//kaniimg=MakeScreen(20,20,TRUE);
	//SetDrawScreen(kaniimg);
	DrawBox(0,0,20,20,white,false);
	SetDrawScreen(DX_SCREEN_BACK);
	//DrawExtendGraph(0,0,SCREEN_WIDTH,SCREEN_HEIGHT, handle,false);
	ClearDrawScreen();
	//nazocount=1;

	debugkey.ResetControl();
	activecount = 0;

}
void CreateEnes() {
	for (int i = 0; i < ENENUMS; i++) {
		if (ene[i].active)continue;
		int spownangle=-130+GetRand(360);
		ene[i].pos.x=sin(PI/180*spownangle)*1000;
		ene[i].pos.y=cos(PI/180*spownangle)*1000;
		ene[i].angle=0;
		ene[i].deadcount=0;
		ene[i].hp=ENEMYHP;
		ene[i].alphanum=255;
		ene[i].active=true;
		activecount++;
		//nazocount++;
		return;
	}
}
void EnemiesUpdate() {
	L = L < 60 ? L + 1 : 0;

	//debug�p
	if (CheckHitKey(KEY_INPUT_RETURN)) {
		spawncount = 0;
		printfDx("�u�ԕ����FON\n");
	}

	//ene�̐���
	if (--spawncount <= 0) {
		//if(activecount<5)
		CreateEnes();

		if (nowdeadnum <= 20) {
			spawncount = 50;
		}
		else if (nowdeadnum <= 50) {
			spawncount=40;
		}
		else if(nowdeadnum<=100){
			spawncount=30;
		}
		else {
			spawncount=5;
		}

	}
	
	//ene�̍s��
	for (int i = 0; i < ENENUMS; i++) {
		if (!ene[i].active)continue;

		//player�ɍ��킹������
		ene[i].pos = PosAdd(ene[i].pos,GetPlayerVX());
		if (RandQuakeGetActive()) {
			VECTOR _p = RandQuakeMove();
			POS pos = {_p.x,_p.y};
			ene[i].pos = PosAdd(ene[i].pos,pos);
		}
		

			//if (!ene[i].active)continue;
			if (ene[i].deadcount == 0) {//�����Ƃ�������s��
				POS m;
				POS _p=GetPlayerPosition();
				m.x =_p.x-ene[i].pos.x;
				m.y =_p.y-ene[i].pos.y;
				float num = sqrtf(m.x * m.x + m.y * m.y);
				m.x = VELOCITY*(m.x/num);
				m.y = VELOCITY*(m.y/num);
				ene[i].pos=PosAdd(ene[i].pos,m);
				//ene[i].pos.x+=VELOCITY;
				//ene[i].pos.y+=VELOCITY;
				//if(nazocount>10)nazocount=-nazocount;
				//ene[i].pos.x-= nazocount;
				ene[i].angle = (2 * PI / 60) * L;
				/*if (ene[i].pos.x > SCREEN_WIDTH+size ||
					ene[i].pos.x < 0-size ||
					ene[i].pos.y > SCREEN_HEIGHT  ||
					ene[i].pos.y < 0-size) {
					ene[i].active = false;
				}*/

			}
			else if (++ene[i].deadcount < 20) {//���̃A�j���[�V����
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
	//DrawRotaGraph(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 1.0, (2 * PI / 60) * L, handle, FALSE);
	VECTOR p = RandQuakeMove();
	DrawRotaGraph3 (SCREEN_WIDTH / 2+p.x, SCREEN_HEIGHT / 2+p.y,8,8,
					n,n, (2 * PI / 60) * L,
					handle, true);
	/*for(int i=0;i<ENENUMS;i++)
	DrawRotaGraph3 (ene[i].pos.x, ene[i].pos.y,8,8,
					n+1,n+1, ene[i].angle,
					ene[i].img, true);*/
	printfDx("\n");
	printfDx("�|����Enemy�̐��F%d\n",nowdeadnum);
	printfDx("\n");

	//Debug�p
	if (debugkey.SwitchControl(CheckHitKey(KEY_INPUT_2))) {
		printfDx("KillAll:ON\n");
		for (int i = 0; i < ENENUMS; i++) {
			if (!ene[i].active)
				continue;
			ene[i].active=false;
			nowdeadnum++;
		}
		printfDx("\n");
	}
}
void EnemiesDraw() {
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
void EnemiesDelete() {
	DeleteSoundMem(deadse);
	for (int i = 0; i < ENENUMS; i++) {
		DeleteGraph(ene[i].timg);
		ene[i].timg= - 1;
		DeleteGraph(ene[i].simg);
		ene[i].simg=-1;
	}
}

bool EnemiesCollisions(POS _pos,int _size,bool _playerflag) {
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
						//enemy��Hp���O�ɂȂ����玀�S
						if (ene[i].hp-- <  0) {
							ene[i].deadcount = 1;
						}
						ene[i].active=false;
						
						//ene[i].deadcount = 1;
						nowdeadnum++;
						EffectCreate(ene[i].pos);
						PlaySoundMem(deadse,DX_PLAYTYPE_BACK);
					}
					else {
						ene[i].active=false;
					}
					return true;
				}
			}
		}
	}
	return false;
}

int GetEneDeadcount(int num) {
	return nowdeadnum+=num;
}