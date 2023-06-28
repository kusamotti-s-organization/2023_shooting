#include"player.h"
#include<DxLib.h>
#include<assert.h>
#include"common.h"
#include<math.h>
#include<assert.h>
#include"switchControl.h"
#include"barrett.h"
#include<string>
#include"enemies.h"
#include"config.h"
#include"boss.h"
#include"item.h"
#include"bossenemy.h"
#include"randquake.h"
#include"health.h"
static const float PI = 3.14159265359f;

/*======調整用========*/
static const int	MAXFASTLIFE = 3;//最初の体力数
static const int	MAXMUTEKITIME = 3*60;//無敵時間

static const int	MAXTHROWNUM	= 18;	//弾の生成間隔
static const int	MINTHROWNUM	= 8;	//生成間隔の最低値

static const int	MAXSIZE		= 64;	//playerの初期大きさ
static const int	MINSIZE		= 20;	//自機の大きさ最低値

static const int	MOVESPEED	= 2;	//移動時の加速度
static const float	STOPSPEED	= 0.5f;	//移動時の減速度
static const int	MAXSPEED	= 6;	//移動時の最大速度
static const float	RUNSPEED	= 1.3f;	//ダッシュ移動時の速度　(例1.3f倍

namespace {
	POS my={};
	VEC vec;
	int size = MAXSIZE;

	float speed=MOVESPEED;
	const float maxspeed=MAXSPEED;
	const float stopspeed=STOPSPEED;

	bool deadflag=false;
	int mylife= MAXFASTLIFE;

	int mutekitime = 0;
	bool mutekiflag=false;
	int mutekialpha = 51;
	int alphaone = 25;

	int img = -1;
	int throwcount=0;
	float throwtime=MAXTHROWNUM;
	bool keystop = false;

	POS endline={};
	POS fastline={};
	OnOff mrkey;//MouseRight
	OnOff debugkey;

	const int maxlogs = 5;
	POS logs[maxlogs] = {};
	POS nowmy = {};

	int damagese = -1;
	int deadse = -1;
}

void PlayerInit() {
	damagese = LoadSoundMem("data/sound/打撃・ビンタ音.mp3");
	assert(damagese>0);
	deadse= LoadSoundMem("data/sound/クラッシュ.mp3");
	assert(deadse>0);
	ChangeVolumeSoundMem(255*75/100,deadse);
	//img = LoadGraph("data/textuer/hpupd.png");
	//assert(img>0);
	my.x = SCREEN_WIDTH /2;
	my.y = SCREEN_HEIGHT/2;
	vec = {};
	size = MAXSIZE;
	speed=MOVESPEED;
	throwtime = MAXTHROWNUM;
	throwcount = throwtime;
	endline={0,0};
	fastline={0,0};

	keystop = false;
	deadflag=false;
	mrkey	.ResetControl();
	debugkey.ResetControl();
	for (int i = 0; i < maxlogs; i++) {
		logs[i].x =SCREEN_WIDTH /2;
		logs[i].y =SCREEN_HEIGHT/2;
	}
	nowmy.x = SCREEN_WIDTH /2;
	nowmy.y = SCREEN_HEIGHT/2;
	mylife = MAXFASTLIFE;

	mutekitime = 0;
	mutekiflag = false;
	mutekialpha = 51;
	alphaone = 25;
}
void PlayerControlsStraight() {
	/*========何キー=======*/
	bool keyleft = CheckHitKey(KEY_INPUT_A);
	bool keyright = CheckHitKey(KEY_INPUT_D);
	bool keyup = CheckHitKey(KEY_INPUT_W);
	bool keydown = CheckHitKey(KEY_INPUT_S);
	bool keyshift = CheckHitKey(KEY_INPUT_LSHIFT);
	/*======移動操作========*/
	float shiftspeed=1;
	if(keyshift)shiftspeed=RUNSPEED;
	if (keyup && !keydown) {//上
		vec.vy+=-speed;
		if(vec.vy<-maxspeed)vec.vy=-maxspeed*shiftspeed;
	}
	else
		if (keydown && !keyup) {//下
			vec.vy+=speed;
			if (vec.vy>maxspeed)vec.vy=maxspeed*shiftspeed;
		}
	if (keyleft && !keyright) {//左
		vec.vx += -speed;
		if (vec.vx<-maxspeed)vec.vx=-maxspeed*shiftspeed;
	}
	else
		if (keyright && !keyleft) {//右
			vec.vx += speed;
			if (vec.vx>maxspeed)vec.vx=maxspeed*shiftspeed;
		}
}
bool PlayerUpdate() {
	/*========何キー=======*/
	//bool keyleft = CheckHitKey(KEY_INPUT_A);
	//bool keyright = CheckHitKey(KEY_INPUT_D);
	//bool keyup = CheckHitKey(KEY_INPUT_W);
	//bool keydown = CheckHitKey(KEY_INPUT_S);
	//bool keysdflag=keyleft&&keyup||keyright&&keyup||keyleft&&keydown||keyright&&keydown;

	//Lifeの可視化
	HealthSetNum(mylife);

	if (!deadflag) {
		/*======移動操作========*/
		PlayerControlsStraight();

		//画面揺れ
		VECTOR _p = RandQuakeMove();
		POS p ={_p.x,_p.y};
		my= PosAdd(p,my);

		/*============計算系==============*/
		int maxbarrett=GetMaxBarrettNums();
		for(int i=0;i<maxbarrett;i++)
		if (EnemiesCollisions(GetBarrettPosition(i), 2)) {
			size-=2;
			throwtime-=0.8f;
			if(size<=MINSIZE)size=MINSIZE;
			if(throwtime<=MINTHROWNUM)throwtime=MINTHROWNUM;
		}

		float a=0.0f, b= 0.0f, c = 0.0f;
				a = my.x - GetMouseX(),
				b=my.y-GetMouseY(),
				c=sqrtf(a*a+b*b);
			POS lin = { 0,0 };
				lin.x=(a/c)*(size/2+40);
				lin.y=(b/c)*(size/2+40);
		endline.x=-lin.x;
		endline.y=-lin.y;
		
		a = my.x - GetMouseX(),
			b = my.y - GetMouseY(),
			c = sqrtf(a * a + b * b);
		lin.x = (a / c) * size/2;
		lin.y = (b / c) * size/2;
		fastline.x = -lin.x;
		fastline.y = -lin.y;

		float downspeed=stopspeed;//減速する速さ
		//X用
		if(vec.vx>0)vec.vx-=downspeed;//０以上
		else if(vec.vx<0)vec.vx+=downspeed;//０以下
		else vec.vx=0;//動かない様にする為
		//Y用
		if(vec.vy>0)vec.vy-=downspeed;//０以上
		else if(vec.vy<0)vec.vy+=downspeed;//０以下
		else vec.vy=0;//動かない様にする為
		
		/*============弾作成==============*/
		bool autokey = mrkey.SwitchControl(GetMouseInput() & MOUSE_INPUT_RIGHT);
		if (autokey) {
			if (throwcount == 0) {
				POS p = { my.x ,
						my.y  };
				COLOR c = { 255,255,255 };
				float	x=my.x-GetMouseX(),
						y=my.y-GetMouseY();
				//float d=sqrtf(x*x+y*y);

				VEC v = {x,y};
				CreatBarrett(p, v, 5,c);
				throwcount = throwtime;
			}
		}
		/*========debug用=======*/
		if (debugkey.SwitchControl(CheckHitKey(KEY_INPUT_1))) {
			printfDx("\n");
			printfDx("　　　　　　　　　　　　　　　　　　　デバッグ用\n");
			std::string str = "弾発射:";
			str += autokey ? "ON" : "OFF";
			str += "\n";
			printfDx(str.c_str());
			printfDx("投げ間隔:%f\n", throwtime);
			printfDx("自機の大きさ:%d\n", size);
			printfDx("自機の加速度x：%.2f\n", vec.vx);
			printfDx("自機の加速度y：%.2f\n", vec.vy);
			if (true) {
				if (throwcount == 0) {
					POS p = { my.x ,
							my.y };
					COLOR c = { 255,255,255 };
					float	x = my.x - GetMouseX(),
						y = my.y - GetMouseY();
					//float d=sqrtf(x*x+y*y);

					VEC v = { x,y };
					CreatBarrett(p, v, 10, c);
					throwcount = 2;
				}
			}
		}

		/*============弾作成==============*/
		bool key = GetMouseInput() & MOUSE_INPUT_LEFT;
		if (key/*&&!keystop*/) {
			if (throwcount == 0) {
				POS p = { my.x ,
						my.y};
				float	x = my.x - GetMouseX(),
					y = my.y - GetMouseY();
				//float d=sqrtf(x*x+y*y);
				VEC v = { x,y };
				CreatBarrett(p, v, 20);
				throwcount = throwtime;
			}
			mrkey.ResetControl();
		}
		keystop = key;
		if (throwcount > 0)
			throwcount--;

		/*============値代入==============*/
		//nowmy.x+=vec.vx;
		//nowmy.y+=vec.vy;

		if(nowmy.x<0+size/2)nowmy.x=0+size/2;
		if(nowmy.y<0+size/2)nowmy.y=0+size/2;
		if(nowmy.x>SCREEN_WIDTH -(size/2))nowmy.x=SCREEN_WIDTH -(size/2);
		if(nowmy.y>SCREEN_HEIGHT-(size/2))nowmy.y=SCREEN_HEIGHT-(size/2);
#if false	
		//下から移動
		for (int i = 0; i < maxlogs; i++) {
			int num=(i==(maxlogs-1))?2:i+1;
			logs[i]=PosAdd( logs[num],GetPlayerVX());
		}
		logs[maxlogs-1]= nowmy;
#else	
		//上から移動
		for (int i = maxlogs - 1; i > 0; i--) {
			logs[i] = PosAdd(logs[i - 1],PosAdd( GetPlayerVX(),p));
		}
		logs[0] = nowmy;
#endif

		my = logs[0];

		
		
		/*============当たり判定==============*/
		//敵
		if (!debugkey.SwitchControl(CheckHitKey(KEY_INPUT_1)))
			if (EnemiesCollisions(my, size, true) ||
				BossCollisions(my, size,true) ||
				BossEnemyCollisions(my, size,true)
				) {
				if (!mutekiflag) {
					if (mylife != 1) {
						PlaySoundMem(damagese, DX_PLAYTYPE_BACK);
					}
					else if(mylife==1){
						PlaySoundMem(deadse,DX_PLAYTYPE_BACK);
					}
					mutekiflag = true;
					RandQuakeSwitch();
					mylife--;
				}
			}
		//無敵時間
		if (mutekiflag) {
			if (mutekitime++>MAXMUTEKITIME) {
				mutekiflag = false;
				mutekitime = 0;
			}
		}
		//無敵時間演出
		if (mutekialpha>200) {
			alphaone = -alphaone;
		}
		else if(mutekialpha < 50) {
			alphaone = -alphaone;
		}
		mutekialpha += alphaone;//代入

		//アイテム
		if (ItemCollision(my,size/2)) {
			//debug用
			//RandQuakeSwitch();
		}

		/*=============死亡判定===============*/
		if (mylife <= 0) {
			deadflag = true;
		}
		printfDx("\n");
		printfDx("残りLife：%d\n", mylife);
		printfDx("\n");
	}
	return !deadflag;
}
void PlayerDraw() {
	if (!deadflag) {
		SetMouseDispFlag(FALSE);
		int num = size / 2;
		if (mutekiflag) {//無敵演出
			SetDrawBlendMode(DX_BLENDMODE_ALPHA,mutekialpha);
		}
		DrawBox(my.x - num, my.y - num,
			my.x + num, my.y + num, GetColor(255, 255, 255), false);
		
		
		for (int i = 0; i < maxlogs; i++) {//装飾用
			int log=maxlogs;
			int alphanum = 255-(i * log/(i+1)*50);
			SetDrawBlendMode(DX_BLENDMODE_ALPHA,alphanum);
			if (mutekiflag) {//無敵演出
				SetDrawBlendMode(DX_BLENDMODE_ALPHA, mutekialpha);
			}
			float num = size / 2 + i * 3;
			DrawBox(logs[i].x - num, logs[i].y - num,
				logs[i].x + num, logs[i].y + num, GetColor(255, 255, 255), false);
		}
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND,0);
		//DrawCircle(my.x,my.y,num,GetColor(255,255,255),false);

		for (int i = 0; i < 2; i++) {//装飾用
			int num = i == 1 ? num = 1 : num = -1;
			DrawLine(	my.x +fastline.x+ num, my.y +fastline.y+ num,
						endline.x + my.x + num, endline.y + my.y + num, GetColor(200, 155, 155));
		}
		DrawLine(	my.x+fastline.x	, my.y+fastline.y,
					endline.x + my.x, endline.y + my.y, GetColor(255, 20, 40));
		float mx= GetMouseX(), my= GetMouseY();
		int rd = 10;
		DrawCircle(mx,my,rd,GetColor(200,200,200),false);
		DrawCircle(mx,my,rd+1,GetColor(200,200,200),false);
		DrawCircle(mx,my,rd+2,GetColor(200,200,200),false);
		DrawLine(mx-rd,my,mx+rd,my,GetColor(200,200,0),3);//横
		DrawLine(mx,my-rd,mx,my+rd,GetColor(200,200,0),3);//縦
		int mid=2;
		DrawLine(mx-mid,my,mx+mid,my,GetColor(200,50,250),3);
		DrawLine(mx,my-mid,mx,my+mid,GetColor(200,50,250),3);
	}
	else {
		SetMouseDispFlag(TRUE);
	}


	/*========debug用=======*/

	if (debugkey.SwitchControl(CheckHitKey(KEY_INPUT_1))) {
		SetMouseDispFlag(TRUE);
	}

}
void PlayerRelease() {
	DeleteSoundMem(deadse);
	DeleteSoundMem(damagese);
//	DeleteGraph(img);
}
POS GetPlayerPosition() {
	return my;
};
POS GetPlayerVX() {
	POS v;
	v.x = -vec.vx;
	v.y = -vec.vy;
	return v;
}

int GetPlayerLife(){
	return mylife;
}
