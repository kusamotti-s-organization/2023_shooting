#pragma once
#include "common.h"

void EnemiesInit();
void EnemiesUpdate();
void EnemiesDraw();
void EnemiesRelease();

// �G�Ɛ΂̓����蔻�������
// �G�̉~���󂯎��A�������Ă���ΓG�����S������
// �������Ă����true��Ԃ�
bool EnemyCollideStone(CIRCLE stone);