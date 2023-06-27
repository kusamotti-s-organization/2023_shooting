#include"player.h"
#include<DxLib.h>
#include"common.h"
#include<math.h>
#include<assert.h>
#include"switchControl.h"
#include"barrett.h"
#include<string>
#include"enemies.h"
#include"config.h"
#include"boss.h"
static const float PI = 3.14159265359f;

/*======�����p========*/
static const int	MAXTHROWNUM	= 18;	//�e�̐����Ԋu
static const int	MINTHROWNUM	= 8;	//�����Ԋu�̍Œ�l
static const int	MAXSIZE		= 64;	//player�̏����傫��
static const int	MINSIZE		= 20;	//���@�̑傫���Œ�l
static const int	MOVESPEED	= 2;	//�ړ����̉����x
static const float	STOPSPEED	= 0.5f;	//�ړ����̌����x
static const int	MAXSPEED	= 6;	//�ړ����̍ő呬�x
static const float	RUNSPEED	= 1.3f;	//�_�b�V���ړ����̑��x�@(��1.3f�{

namespace {
	POS my={};
	VEC vec;
	int size = MAXSIZE;
	float speed=MOVESPEED;
	const float maxspeed=MAXSPEED;
	const float stopspeed=STOPSPEED;
	bool deadflag=false;
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
}

void PlayerInit() {
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
}
void PlayerControlsStraight() {
	/*========���L�[=======*/
	bool keyleft = CheckHitKey(KEY_INPUT_A);
	bool keyright = CheckHitKey(KEY_INPUT_D);
	bool keyup = CheckHitKey(KEY_INPUT_W);
	bool keydown = CheckHitKey(KEY_INPUT_S);
	bool keyshift = CheckHitKey(KEY_INPUT_LSHIFT);
	/*======�ړ�����========*/
	float shiftspeed=1;
	if(keyshift)shiftspeed=RUNSPEED;
	if (keyup && !keydown) {//��
		vec.vy+=-speed;
		if(vec.vy<-maxspeed)vec.vy=-maxspeed*shiftspeed;
	}
	else
		if (keydown && !keyup) {//��
			vec.vy+=speed;
			if (vec.vy>maxspeed)vec.vy=maxspeed*shiftspeed;
		}
	if (keyleft && !keyright) {//��
		vec.vx += -speed;
		if (vec.vx<-maxspeed)vec.vx=-maxspeed*shiftspeed;
	}
	else
		if (keyright && !keyleft) {//�E
			vec.vx += speed;
			if (vec.vx>maxspeed)vec.vx=maxspeed*shiftspeed;
		}
}
bool PlayerUpdate() {
	/*========���L�[=======*/
	bool keyleft = CheckHitKey(KEY_INPUT_A);
	bool keyright = CheckHitKey(KEY_INPUT_D);
	bool keyup = CheckHitKey(KEY_INPUT_W);
	bool keydown = CheckHitKey(KEY_INPUT_S);
	bool keysdflag=keyleft&&keyup||keyright&&keyup||keyleft&&keydown||keyright&&keydown;

	if (!deadflag) {
		/*======�ړ�����========*/
		PlayerControlsStraight();

		/*============�v�Z�n==============*/
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

		float downspeed=stopspeed;//�������鑬��
		//X�p
		if(vec.vx>0)vec.vx-=downspeed;//�O�ȏ�
		else if(vec.vx<0)vec.vx+=downspeed;//�O�ȉ�
		else vec.vx=0;//�����Ȃ��l�ɂ����
		//Y�p
		if(vec.vy>0)vec.vy-=downspeed;//�O�ȏ�
		else if(vec.vy<0)vec.vy+=downspeed;//�O�ȉ�
		else vec.vy=0;//�����Ȃ��l�ɂ����
		
		/*============�e�쐬==============*/
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
		/*========debug�p=======*/
		if (debugkey.SwitchControl(CheckHitKey(KEY_INPUT_1))) {
			printfDx("\n");
			printfDx("�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�f�o�b�O�p\n");
			std::string str = "�e����:";
			str += autokey ? "ON" : "OFF";
			str += "\n";
			printfDx(str.c_str());
			printfDx("�����Ԋu:%f\n", throwtime);
			printfDx("���@�̑傫��:%d\n", size);
			printfDx("���@�̉����xx�F%.2f\n", vec.vx);
			printfDx("���@�̉����xy�F%.2f\n", vec.vy);
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

		/*============�e�쐬==============*/
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

		/*============�l���==============*/
		nowmy.x+=vec.vx;
		nowmy.y+=vec.vy;

		if(nowmy.x<0+size/2)nowmy.x=0+size/2;
		if(nowmy.y<0+size/2)nowmy.y=0+size/2;
		if(nowmy.x>SCREEN_WIDTH -(size/2))nowmy.x=SCREEN_WIDTH -(size/2);
		if(nowmy.y>SCREEN_HEIGHT-(size/2))nowmy.y=SCREEN_HEIGHT-(size/2);

		for (int i = 0; i < maxlogs; i++) {
			int num=(i==(maxlogs-1))?2:i+1;
			logs[i]=logs[num];
		}
		logs[maxlogs-1]=nowmy;

		my = logs[0];

		
		
		/*============�����蔻��==============*/
		if (!debugkey.SwitchControl(CheckHitKey(KEY_INPUT_1)))
		if (EnemiesCollisions(my, size, true)||
			BossCollisions(my,size)
			) {
			deadflag = true;
		}
		
	}
	return !deadflag;
}
void PlayerDraw() {
	if (!deadflag) {
		SetMouseDispFlag(FALSE);
		int num = size / 2;
		DrawBox(my.x - num, my.y - num,
			my.x + num, my.y + num, GetColor(255, 255, 255), false);
		for (int i = 0; i < maxlogs; i++) {//�����p
			int log=maxlogs;
			int alphanum = 255-(i * log/(i+1)*50);
			SetDrawBlendMode(DX_BLENDMODE_ALPHA,alphanum);
			float num = size / 2 + i * 3;
			DrawBox(logs[i].x - num, logs[i].y - num,
				logs[i].x + num, logs[i].y + num, GetColor(255, 255, 255), false);
		}
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND,0);
		//DrawCircle(my.x,my.y,num,GetColor(255,255,255),false);

		for (int i = 0; i < 2; i++) {//�����p
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
		DrawLine(mx-rd,my,mx+rd,my,GetColor(200,200,0),3);//��
		DrawLine(mx,my-rd,mx,my+rd,GetColor(200,200,0),3);//�c
		int mid=2;
		DrawLine(mx-mid,my,mx+mid,my,GetColor(200,50,250),3);
		DrawLine(mx,my-mid,mx,my+mid,GetColor(200,50,250),3);
	}
	else {
		SetMouseDispFlag(TRUE);
	}


	/*========debug�p=======*/

	if (debugkey.SwitchControl(CheckHitKey(KEY_INPUT_1))) {
		SetMouseDispFlag(TRUE);
	}

}
void PlayerRelease() {
//	DeleteGraph(img);
}
POS GetPlayerPosition() {
	return my;
};