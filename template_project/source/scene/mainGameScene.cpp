#include"mainGameScene.h"

#include"../object/player.h"
#include"../object/enemy.h"
#include"../object/bullet.h"
#include"../object/backgroundGraphic.h"
#include"../object/destroyEffect.h"

namespace {

}

void MainGameSceneInit(){
	backgroundGraphicInit();
	EnemyInit();
	PlayerInit();
	BulletInit();

	destroyEffectInit();
}

void MainGameSceneUpdate(){
	PlayerUpdate();
	BulletUpdate();
	EnemyUpdate();
	backgroundGraphicUpdate();

	destroyEffectUpdate();
}

void MainGameSceneDraw(){
	backgroundGraphicDraw();
	destroyEffectDraw();
	EnemyDraw();
	BulletDraw();
	PlayerDraw();

}

void MainGameSceneDelete(){
	backgroundGraphicDelete();
	PlayerDelete();
	EnemyDelete();
	BulletDelete();

	destroyEffectDelete();
}
