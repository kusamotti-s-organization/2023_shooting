#include "bullet.h"

#include<DxLib.h>
#include"../common.h"
#include"enemy.h"
#include"graphic.h"

namespace {
	constexpr float BULLET_SPEED = 3.f;
	struct Bullet {
		Position m_position;
		float radius;
		bool isActive;
	};
	constexpr int MAX_BULLET_NUM = 50 + 1;
	Bullet bullets[MAX_BULLET_NUM];
}

void BulletInit(){
	for (int i = 0; i < MAX_BULLET_NUM; ++i) {
		bullets[i].m_position = Position{0,0};
		bullets[i].radius=3.f;
		bullets[i].isActive = false;
	}
}

void BulletUpdate(){

	//(‰¼)’e ˆÚ“®
	for (int i = 0; i < MAX_BULLET_NUM; ++i) {
		Bullet bullet = bullets[i];
		if (!bullet.isActive)
			continue;

		bullets[i].m_position.y += -BULLET_SPEED;
	}

	//‰æ–ÊŠO‚Ì’e‚ðÁ‚·
	for (int i = 0; i < MAX_BULLET_NUM; ++i) {
		Bullet bullet = bullets[i];
		if (!bullet.isActive)
			continue;
		if (bullet.m_position.y > 0)
			continue;

		bullets[i].isActive = false;
		bullets[i].m_position = Position{0,0};
	}

	//Enemy‚Æ“–‚½‚Á‚½‚©‚Ç‚¤‚©
	for (int i = 0; i < MAX_BULLET_NUM; ++i) {
		Bullet bullet = bullets[i];
		if (!bullet.isActive)
			continue;

		bool isCollision= EnemyToBulletCollision(bullet.m_position.x,bullet.m_position.y,bullet.radius);
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
	
		DrawCircleAA(bullet.m_position.x,bullet.m_position.y, bullet.radius,22,0xff0fff);
		ArrowGraphicDrawUp(bullet.m_position.x, bullet.m_position.y, bullet.radius*10);
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

