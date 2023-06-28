#pragma once
#include"common.h"


void BossEnemyInit()   ;
void BossEnemyUpdate() ;
void BossEnemyDraw()	 ;
void BossEnemyDelete() ;
bool BossEnemyCollisions(POS _pos,int _size,bool _playerflag=false);
void BossEnemyCreate(POS _pos, POS _vec);