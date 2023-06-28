#pragma once
#include"common.h"
void ItemInit()	 ;
void ItemUpdate();
void ItemDraw()	 ;
void ItemDelete();
void ItemCreate(POS ,int _type=-1);
bool ItemCollision(POS _pos, double _size);
int ItemGetR();
int ItemGetG();
int ItemGetB();