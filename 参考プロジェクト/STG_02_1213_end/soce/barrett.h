#pragma once
#include"common.h"
void BarrettInit()	;
void BarrettUpdate();
void BarrettDraw()	;
void BarrettDelete();
void CreatBarrett(POS _pos, VEC _vec, double _speed, COLOR _color={-1,-1,-1});
POS GetBarrettPosition(int i=0);

int GetMaxBarrettNums();