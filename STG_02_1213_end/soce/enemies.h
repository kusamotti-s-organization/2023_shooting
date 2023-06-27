#pragma once
#include"common.h"


void EnemiesInit()   ;
void EnemiesUpdate() ;
void EnemiesDraw()	 ;
void EnemiesDelete() ;
bool EnemiesCollisions(POS _pos,int _size,bool _playerflag=false);
//POS GetEnemiesPosition();
int GetEneDeadcount(int num=0);
int GetBossHp();