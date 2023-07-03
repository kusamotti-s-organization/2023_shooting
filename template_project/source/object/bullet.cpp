#include "bullet.h"

#include<DxLib.h>
#include"../common.h"
#include"enemy.h"
#include"graphic.h"

namespace {
	constexpr float BULLET_SPEED = 8.f;
	struct Bullet {
		Position m_position;
		float radius;
		bool isActive;
	};
	constexpr int MAX_BULLET_NUM = 300 + 1;
	Bullet bullets[MAX_BULLET_NUM];
	constexpr float BULLETS_RADIUS= 30.f;
}

void BulletInit(){
	for (int i = 0; i < MAX_BULLET_NUM; ++i) {
		bullets[i].m_position = Position{0,0};
		bullets[i].radius= BULLETS_RADIUS;
		bullets[i].isActive = false;
	}
}

void BulletUpdate(){

	//(仮)弾 移動
	for (int i = 0; i < MAX_BULLET_NUM; ++i) {
		Bullet bullet = bullets[i];
		if (!bullet.isActive)
			continue;

		bullets[i].m_position.y += -BULLET_SPEED;
	}

	//画面外の弾を消す
	for (int i = 0; i < MAX_BULLET_NUM; ++i) {
		Bullet bullet = bullets[i];
		if (!bullet.isActive)
			continue;
		if (bullet.m_position.y > 0)
			continue;

		bullets[i].isActive = false;
		bullets[i].m_position = Position{0,0};
	}

	//Enemyと当たったかどうか
	for (int i = 0; i < MAX_BULLET_NUM; ++i) {
		Bullet bullet = bullets[i];
		if (!bullet.isActive)
			continue;

		bool isCollision= EnemyToBulletCollision(bullet.m_position.x,bullet.m_position.y,bullet.radius/2);
		if (!isCollision)
			continue;
		bullets[i].isActive = false;
	}
}

void BulletDraw(){
	for (int i = 0; i < MAX_BULLET_NUM; ++i) {
		Bullet bullet = bullets[i];
		if (!bullet.isActive)
			continue;
	
		//DrawCircleAA(bullet.m_position.x,bullet.m_position.y, bullet.radius,22,0xff0fff);
		ArrowGraphicDrawUp(bullet.m_position.x, bullet.m_position.y, bullet.radius);
	}
}

void BulletDelete(){

}

void BulletCreate(float x, float y){
	for (int i = 0; i < MAX_BULLET_NUM; ++i) {
		Bullet bullet = bullets[i];
		if (bullet.isActive)
			continue;

		bullets[i].m_position = Position{x,y};
		bullets[i].isActive = true;
		break;
	}
}

