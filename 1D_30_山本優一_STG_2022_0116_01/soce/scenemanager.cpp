#include"scenemanager.h"
#include<DxLib.h>
#include<assert.h>
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
#include"bossSpawnWarning.h"
#include"bosshoukou.h"
#include"fire.h"
#include"works.h"
#include"bossenemy.h"
#include"randquake.h"
#include"title.h"
#include"health.h"
namespace {
	enum SCENE {
		title,
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
	int nextscene=scene;
	int deadnum=100;//敵の死亡数
	bool keystop=false;

	bool warningflag=false;

	int bgm = -1;
	int startse = -1;
	int clearbgm = -1;
	int overbgm = -1;
}


void SceneInit() {
	bgm = LoadSoundMem("data/sound/Reflect.mp3");
	assert(bgm>0);
	ChangeVolumeSoundMem(255*80/100,bgm);
	startse = LoadSoundMem("data/sound/合戦が始まる法螺貝の音.mp3");
	assert(startse > 0);
	clearbgm = LoadSoundMem("data/sound/成功した時の嬉しい音.mp3");
	assert(clearbgm > 0);
	overbgm = LoadSoundMem("data/sound/失敗した時の残念な音.mp3");
	assert(overbgm > 0);
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
	WarningInit();
	BossHoukouInit();
	FireInit();
	WorksInit();
	BossEnemyInit();
	RandQuakeInit();
	TitleInit();
	HealthInit();
	scene=0;
	chengenum=0;
	deadnum = 100;//敵の死亡数
	debugkey.ResetControl();
	debugkey4.ResetControl();
	warningflag=false;
	nextscene = scene;
}
void SceneGame() {
	if (GetEneDeadcount() < deadnum) {
		EnemiesUpdate();
	}else if (GetEneDeadcount() >= deadnum) {
		scene=boss;
	}
	HealthUpdate();
}
void SceneBoss() {
	//chengenum = GetEneDeadcount();
	if (!warningflag) {
		warningflag=WarningUpdate();
	}
	BossCreate();
	BossUpdate();
	BossHoukouUpdate();
	BossEnemyUpdate();
	HealthUpdate();
	if (GetBossHp() <= 0) {
	scene=clear;
	PlaySoundMem(clearbgm,DX_PLAYTYPE_BACK);
	}
}
void SceneClear() {
	FireUpdate();
	WorksUpdate();
	ClearUpdate();
	SetMouseDispFlag(TRUE);
}
void SceneOver() {
	GameoverUpdate();
}
void SceneUpdate() {
	//resset key R
	bool key = CheckHitKey(KEY_INPUT_R);
	if (key && !keystop) {
		SceneDelete();
		SceneInit();
		EnemiesInit();
		keystop = true;
	}
	else if (!key) {
		keystop = false;
	}
	if (scene != title) {
		BackimgUpdate();
		EffectUpdate();
		GetEneDeadcount(chengenum);
		
		ItemUpdate();
	}
	

	switch (scene) {
	case title:
		if (CheckSoundMem(bgm) == 1)
			StopSoundMem(bgm);
		if (TitleUpdate()) {
			scene++;
			PlaySoundMem(startse, DX_PLAYTYPE_BACK);
			PlaySoundMem(bgm, DX_PLAYTYPE_LOOP);
		}
		break;
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
		if (CheckSoundMem(bgm) == 1)
			StopSoundMem(bgm);
		SceneClear();
		break;
	case over:
		if (CheckSoundMem(bgm) == 1) {
			PlaySoundMem(overbgm, DX_PLAYTYPE_BACK);
			StopSoundMem(bgm);
		}
		SceneOver();
		break;
	default:
		DrawBox(0,0,SCREEN_WIDTH,SCREEN_HEIGHT,GetColor(50,50,50),TRUE);
		break;
	}
	
	
	if (scene != title) {
		MouseUpdate();
		if (!PlayerUpdate()) {
			scene = over;
		}
		BarrettUpdate();

		if (scene != clear) {
		RandQuakeUpdate();
		}
	}
	
	//debug用
	if (debugkey.SwitchControl(CheckHitKey(KEY_INPUT_1))) {
		printfDx("SCENE：%d\n", scene);
		printfDx("SCENEgame =  0\n");
		printfDx("SCENEboss =  1\n");
		printfDx("SCENEclear=  2\n");
		printfDx("SCENEover =  3\n");

		if (CheckHitKey(KEY_INPUT_NUMPAD0)) {
			scene = game;
		}
		if (CheckHitKey(KEY_INPUT_NUMPAD1)) {
			scene = boss;
		}if (CheckHitKey(KEY_INPUT_NUMPAD2)) {
			scene = clear;
		}if (CheckHitKey(KEY_INPUT_NUMPAD3)) {
			scene = over;
		}
	}
}
void SceneDraw() {

	if (scene != title) {
		if (t_key.SwitchControl(CheckHitKey(KEY_INPUT_T))) {
			printfDx("移動　　　　　 ：WASD\n");
			printfDx("ダッシュ移動　 ：LeftShift\n");
			printfDx("弾を打つ　　　 ：MouseLeft\n");
			printfDx("弾を打つオート ：MouseRight\n");
		}
		else {

			printfDx("Tキーで操作説明\n");
			POS p = GetPlayerPosition();

			//debug用
			/*printfDx("X=%.2f\n",p.x);
			printfDx("Y=%.2f\n",p.y);*/
		}
	}

	if (debugkey4.SwitchControl(CheckHitKey(KEY_INPUT_4)))
		BackimgDraw();
	if (scene != title) {

	EffectDraw();
	ItemDraw();
	PlayerDraw();
	BarrettDraw();
	RandQuakeDraw();
	}

	VECTOR p = RandQuakeMove();
	if (RandQuakeGetActive()) {
	DrawBox(1+p.x,1+p.y,SCREEN_WIDTH-1+p.x,SCREEN_HEIGHT-1+p.y,GetColor(255,255,50),false);
	}
	else {
		DrawBox(1, 1,SCREEN_WIDTH - 1 , SCREEN_HEIGHT-1, GetColor(255, 255, 50), false);
	}

	
	switch (scene) {
	case title:
		TitleDraw();
		break;
	case game:
		EnemiesDraw();
		HealthDraw();
		break;
	case boss:
		if(!warningflag)WarningDraw();
		BossHoukouDraw();
		BossDraw();
		BossEnemyDraw();
		HealthDraw();
		break;
	case clear:
		FireDraw();
		WorksDraw();
		ClearDraw();
		break;
	case over:
		GameoverDraw();
		break;
	default:
		break;
	}

}
void SceneDelete() {
	DeleteSoundMem(bgm);
	DeleteSoundMem(startse);
	DeleteSoundMem(clearbgm);
	DeleteSoundMem(overbgm);

	PlayerRelease();
	EnemiesDelete();
	BarrettDelete();
	BackimgDelete();
	ItemDelete();
	EffectDelete();
	BossDelete();
	ClearDelete();
	GameoverDelete();
	WarningDelete();
	BossHoukouDelete();
	FireDelete();
	WorksDelete();
	BossEnemyDelete();
	RandQuakeDelete();
	TitleDelete();
	HealthDelete();
}

int GetNowScene(){
	return scene;
}
