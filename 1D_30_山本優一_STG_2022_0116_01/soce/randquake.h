#pragma once
#include<DxLib.h>
void RandQuakeInit()		 ;
void RandQuakeUpdate()	 ;
void RandQuakeDraw()		 ;
void RandQuakeDelete()	 ;
void RandQuakeSwitch(bool _active = true);
bool RandQuakeGetActive();
VECTOR RandQuakeMove();