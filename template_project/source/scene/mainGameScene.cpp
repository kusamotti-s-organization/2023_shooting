#include"mainGameScene.h"

#include"../object/player.h"
#include"../object/enemy.h"
#include"../object/bullet.h"

namespace {

}

void MainGameSceneInit(){
	EnemyInit();
	PlayerInit();
	BulletInit();
}

void MainGameSceneUpdate(){
	PlayerUpdate();
	BulletUpdate();
	EnemyUpdate();
}

void MainGameSceneDraw(){
	PlayerDraw();
	EnemyDraw();
	BulletDraw();

}

void MainGameSceneDelete(){
	PlayerDelete();
	EnemyDelete();
	BulletDelete();

}
