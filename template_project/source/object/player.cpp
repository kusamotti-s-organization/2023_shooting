#include "player.h"

#include<DxLib.h>
#include<algorithm>
#include"../main/config.h"
#include"../common.h"
#include"bullet.h"
#include"graphic.h"

namespace {
	constexpr float PLAYER_SPEED = 2.f;//プレイヤーの移動速度
	constexpr float SHOT_COOL_TIME = 0.09f;//ショットのクールタイム
	Position position;//プレイヤー座標
	float shotCoolTime;//カウンタ
	bool keystop;//前回のキー入力の記録
	bool onKey;//現在のキー入力
}

void PlayerInit() {
	position.x = SCREEN_WIDTH / 2;
	position.y = SCREEN_HEIGHT / 2;
	shotCoolTime = SHOT_COOL_TIME * 60.f;
	keystop = true;
	onKey = false;
}

void PlayerUpdate() {

	//bool へ暗黙的キャスト

	bool upKey		= CheckHitKey(KEY_INPUT_W);
	bool downKey	= CheckHitKey(KEY_INPUT_S);
	bool leftKey	= CheckHitKey(KEY_INPUT_A);
	bool rightKey	= CheckHitKey(KEY_INPUT_D);


	//画面左端か ｘ座標-左への 大きい方を 代入
	position.x = (std::max)(0.f, position.x+(int)leftKey* PLAYER_SPEED * -1);
	//画面右端か ｘ座標+右への 小さい方を 代入
	position.x = (std::min)((float)SCREEN_WIDTH, position.x+(int)rightKey * PLAYER_SPEED * 1);
	//画面上端か y座標-上への 大きい方を 代入
	position.y = (std::max)(0.f, position.y+(int)upKey * PLAYER_SPEED * -1);
	//画面下端か y座標+下への 小さい方を 代入
	position.y = (std::min)((float)SCREEN_HEIGHT, position.y+(int)downKey * PLAYER_SPEED * 1);

	//前回の記録へキー入力を代入
	keystop = onKey;
	//現在のキー入力を代入
	onKey = GetMouseInput() & MOUSE_INPUT_LEFT;
	//キー入力 前回が押してなくて現在が押しているとき
	if (onKey && !keystop)
	{
		//1つ弾生成
		BulletCreate(position.x, position.y);
	}
	
	//弾のクールタイムカウンタ
	shotCoolTime += -1.f;

	//０より小さいなら
	if (shotCoolTime <= 0)
	{
		//０代入
		shotCoolTime = 0;
	}

	//マウス右クリックとクールタイムが過ぎたら
	if ((GetMouseInput() & MOUSE_INPUT_RIGHT)&&shotCoolTime <= SHOT_COOL_TIME)
	{
		//クールタイムを入れる
		shotCoolTime = SHOT_COOL_TIME * 60.f;
		//弾を生成
		BulletCreate(position.x,position.y);
	}

}

void PlayerDraw(){
	//最初位置を確認するために書いたデバッグ用
	//DrawCircleAA(position.x,position.y,7.f,22,0x0fffff);

	//プレイヤー描画 概ね赤色 0xdd2222
	PlayerGraphicDraw(position.x,position.y,20.f,0xdd2222);
}

void PlayerDelete(){
	//消すものなし
	/* 
	 * ここには 
	 * LoadGraphなどで読み込んだものや
	 * メモリを確保したものを解放するために書かれる関数
	 * 詳しくはそのうち。。。
	 * あるいは先生へ
	 * または先輩へ
	 * 
	 */
}
