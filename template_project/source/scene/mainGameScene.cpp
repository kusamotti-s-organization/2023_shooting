#include"mainGameScene.h"

#include<DxLib.h>
#include<cmath>
#include"../main/config.h"
#include"../object/player.h"
#include"../object/enemy.h"
#include"../object/bullet.h"
#include"../object/backgroundGraphic.h"
#include"../object/destroyEffect.h"
#include"../object/wave.h"

namespace {
	int count;
	bool feedoutEnd;
}

void MainGameSceneInit(){
	count = 0;
	feedoutEnd = false;

	BackgroundGraphicInit();
	EnemyInit();
	PlayerInit();
	BulletInit();

	DestroyEffectInit();
	WaveInit();
}

void MainGameSceneUpdate(){
	if ( !feedoutEnd) {
		++count;

		if (count > 90) {
			feedoutEnd = true;
		}

		return;
	}
	PlayerUpdate();
	BulletUpdate();
	WaveUpdate();
	EnemyUpdate();
	BackgroundGraphicUpdate();

	DestroyEffectUpdate();
}

void MainGameSceneDraw(){
	BackgroundGraphicDraw();
	DestroyEffectDraw();
	EnemyDraw();
	BulletDraw();
	PlayerDraw();
	WaveDraw();

	if (!feedoutEnd) {
	float cosValue = (float)std::abs(std::cos((count) * DX_PI / 180));
	int feed = (int)(255* cosValue);
		SetDrawBlendMode(DX_BLENDMODE_ALPHA,feed);
		DrawBox(0,0,SCREEN_WIDTH,SCREEN_HEIGHT,0x0,TRUE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND,0);
	}
}

void MainGameSceneDelete(){
	BackgroundGraphicDelete();
	PlayerDelete();
	EnemyDelete();
	BulletDelete();

	DestroyEffectDelete();
	WaveDelete();
}
