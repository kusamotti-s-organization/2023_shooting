#include "resultScene.h"

#include<DxLib.h>
#include<string>
#include<cmath>
#include<cassert>
#include"../main/config.h"
#include"../sceneManager.h"
#include"../object/backgroundGraphic.h"

namespace {
	std::string dispStr = "ゲームクリア";
	int fontHandle;
	int cosCount;
	int blackCount;
	bool keystop;
	bool feedout;
}

void ResultSceneInit(){
	fontHandle = LoadFontDataToHandle("data/font/なつめもじ.dft");
	assert(fontHandle > 0);
	cosCount = 0;
	blackCount = 0;
	keystop = true;
	feedout = false;
	BackgroundGraphicInit();
}

void ResultSceneUpdate(){
	bool key = CheckHitKeyAll();

	if (key && !keystop) {
		feedout = true;
	}
	keystop = key;

	BackgroundGraphicUpdate();

	if (!feedout)
		return;
	++cosCount;
	if (cosCount <= 90)
		return;
	cosCount = 90;
	++blackCount;
	if (blackCount <= 255)
		return;
	ChangeScene(Scene::title);
}

void ResultSceneDraw(){
	BackgroundGraphicDraw();
	

	float cosValue = (float)std::abs(std::cos((cosCount)*DX_PI / 180));
	int feed = (int)(255 * cosValue);
	//SetDrawBlendMode(DX_BLENDMODE_ALPHA, feed);

	std::string disp = dispStr ;
	int widNum = GetDrawFormatStringWidthToHandle(fontHandle, disp.c_str());
	int heiNum = GetFontSizeToHandle(fontHandle);

	int y = SCREEN_HEIGHT / 2;
	int fontsize = heiNum;
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, (int)(255 / 3 * cosValue));
	DrawBoxAA(0, y - fontsize * 2.f, SCREEN_WIDTH, y + fontsize * 1.5f, 0x0, TRUE);

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, feed);
	DrawFormatStringToHandle(SCREEN_WIDTH / 2 - widNum / 2, SCREEN_HEIGHT / 2 - heiNum, 0xffffff, fontHandle, disp.c_str());

	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, blackCount);
	DrawBox(0,0,SCREEN_WIDTH,SCREEN_HEIGHT,0x0,TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

void ResultSceneDelete(){
	BackgroundGraphicDelete();
}
