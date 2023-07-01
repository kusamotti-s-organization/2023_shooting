#include "player.h"

#include<DxLib.h>
#include"../main/config.h"
#include"../common.h"
#include"bullet.h"

namespace {
	constexpr float PLAYER_SPEED = 2.f;
	constexpr float SHOT_COOL_TIME = 0.12f;
	Position position;
	float shotCoolTime;
	bool keystop;
	bool onKey;
}

void PlayerInit() {
	position.x = SCREEN_WIDTH / 2;
	position.y = SCREEN_HEIGHT / 2;
	shotCoolTime = SHOT_COOL_TIME * 60.f;
	keystop = true;
	onKey = false;
}

void PlayerUpdate() {
	bool upKey = CheckHitKey(KEY_INPUT_W);
	bool downKey = CheckHitKey(KEY_INPUT_S);
	bool leftKey = CheckHitKey(KEY_INPUT_A);
	bool rightKey = CheckHitKey(KEY_INPUT_D);

	position.x += (int)leftKey * PLAYER_SPEED * -1;
	position.x += (int)rightKey * PLAYER_SPEED * 1;
	position.y += (int)upKey * PLAYER_SPEED * -1;
	position.y += (int)downKey * PLAYER_SPEED * 1;

	keystop = onKey;
	onKey = GetMouseInput() & MOUSE_INPUT_LEFT;
	if (onKey && !keystop) {
		BulletCreate(position.x, position.y);
	}
	
	shotCoolTime += -1.f;
	if (shotCoolTime <= 0)
		shotCoolTime = 0;

	if ((GetMouseInput() & MOUSE_INPUT_RIGHT)&&shotCoolTime <= SHOT_COOL_TIME) {
		shotCoolTime = SHOT_COOL_TIME * 60.f;

		BulletCreate(position.x,position.y);
	}

}

void PlayerDraw(){
	DrawCircleAA(position.x,position.y,7.f,22,0x0fffff);
}

void PlayerDelete(){

}
