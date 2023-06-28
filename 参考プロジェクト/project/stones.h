#pragma once
#include "common.h"

void StonesInit();
void StonesUpdate();
void StonesDraw();
void StonesRelease();

// 石を生成します。
// _posの位置に位置を生成して、右に飛んでいきます
// 配列がいっぱいなら、生成されません
void CreateStone(POSITION _pos);