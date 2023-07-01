#include "enemy.h"

#include<DxLib.h>
#include"../main/config.h"
#include"../common.h"
#include"../sceneManager.h"

//#define MAX_ENEMY_NUM (5 +1)

namespace {
	struct Enemy {
		Position m_position;
		bool isActive;
	};
	constexpr int MAX_ENEMY_NUM = 100 +1;
	constexpr float ENMEY_INSTANCE_TIME = 0.2f;
	Enemy enemies[MAX_ENEMY_NUM];

	int frameCounter;
	int instanceCount;
	int insranceTime;
	int enemiesKillCount;
}


void EnemyInit(){
	for (int i = 0; i < MAX_ENEMY_NUM; ++i) {
		enemies[i].m_position = Position{0,0};
		enemies[i].isActive = false;
	}
	frameCounter = 0;
	instanceCount =0;
	insranceTime = GetRand((int)(60 * ENMEY_INSTANCE_TIME))+1;
	enemiesKillCount = 0;
}

void EnemyUpdate(){

	//�G�����I��
	int instanceGoalNum = MAX_ENEMY_NUM - 1;
	if (instanceCount >= instanceGoalNum && enemiesKillCount >= instanceGoalNum) {
		//�{�X�̐���
		//�i��ɂ���O�̉��j�Ƃ肠�����V�[����؂�ւ���
		ChangeScene(Scene::title);
	}

	//�G�̐���
	if (enemiesKillCount <= instanceGoalNum)
	if (frameCounter% insranceTime == 0) {
		bool instanceSuccess = false;
		for (int i = 0; i < MAX_ENEMY_NUM; ++i) {
			Enemy enemy = enemies[i];
			if (enemy.isActive)
				continue;

			enemies[i].m_position.x= 100.f+GetRand(SCREEN_WIDTH-100);
			enemies[i].m_position.y=0;
			enemies[i].isActive = true;
			instanceSuccess = true;
			break;
		}

		if(instanceSuccess)
			++instanceCount;

		insranceTime = GetRand((int)(60 * ENMEY_INSTANCE_TIME))+1;
	}

	//�G�ړ�
	for (int i = 0; i < MAX_ENEMY_NUM; ++i) {
		Enemy enemy = enemies[i];
		if ( !enemy.isActive)
			continue;
		enemies[i].m_position.y += 1.f;
	}

	//(��)�G�������Ȃ��Ȃ�����
	for (int i = 0; i < MAX_ENEMY_NUM; ++i) {
		Enemy enemy = enemies[i];
		
		if ( !enemy.isActive)
			continue;

		if (enemy.m_position.y <= SCREEN_HEIGHT)
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
		
		DrawCircleAA(enemy.m_position.x,enemy.m_position.y,5.f,22,0xffff0f);
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
		
		break;
	}

	return anser;
}

void EnemiesAllActive() {
	for (int i = 0; i < MAX_ENEMY_NUM; ++i) {
		enemies[i].m_position = {};
		enemies[i].isActive = false;
	}

}