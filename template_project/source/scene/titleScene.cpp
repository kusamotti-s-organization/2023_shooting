#include "titleScene.h"

#include<DxLib.h>
#include<string>
#include<cmath>
#include<cassert>
#include"../main/config.h"
#include"../sceneManager.h"


namespace {
	std::string dispStr = "的あてシューティング";
	int feedCounter;
	int titleFont;
	int titleFontSize;
	bool feedOn;
	bool keystop;
	bool onKey;
}

void TitleSceneInit(){
	feedCounter = 0;
	titleFont = LoadFontDataToHandle("data/font/なつめもじ.dft");
	assert(titleFont>0);
	titleFontSize = GetFontSizeToHandle(titleFont);
	feedOn = false;
	keystop = true;
	onKey = false;
}

void TitleSceneUpdate(){
	
	keystop = onKey;
	onKey = CheckHitKey(KEY_INPUT_RETURN) ||(GetMouseInput()&MOUSE_INPUT_LEFT);
	onKey = onKey || CheckHitKeyAll();

	if (onKey && !keystop) {
		feedOn = true;
	}

	if (feedOn) {
		feedCounter+= 3;
	}
	if (feedCounter > 180) {

		ChangeScene(Scene::mainGame);
	}
}

void TitleSceneDraw(){
	if (feedOn) {
		float feed = (cos((feedCounter)*DX_PI_F / 180) + 1) / 2;
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255 * feed);
		DrawBox(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, 0x0, TRUE);
	}

	int widNum = GetDrawFormatStringWidthToHandle(titleFont, dispStr.c_str());

	int x = SCREEN_WIDTH  / 2 - widNum/2;
	int y = SCREEN_HEIGHT / 2 - titleFontSize;

	DrawFormatStringToHandle(x,y,0xffffff,titleFont,dispStr.c_str());

	DrawFormatString(SCREEN_WIDTH/2,SCREEN_HEIGHT/2,0x0fffff,"Title");

	SetDrawBlendMode(DX_BLENDMODE_NOBLEND,0);
}

void TitleSceneDelete(){

}
