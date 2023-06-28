#include "enemies.h"
#include <DxLib.h>
#include <assert.h>
#include "common.h"
#include "config.h"

namespace {
	struct ENEMY {
		bool active;
		POSITION pos;
		int animCounter;
		int deadCounter;
	};
	static const int ENEMY_NUM = 20;
	ENEMY enemies[ENEMY_NUM];
	int spawnCounter = 60;
	int hImage = -1;
};

void EnemiesInit()
{
	hImage = LoadGraph("data\\texture\\mob.png");
	assert(hImage>0);

	for (int i=0; i<ENEMY_NUM; i++)
		enemies[i].active = false;
	spawnCounter = 60;
}

void EnemiesUpdate()
{
	// “G‚ð¶¬‚·‚é
	if (--spawnCounter<=0) {
		for (int i = 0; i < ENEMY_NUM; i++) {
			if (!enemies[i].active) {
				enemies[i].pos.x = SCREEN_WIDTH;
				enemies[i].pos.y = GetRand(SCREEN_HEIGHT-64);
				enemies[i].active = true;
				enemies[i].animCounter = 0;
				enemies[i].deadCounter = 0;
				break;
			}
		}
		spawnCounter = 30;
	}

	// “G‚ðs“®‚·‚é
	for (int i = 0; i < ENEMY_NUM; i++) {
		if (!enemies[i].active)
			continue;
		if (enemies[i].deadCounter==0) { // ¶‚«‚Ä‚¢‚é
			enemies[i].pos.x -= 2.0;
			if (enemies[i].pos.x < -64.0)
				enemies[i].active = false;
			enemies[i].animCounter++;
		} else { // Ž€‚ñ‚Å‚¢‚é
			if (++enemies[i].deadCounter>60)
				enemies[i].active = false;
		}
	}
}

void EnemiesDraw()
{
	for (int i = 0; i < ENEMY_NUM; i++) {
		if (enemies[i].active) {
			int pat = (enemies[i].animCounter/8)%4;
			if (enemies[i].deadCounter>0)
				pat = 4;
			DrawRectGraph((int)enemies[i].pos.x, (int)enemies[i].pos.y,
				0, pat*64, 64, 64, hImage, TRUE);
		}
	}
}

void EnemiesRelease()
{
	if (hImage>0) {
		DeleteGraph(hImage);
		hImage = -1;
	}
}

bool EnemyCollideStone(CIRCLE stone)
{
	for (int i = 0; i < ENEMY_NUM; i++) {
		if (enemies[i].active && enemies[i].deadCounter == 0) {
			CIRCLE my;
			my.x = (int)enemies[i].pos.x+32;
			my.y = (int)enemies[i].pos.y+32;
			my.r = 20;
			if (CircleCollision(my, stone)) {
				enemies[i].deadCounter=1;
				return true;
			}
		}
	}
	return false;
}
