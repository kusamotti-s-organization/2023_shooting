#include "resultScene.h"

#include<DxLib.h>
#include<string>
#include<cmath>
#include<cassert>
#include"../main/config.h"
#include"../sceneManager.h"
#include"../object/backgroundGraphic.h"

namespace {
	std::string dispStr = "ゲームクリア";//描画文字
	int fontHandle;//フォントハンドル
	int cosCount;//cos用カウンタ
	int blackCount;//フェード用のカウンタ
	bool keystop;//前回のキー入力の記録
	bool feedout;//フェードしているか
}

void ResultSceneInit(){
	//メモリに読み込み
	fontHandle = LoadFontDataToHandle("data/font/なつめもじ.dft");
	//-1でエラーならお知らせ
	assert(fontHandle > 0);
	cosCount = 0;
	blackCount = 0;
	keystop = true;
	feedout = false;
	//背景画像も読み込み
	BackgroundGraphicInit();
}

void ResultSceneUpdate(){
	//現在のキー入力
	bool key = CheckHitKeyAll();
	//キー入力が現在が押していて前回が押していない
	if (key && !keystop) 
	{
		//フェード開始
		feedout = true;
	}
	//前回のキー入力の記録を代入
	keystop = key;

	//背景の動きも処理
	BackgroundGraphicUpdate();

	//フェードが開始していなかったら
	if (!feedout)
	{
		//早期リターン
		return;
	}
	//カウンタ cos用
	++cosCount;

	//カウンタ 90以下なら
	if (cosCount <= 90)
	{
		//早期リターン
		return;
	}

	//オーバーフローしないように固定
	cosCount = 90;

	//カウンタ 黒画面用
	++blackCount;

	//カウンタ255以下なら
	if (blackCount <= 255)
	{
		//早期リターン
		return;
	}
	//シーン切替
	ChangeScene(Scene::title);
}

void ResultSceneDraw(){
	//背景を描画
	BackgroundGraphicDraw();
	
	//cosの値
	float cosValue = (float)std::abs(std::cos((cosCount)*DX_PI / 180));
	//フェード用の値
	int feed = (int)(255 * cosValue);
	//SetDrawBlendMode(DX_BLENDMODE_ALPHA, feed);

	//描画用文字
	std::string disp = dispStr ;
	//文字の横幅
	int widNum = GetDrawFormatStringWidthToHandle(fontHandle, disp.c_str());
	//文字の縦幅
	int heiNum = GetFontSizeToHandle(fontHandle);
	//ｙ座標
	int y = SCREEN_HEIGHT / 2;
	//フォントの縦幅
	int fontsize = heiNum;
	//半透明を設定
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, (int)(255 / 3 * cosValue));
	//黒帯 黒 0x0
	DrawBoxAA(0, y - fontsize * 2.f, SCREEN_WIDTH, y + fontsize * 1.5f, 0x0, TRUE);

	//半透明を設定
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, feed);
	//クリア文字 白0xffffff
	DrawFormatStringToHandle(SCREEN_WIDTH / 2 - widNum / 2, SCREEN_HEIGHT / 2 - heiNum, 0xffffff, fontHandle, disp.c_str());

	//半透明を設定
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	//半透明を設定
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, blackCount);
	//黒フェード用 黒 0x0
	DrawBox(0,0,SCREEN_WIDTH,SCREEN_HEIGHT,0x0,TRUE);
	//半透明を解除
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

void ResultSceneDelete(){
	//メモリから解放
	BackgroundGraphicDelete();
}
