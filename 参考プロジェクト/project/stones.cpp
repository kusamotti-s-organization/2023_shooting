#include "stones.h"
#include <DxLib.h>
#include <assert.h>
#include "common.h"
#include "config.h"
#include "enemies.h"
#include "score.h"

namespace {
	struct STONE {
		bool active;
		POSITION pos;
	};
	static const int STONE_NUM = 20;
	STONE stones[STONE_NUM];
	int hImage = -1;
	int hSound = -1;
};

void StonesInit()
{
	hImage = LoadGraph("data\\texture\\stone.png");
	assert(hImage>0);
	hSound = LoadSoundMem("data\\sound\\hit.wav");
	assert(hSound>0);
	for (int i=0; i<STONE_NUM; i++) {
		stones[i].active = false;
	}
}

void StonesRelease()
{
	if (hImage > 0) {
		DeleteGraph(hImage);
		hImage = -1;
	}
	if (hSound > 0) {
		DeleteSoundMem(hSound);
		hSound = -1;
	}
}

void StonesUpdate()
{
	for (int i = 0; i < STONE_NUM; i++) {
		if (stones[i].active) {
			stones[i].pos.x += 5.0;
			if (stones[i].pos.x > SCREEN_WIDTH) {
				stones[i].active = false;
			}
			CIRCLE c;
			c.x = (int)stones[i].pos.x+10;
			c.y = (int)stones[i].pos.y+10;
			c.r = 10;
			if (EnemyCollideStone(c)) {
				stones[i].active = false;
				PlaySoundMem(hSound, DX_PLAYTYPE_BACK);
				ScoreAdd(10);
			}
		}
	}
}

void StonesDraw()
{
	for (int i = 0; i < STONE_NUM; i++) {
		if (stones[i].active) {
			DrawGraph((int)stones[i].pos.x, (int)stones[i].pos.y,
				hImage, TRUE);
		}
	}
}

void CreateStone(POSITION _pos)
{
	for (int i=0; i<STONE_NUM; i++) {
		if (stones[i].active)
			continue;
		stones[i].pos = _pos;
		stones[i].active = true;
		return;
	}
}
