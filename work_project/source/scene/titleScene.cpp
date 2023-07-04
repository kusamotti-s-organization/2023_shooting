#include "titleScene.h"

#include<DxLib.h>
#include<string>
#include<cmath>
#include<cassert>
#include"../main/config.h"
#include"../sceneManager.h"


namespace {
	std::string dispStr = "的あてシューティング";//描画文字
	int feedCounter;//カウンタ フェード
	int titleFont;//文字ハンドル
	int titleFontSize;//文字フォントサイズ
	bool feedOn;//フェードしているかどうか
	bool keystop;//前回のキー入力の記録
	bool onKey;//現在のキー入力
}

void TitleSceneInit(){
	feedCounter = 0;
	//メモリに読み込み
	titleFont = LoadFontDataToHandle("data/font/なつめもじ.dft");
	//結果が-1で 失敗したら お知らせ
	assert(titleFont>0);
	titleFontSize = GetFontSizeToHandle(titleFont);
	feedOn = false;
	keystop = true;
	onKey = false;
}

void TitleSceneUpdate(){
	//前回のキー入力の記録を代入
	keystop = onKey;
	//現在のキー入力を代入
	onKey = CheckHitKey(KEY_INPUT_RETURN) ||(GetMouseInput()&MOUSE_INPUT_LEFT);
	//現在のキー入力を代入
	onKey = onKey || CheckHitKeyAll();

	//現在押していて前回押してないなら
	if (onKey && !keystop) 
	{
		//フェード開始
		feedOn = true;
	}

	//フェードしているなら
	if (feedOn) 
	{
		//カウンタ
		feedCounter+= 3;
	}
	//カウンタ 180を超えたら
	if (feedCounter > 180) 
	{
		//シーンを切替
		ChangeScene(Scene::mainGame);
	}
}

void TitleSceneDraw(){
	if (feedOn) 
	{
		float feed = (cos((feedCounter)*DX_PI_F / 180) + 1) / 2;//フェード cos結果
		//半透明を設定
		SetDrawBlendMode(DX_BLENDMODE_ALPHA,(int)(255 * feed));
		//真っ黒にする
		DrawBox(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, 0x0, TRUE);
	}

	//文字の横幅
	int widNum = GetDrawFormatStringWidthToHandle(titleFont, dispStr.c_str());

	//ｘ座標
	int x = SCREEN_WIDTH  / 2 - widNum/2;
	//ｙ座標
	int y = SCREEN_HEIGHT / 2 - titleFontSize;

	//toHandle用の文字描画
	DrawFormatStringToHandle(x,y,0xffffff,titleFont,dispStr.c_str());
	//文字描画
	DrawFormatString(SCREEN_WIDTH/2,SCREEN_HEIGHT/2,0x0fffff,"Title");

	std::string explanation = "操作方法\n";
	explanation += "WASDで移動\n";
	explanation += "左マウスで単発\n";
	explanation += "右マウスで連射\n";
	explanation += "";
	DrawFormatString(10, 10, 0xffffff, explanation.c_str());

	//半透明解除
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND,0);
}

void TitleSceneDelete(){
	//-1じゃなかったら ハンドル有
	if (titleFont > 0)
	{
		//ハンドル削除
		DeleteFontToHandle(titleFont);
	}
	//無いので初期化
	titleFont = -1;
}
