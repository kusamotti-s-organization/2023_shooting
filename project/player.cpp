#include "player.h"
#include <DxLib.h>
#include <assert.h>
#include "common.h"
#include "stones.h"
#include "config.h"

namespace {
	int hImage = -1;
	int hSound = -1;
	POSITION pos;
	bool spacePushed = true;
	int throwCounter = 0;
};

void PlayerInit()
{
	hImage = LoadGraph("data\\texture\\aoi.png");
	assert(hImage>0);
	hSound = LoadSoundMem("data\\sound\\throw.wav");
	assert(hSound > 0);
	pos.x = 0.0;
	pos.y = 400.0;
	spacePushed = true;
	throwCounter = 0;
}

void PlayerRelease()
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

void PlayerUpdate()
{
	if (CheckHitKey(KEY_INPUT_W)) {
		pos.y -= 3.0;
		if (pos.y<0)
			pos.y = 0;
	}
	if (CheckHitKey(KEY_INPUT_S)) {
		pos.y += 3.0;
		if (pos.y > SCREEN_HEIGHT-64)
			pos.y = SCREEN_HEIGHT-64;
	}
	if (CheckHitKey(KEY_INPUT_A)) {
		pos.x -= 3.0;
		if (pos.x<0)
			pos.x = 0;
	}
	if (CheckHitKey(KEY_INPUT_D)) {
		pos.x += 3.0;
		if (pos.x > SCREEN_WIDTH-64)
			pos.x = SCREEN_WIDTH-64;
	}

	bool push = CheckHitKey(KEY_INPUT_SPACE);
	if (push && !spacePushed) {
		if (throwCounter==0) {
			POSITION p;
			p.x = pos.x + 28;
			p.y = pos.y + 12;
			CreateStone(p);
			PlaySoundMem(hSound, DX_PLAYTYPE_BACK);
			throwCounter = 10;
		}
	}
	if (throwCounter>0)
		throwCounter--;
	spacePushed = push;
}

void PlayerDraw()
{
	int cellX = 0;
	int cellY = 0;
	if (throwCounter>0) {
		cellY = 1*64;
		cellX = 2*64;
	}
	DrawRectGraph((int)pos.x, (int)pos.y,
			cellX, cellY, 64, 64, hImage, TRUE);
}
