#include"object.h"
#include<DxLib.h>
#include"config.h"
#include"player.h"
#include"common.h"
#include"enemies.h"
#include"barrett.h"
#include"switchControl.h"
#include"item.h"
#include"backimg.h"
#include"effect.h"
#include"boss.h"
#include"clear.h"
#include"gameover.h"
namespace {
	enum SCENE {
		game,
		boss,
		clear,
		over,
		maxscene,
	};
	int mousex=SCREEN_WIDTH /2, 
		mousey=SCREEN_HEIGHT/2;

	OnOff t_key={};
	OnOff debugkey={};
	OnOff debugkey4={};
	int chengenum=0;
	int scene=0;
	int deadnum=100;//敵の死亡数
}


void Init() {
	mousex=SCREEN_WIDTH /2;
	mousey=SCREEN_HEIGHT/2;
	SetMousePoint(mousex,mousey);
	PlayerInit();
	EnemiesInit();
	BarrettInit();
	ItemInit();
	BackimgInit();
	EffectInit();
	BossInit();
	ClearInit();
	GameoverInit();
	scene=0;
	chengenum=0;
	deadnum = 100;//敵の死亡数
	debugkey.ResetControl();
	debugkey4.ResetControl();
}
void SceneGame() {
	BossInit();
	if (GetEneDeadcount() < deadnum) {
		EnemiesUpdate();
	}else if (GetEneDeadcount() >= deadnum) {
		scene=boss;
	}
}
void SceneBoss() {
	//chengenum = GetEneDeadcount();
	BossCreate();
	EnemiesInit();
	BossUpdate();
	if(GetBossHp()<=0)
	scene=clear;
}
void SceneClear() {
	ClearUpdate();
	SetMouseDispFlag(TRUE);
}
void SceneOver() {
	GameoverUpdate();
}
void Update() {
	BackimgUpdate();
	EffectUpdate();
	ItemUpdate();
	GetEneDeadcount(chengenum);
	

	switch (scene) {
	case game:
		SceneGame();
		if (!debugkey.SwitchControl(CheckHitKey(KEY_INPUT_1))) {
			GetMousePoint(&mousex, &mousey);
			SetMousePoint(mousex, mousey);
		}
		break;
	case boss:
		SceneBoss();
		if (!debugkey.SwitchControl(CheckHitKey(KEY_INPUT_1))) {
			GetMousePoint(&mousex, &mousey);
			SetMousePoint(mousex, mousey);
		}
		break;
	case clear:
		SceneClear();
		break;
	case over:
		SceneOver();
		break;
	default:
		DrawBox(0,0,SCREEN_WIDTH,SCREEN_HEIGHT,GetColor(50,50,50),TRUE);
		break;
	}
	if (!PlayerUpdate()) {
		scene = over;
	}

	MouseUpdate();
	BarrettUpdate();
	bool key = CheckHitKey(KEY_INPUT_R);
	if (key)Init();
	/*if (!debugkey.SwitchControl(CheckHitKey(KEY_INPUT_1))) {
		GetMousePoint(&mousex, &mousey);
		SetMousePoint(mousex, mousey);
	}*/
	if (debugkey.SwitchControl(CheckHitKey(KEY_INPUT_1))) {
		printfDx("SCENE：%d\n", scene);
	}
}
void Draw() {

	if (t_key.SwitchControl(CheckHitKey(KEY_INPUT_T))) {
		printfDx("移動　　　　　 ：WASD\n");
		printfDx("ダッシュ移動　 ：LeftShift\n");
		printfDx("弾を打つ　　　 ：MouseLeft\n");
		printfDx("弾を打つオート ：MouseRight\n");
	}
	else {
		printfDx("Tキーで操作説明\n");
		printfDx("Rキーでリセット\n");
	}
	if (debugkey4.SwitchControl(CheckHitKey(KEY_INPUT_4)))
		BackimgDraw();
	EffectDraw();
	ItemDraw();
	PlayerDraw();
	BarrettDraw();
	DrawBox(1,1,SCREEN_WIDTH-1,SCREEN_HEIGHT-1,GetColor(255,255,50),false);
	switch (scene) {
	case game:
		EnemiesDraw();
		break;
	case boss:
		BossDraw();
		break;
	case clear:
		ClearDraw();
		break;
	case over:
		GameoverDraw();
		break;
	default:
		break;
	}
}
void Delete() {
	PlayerRelease();
	EnemiesDelete();
	BarrettDelete();
	BackimgDelete();
	ItemDelete();
	EffectDelete();
	BossDelete();
	ClearDelete();
	GameoverDelete();
}