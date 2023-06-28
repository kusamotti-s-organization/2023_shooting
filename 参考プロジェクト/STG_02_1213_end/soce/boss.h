#pragma once
#include"common.h"


void BossInit()   ;
void BossUpdate() ;
void BossDraw()	 ;
void BossDelete() ;
bool BossCollisions(POS _pos,int _size);
void BossCreate();
//POS GetEnemiesPosition();
