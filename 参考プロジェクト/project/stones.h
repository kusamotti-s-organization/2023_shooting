#pragma once
#include "common.h"

void StonesInit();
void StonesUpdate();
void StonesDraw();
void StonesRelease();

// �΂𐶐����܂��B
// _pos�̈ʒu�Ɉʒu�𐶐����āA�E�ɔ��ł����܂�
// �z�񂪂����ς��Ȃ�A��������܂���
void CreateStone(POSITION _pos);