#include"barrett.h"
#include<DxLib.h>
#include<assert.h>
#include"common.h"
#include<assert.h>
#include<math.h>
#include"config.h"
#include"enemies.h"
#include"boss.h"
#include"player.h"
#include"bossenemy.h"

static const double PI =3.14159265359f;

/*======í≤êÆóp========*/
static const int MAXBARRETTS = 40;//íeÇÃç≈ëÂêî

namespace {
	const int maxlog=10;
	struct BARRETTS {
		bool active=false;
		POS nowpos = {0,0};
		VEC vec = {};
		double angle=0;
		double speed=0;
		int size=30;
		int img=-1;
		COLOR color={255,255,255};
		POS logs[maxlog]={};
	};
	static const int barrettnums = MAXBARRETTS;
	BARRETTS barrett[barrettnums];

	int blse = -1;
	int brse = -1;
}

void BarrettInit() {
	blse = LoadSoundMem("data/sound/ÉWÉÉÉìÉv.mp3");
	assert(blse>0);
	brse = LoadSoundMem("data/sound/ÉrÅ[ÉÄâπ.mp3");
	assert(brse>0);
	ChangeVolumeSoundMem(255 * 65 / 100,brse);
	ChangeVolumeSoundMem(255 * 80 / 100,blse);
	for (int i = 0; i < barrettnums; i++) {
		barrett[i] = {};
		//barrett[i].nowpos = GetPlayerPosition();
		barrett[i].active = false;
		barrett[i].img = MakeScreen(30, 30, TRUE);
		SetDrawScreen(barrett[i].img);
		DrawFormatString(15-8, 15-8, GetColor(255,200,100), "íe");
		DrawCircle(0+15, 0+15,10, GetColor(0,255,255), false);
		assert(barrett[i].img > 0);
		SetDrawScreen(DX_SCREEN_BACK);
	}
		ClearDrawScreen();
}
void BarrettReset(int i) {
	barrett[i].nowpos = {};
}
void BarrettUpdate() {
	for (int i = 0; i < barrettnums; i++) {
		//if (!barrett[i].active) 
		//	continue;
		if (barrett[i].active) {


			//playerÇ…çáÇÌÇπÇΩìÆÇ´
			barrett[i].nowpos = PosAdd(barrett[i].nowpos, GetPlayerVX());

			//à⁄ìÆèàóù
			barrett[i].nowpos.x += barrett[i].vec.vx;
			barrett[i].nowpos.y += barrett[i].vec.vy;

			POS vp = GetPlayerVX();
			////íeìπpos ämï€
			for (int j = maxlog - 1; j > 0; j--) {
				//int num = (j == maxlog) ? num = maxlog - 1 : num = j;
				barrett[i].logs[j].x = barrett[i].logs[j - 1].x + vp.x;
				barrett[i].logs[j].y = barrett[i].logs[j - 1].y + vp.y;
			}
			barrett[i].logs[0] = barrett[i].nowpos;

			//éÄñSÉtÉâÉO
			if (barrett[i].nowpos.x > SCREEN_WIDTH ||
				barrett[i].nowpos.x<0 ||
				barrett[i].nowpos.y>SCREEN_HEIGHT ||
				barrett[i].nowpos.y < 0
				) {
				BarrettReset(i);
				barrett[i].active = false;
			}

			//ìGÇ…ìñÇΩÇ¡ÇΩéû
			POS collider = { barrett[i].nowpos.x,barrett[i].nowpos.y };
			if (EnemiesCollisions(collider, 2) ||
				BossCollisions(collider, 2)||
				BossEnemyCollisions(collider,2)
				){
				BarrettReset(i);
				barrett[i].active = false;
			}
		}
		//debugóp
		if(i>10)continue;
#if false
		printfDx("barrett%2dx %lf\n", i, barrett[i].nowpos.x);
		printfDx("barrett%2dy %lf\n", i, barrett[i].nowpos.y);
		printfDx("TorF%2dy %d\n", i, barrett[i].active);
#endif
	}


	/*============íeçÏê¨==============*/
	/*for (int i = 0; i < barrettnums; i++) {
		if (barrett[i].active)continue;
		if (GetMouseInput() & MOUSE_INPUT_RIGHT) {
			POS a = { 5,5 };
			CreatBarrett(a, 0.0f, 5.0f, GetColor(222, 111, 0xf6));
			break;
		}
	}*/
}
void BarrettDraw() {
	for (int i = 0; i < barrettnums; i++) {
		if (barrett[i].active) {
			SetDrawBright(barrett[i].color.r, barrett[i].color.g, barrett[i].color.b);
			
			if (!CheckHitKey(KEY_INPUT_K)) {
				for (int j = 0; j < maxlog; j++) {
					int pal = 150 / (j + 1);
					SetDrawBlendMode(DX_BLENDMODE_ALPHA, pal);
					//SetDrawBlendMode(DX_BLENDMODE_ADD, pal);

					DrawRotaGraph3(barrett[i].logs[j].x, barrett[i].logs[j].y,
						barrett[i].size / 2, barrett[i].size / 2,
						0.5f, 1.5f, barrett[i].angle, barrett[i].img, true);
				}
			}
				SetDrawBlendMode(DX_BLENDMODE_NOBLEND,0);

			if (i % 2 == 0)
				SetDrawBlendMode(DX_BLENDMODE_ADD, 255);
			//DrawCircle(barrett[i].nowpos.x,barrett[i].nowpos.y,barrett[i].size/2,GetColor(barrett[i].color.r, barrett[i].color.g, barrett[i].color.b),false);
			//DrawGraph(barrett[i].nowpos.x-barrett[i].size/2,barrett[i].nowpos.y -barrett[i].size/2,barrett[i].img,true);
			DrawRotaGraph3(barrett[i].nowpos.x, barrett[i].nowpos.y,
				barrett[i].size / 2, barrett[i].size / 2,
				0.5f, 1.5f, barrett[i].angle, barrett[i].img, true);
			DrawRotaGraph3(barrett[i].nowpos.x, barrett[i].nowpos.y,
				barrett[i].size / 2, barrett[i].size / 2,
				0.5f, 0.7f, barrett[i].angle, barrett[i].img, true);

			
		}

	}
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	SetDrawBright(255, 255, 255);
}
void BarrettDelete() {
	DeleteSoundMem(blse);
	DeleteSoundMem(brse);
	for (int i = 0; i < barrettnums; i++) {
		DeleteGraph(barrett[i].img);
		barrett[i].img = -1;
	}
}

void CreatBarrett(POS _pos,VEC _vec,double _speed,COLOR _color) {
	for (int i = 0; i < barrettnums; i++) {
		if (barrett[i].active)
			continue;
		float a = 0.0f, b = 0.0f, c = 0.0f;
		a = _pos.x - GetMouseX(),
			b = _pos.y - GetMouseY(),
			c = sqrtf(a * a + b * b);
		POS lin = { 0,0 };
		lin.x = -((a / c) * (64/2+40));
		lin.y = -((b / c) * (64/2+40));
		barrett[i].nowpos=PosAdd(lin,_pos);
		float cnum=sqrtf(_vec.vx* _vec.vx+ _vec.vy* _vec.vy);
		VEC temp = {_speed*(_vec.vx/cnum),
					_speed*(_vec.vy/cnum)};
		barrett[i].vec.vx=-temp.vx;
		barrett[i].vec.vy=-temp.vy;
		barrett[i].speed=_speed;
		barrett[i].angle =- atan2(_vec.vx,_vec.vy);
		if (_color.r==-1) {
			PlaySoundMem(brse, DX_PLAYTYPE_BACK);
			COLOR cols;
			int cnum = i % 3;
			int normalnum=205+GetRand(50);
			switch (cnum)
			{
			case 0:
				cols.r=GetRand(255);
				cols.g=normalnum;
				cols.b= normalnum;
				break;
			case 1:
				cols.r=normalnum;
				cols.g=GetRand(255);
				cols.b=normalnum;
				break;
			case 2:
				cols.r=normalnum;
				cols.g=normalnum;
				cols.b=GetRand(255);
				break;
			default:
				break;
			}
			_color=cols;
		}
		else {
			PlaySoundMem(blse, DX_PLAYTYPE_BACK);
		}
		barrett[i].color= _color;
		barrett[i].active =true;
		for (int j = 0; j < maxlog; j++) {
			barrett[i].logs[j].x=barrett[i].nowpos.x;
			barrett[i].logs[j].y=barrett[i].nowpos.y;
		}
		return;
	}
}
POS GetBarrettPosition(int i) {
	return barrett[i].nowpos;
}
int GetMaxBarrettNums() {
	return MAXBARRETTS;
}