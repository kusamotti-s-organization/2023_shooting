#pragma once
#include"common.h"


void BossInit()   ;
void BossUpdate() ;
void BossDraw()	 ;
void BossDelete() ;
bool BossCollisions(POS _pos,int _size, bool _playerflag=false);
void BossCreate();
//POS GetEnemiesPosition();
int GetBossHp();
POS GetBossPos();
