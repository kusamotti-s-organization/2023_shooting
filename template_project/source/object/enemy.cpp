#include "enemy.h"

#include<DxLib.h>
#include<cassert>
#include"../main/config.h"
#include"../common.h"
#include"../sceneManager.h"
#include"graphic.h"
#include"destroyEffect.h"

//#define MAX_ENEMY_NUM (5 +1)

namespace {
	struct Enemy {
		Position m_position;
		Position m_moveVector;
		bool isActive;
		bool color;
	};
	constexpr int MAX_ENEMY_NUM = 400 +1;
	constexpr float ENMEY_INSTANCE_TIME = 0.2f;
	constexpr float ENEMY_RADIUS = 20.f;
	Enemy enemies[MAX_ENEMY_NUM];

	int frameCounter;
	int instanceCount;
	int instanceTime;
	int enemiesKillCount;
}


void EnemyInit(){
	for (int i = 0; i < MAX_ENEMY_NUM; ++i) {
		enemies[i].m_position = Position{0,0};
		enemies[i].m_moveVector= Position{0,0};
		enemies[i].isActive = false;
		enemies[i].color = false;
	}
	frameCounter = 0;
	instanceCount =0;
	instanceTime = GetRand((int)(60 * ENMEY_INSTANCE_TIME))+1;
	enemiesKillCount = 0;
}

void EnemyUpdate(){

	//ìGê∂ê¨èIóπ
	int instanceGoalNum = MAX_ENEMY_NUM - 1;
	if (instanceCount >= instanceGoalNum && enemiesKillCount >= instanceGoalNum) {
		//É{ÉXÇÃê∂ê¨
		//Åiè„Ç…Ç∑ÇÈëOÇÃâºÅjÇ∆ÇËÇ†Ç¶Ç∏ÉVÅ[ÉìÇêÿÇËë÷Ç¶ÇÈ
		ChangeScene(Scene::title);
	}

	////ìGÇÃê∂ê¨
	//{
	//	//float x= 100.f + GetRand(SCREEN_WIDTH - 100);
	//	//EnemyCreate(x,0,0,1,GetRand(1));
	//	EnemyMovePattarn(EnemyMovePatternState::left);
	//}

	//ìGÇÃê∂ê¨
	//if (enemiesKillCount <= instanceGoalNum)
	//if (frameCounter% instanceTime == 0) {
	//	bool instanceSuccess = false;
	//	for (int i = 0; i < MAX_ENEMY_NUM; ++i) {
	//		Enemy enemy = enemies[i];
	//		if (enemy.isActive)
	//			continue;
	//
	//		enemies[i].m_position.x= 100.f+GetRand(SCREEN_WIDTH-100);
	//		enemies[i].m_position.y=0;
	//		enemies[i].m_moveVector = Position{0,1};
	//		enemies[i].isActive = true;
	//		instanceSuccess = true;
	//		break;
	//	}
	//
	//	if(instanceSuccess)
	//		++instanceCount;
	//
	//	instanceTime = GetRand((int)(60 * ENMEY_INSTANCE_TIME))+1;
	//}

	//ìGà⁄ìÆ
	for (int i = 0; i < MAX_ENEMY_NUM; ++i) {
		Enemy enemy = enemies[i];
		if ( !enemy.isActive)
			continue;
		enemies[i].m_position.x += enemies[i].m_moveVector.x;
		enemies[i].m_position.y += enemies[i].m_moveVector.y;
	}

	//ìGÇ™å©Ç¶Ç»Ç≠Ç»Ç¡ÇΩÇÁ
	for (int i = 0; i < MAX_ENEMY_NUM; ++i) {
		Enemy enemy = enemies[i];
		
		if ( !enemy.isActive)
			continue;

		bool top	= enemy.m_position.y >= 0-ENEMY_RADIUS;
		bool bottom	= enemy.m_position.y <= SCREEN_HEIGHT+ ENEMY_RADIUS;

		bool left  = enemy.m_position.x <= SCREEN_WIDTH+ ENEMY_RADIUS;
		bool right = enemy.m_position.x >= 0- ENEMY_RADIUS;
		if (left&&right && top&&bottom)
			continue;

		enemies[i].isActive = false;
	}

	++frameCounter;
}

void EnemyDraw(){
	for (int i = 0; i < MAX_ENEMY_NUM; ++i) {
		Enemy enemy = enemies[i];
		
		if (!enemy.isActive)
			continue;
		if(enemy.color)
			TargetGraphicDrawColor(enemy.m_position.x, enemy.m_position.y, ENEMY_RADIUS);
		else
			TargetGraphicDrawMono(enemy.m_position.x, enemy.m_position.y, ENEMY_RADIUS);

	//	DrawCircleAA(enemy.m_position.x,enemy.m_position.y,5.f,22,0xffff0f);
	}

}

void EnemyDelete(){

}

bool EnemyToBulletCollision(float a_x, float a_y, float a_radius){
	Circle bullet = { Position{a_x,a_y},a_radius };
	bool anser = false;

	for (int i = 0; i < MAX_ENEMY_NUM; ++i) {
		Enemy enemy = enemies[i];
		if (!enemy.isActive)
			continue;

		Circle enemyCiecle = { enemy.m_position,5 };
		anser = CircleCollision(bullet, enemyCiecle);

		if ( !anser)
			continue;
		
		enemies[i].isActive = false;
		++enemiesKillCount;
		EffectOn(enemy.m_position.x,enemy.m_position.y,20);
		
		break;
	}

	return anser;
}

void EnemyCreate(float x, float y, float mx, float my,bool color){
	int instanceGoalNum = MAX_ENEMY_NUM - 1;
	//ìGÇÃê∂ê¨
	if (frameCounter % instanceTime == 0) {
		bool instanceSuccess = false;
		for (int i = 0; i < MAX_ENEMY_NUM; ++i) {
			Enemy enemy = enemies[i];
			if (enemy.isActive)
				continue;

			enemies[i].m_position = Position{x,y};
			enemies[i].m_moveVector = Position{ mx,my};
			enemies[i].isActive = true;
			enemies[i].color = color;
			instanceSuccess = true;
			break;
		}

		if (instanceSuccess)
			++instanceCount;

		instanceTime = GetRand((int)(60 * ENMEY_INSTANCE_TIME)) + 1;
	}
}
void EnemyCreate(Position pos,Position vec ,bool color) {
	EnemyCreate(pos.x,pos.y,vec.x,vec.y,color);
}

int GetKillNum(){
	return enemiesKillCount;
}

int GetInstanceNum(){
	return instanceCount;
}

void ResetInstanceNum(){
	instanceCount = 0;
}

int GetActiveEnemy(){
	int count = 0;
	for (int i = 0; i < MAX_ENEMY_NUM; ++i) {
		if (!enemies[i].isActive)
			continue;

		++count;
	}
	return count;
}

void EnemyMovePattarn(EnemyMovePatternState pattarn) {
	Position pos = {0,0};
	Position move = {0,0};
	bool col = false;

	switch (pattarn){
	case left:
		pos.x = -ENEMY_RADIUS;
		pos.y = ENEMY_RADIUS + GetRand(SCREEN_HEIGHT - (int)ENEMY_RADIUS);
		move = {1,0};
		col = false;

		break;
	case right:
		pos.x = SCREEN_WIDTH +ENEMY_RADIUS;
		pos.y = ENEMY_RADIUS + GetRand(SCREEN_HEIGHT - (int)ENEMY_RADIUS);
		move = {-1,0};
		col = true;

		break;
	case top:
		pos.x = 100.f + GetRand(SCREEN_WIDTH - 100);
		pos.y = -ENEMY_RADIUS;
		move = {0,1};
		col = GetRand(1);
		break;
	default:
		assert(false);
		break;
	}


	EnemyCreate(pos, move, col);
}

void EnemiesAllActive(bool _active) {
	for (int i = 0; i < MAX_ENEMY_NUM; ++i) {
		enemies[i].m_position = {};
		enemies[i].isActive = _active;
	}

}