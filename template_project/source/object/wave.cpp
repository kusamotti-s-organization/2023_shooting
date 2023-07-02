#include "wave.h"

#include<DxLib.h>
#include<string>
#include<cassert>
#include<cmath>
#include"../main/config.h"
#include"enemy.h"

namespace {
	constexpr int ENEMY_INSTANCE_NUM=300;
	enum State{
		start=0
		,wave1_mob
		,wave2_mob
		,wave3_mobAll
		,wave4_boss
		,max
	};
	State state;
	State stateNext;
	std::string dispStr = "Wave ";
	int fontHandle;
	int cosCount;
	bool standing;
}

void WaveInit(){
	state = State::start;
	stateNext = State::start;
	fontHandle = LoadFontDataToHandle("data/font/‚È‚Â‚ß‚à‚¶.dft");
	assert(fontHandle>0);
	cosCount = 0;
	standing = true;
}
void WaveUpdate(){
	if (standing) {
		++cosCount;

		if (cosCount > 90) {
			standing = false;
			int stateNum = (int)(state)+1;
			stateNext = (State)(stateNum);
			cosCount = 0;
			ResetInstanceNum();
		}

	}


	int instanceCount = GetInstanceNum();
	bool instance = instanceCount < ENEMY_INSTANCE_NUM;

	if (state != stateNext) {
		state = stateNext;
	}
	if (instance) {
		switch (state) {
		case start:
			break;
		case wave1_mob:
			EnemyMovePattarn(EnemyMovePatternState::right);
			break;
		case wave2_mob:
			EnemyMovePattarn(EnemyMovePatternState::left);
			break;
		case wave3_mobAll:
			EnemyMovePattarn(EnemyMovePatternState::top);
			break;
		case wave4_boss:
			//boss
			break;
		case max:

			break;
		default:
			assert(false);
			break;
		}
	}

#ifdef _DEBUG
	if (CheckHitKey(KEY_INPUT_SPACE) && CheckHitKey(KEY_INPUT_LSHIFT))
		standing = true;
#endif

	if (!standing && !instance) {
		standing = GetActiveEnemy() <= 0;
	}
}

void WaveDraw(){
	if (!standing) {
		return;
	}

	float cosValue = (float)std::abs(std::cos((cosCount)*DX_PI / 180));
	int feed = (int)(255 * cosValue);
	//SetDrawBlendMode(DX_BLENDMODE_ALPHA, feed);


	std::string disp = dispStr + std::to_string((int)(state) + 1);
	int widNum = GetDrawFormatStringWidthToHandle(fontHandle,disp.c_str());
	int heiNum = GetFontSizeToHandle(fontHandle);
	
	int y = SCREEN_HEIGHT / 2;
	int fontsize = heiNum;
	SetDrawBlendMode(DX_BLENDMODE_ALPHA,(int)(255/3 *cosValue));
	DrawBoxAA(0,y-fontsize*2.f,SCREEN_WIDTH,y+fontsize*1.5f,0x0,TRUE);

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, feed);
	DrawFormatStringToHandle(SCREEN_WIDTH/2 -widNum/2,SCREEN_HEIGHT/2 -heiNum,0xffffff,fontHandle,disp.c_str());

	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

void WaveDelete(){
	if(fontHandle>0)
		DeleteFontToHandle(fontHandle);
	fontHandle = -1;
}