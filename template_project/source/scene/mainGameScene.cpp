#include"mainGameScene.h"

#include"../object/player.h"
#include"../object/enemy.h"
#include"../object/bullet.h"
#include"../object/backgroundGraphic.h"

namespace {

}

void MainGameSceneInit(){
	backgroundGraphicInit();
	EnemyInit();
	PlayerInit();
	BulletInit();
}

void MainGameSceneUpdate(){
	PlayerUpdate();
	BulletUpdate();
	EnemyUpdate();
	backgroundGraphicUpdate();
}

void MainGameSceneDraw(){
	backgroundGraphicDraw();
	PlayerDraw();
	EnemyDraw();
	BulletDraw();

}

void MainGameSceneDelete(){
	backgroundGraphicDelete();
	PlayerDelete();
	EnemyDelete();
	BulletDelete();

}
