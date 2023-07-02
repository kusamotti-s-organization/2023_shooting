#pragma once

void EnemyInit();
void EnemyUpdate();
void EnemyDraw();
void EnemyDelete();

bool EnemyToBulletCollision(float x,float y,float radius);
void EnemyCreate(float x,float y,float mx,float my,bool color = true);
int GetKillNum();
int GetInstanceNum();
void ResetInstanceNum();
int GetActiveEnemy();
enum EnemyMovePatternState {
	left=0//������E��
	,right//�E���獶��
	,top
};
void EnemyMovePattarn(EnemyMovePatternState pattarn);

