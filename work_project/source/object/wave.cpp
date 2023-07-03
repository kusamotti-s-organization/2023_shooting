#include "wave.h"

#include<DxLib.h>
#include<string>
#include<cassert>
#include<cmath>
#include"../main/config.h"
#include"../sceneManager.h"
#include"enemy.h"

namespace {
	constexpr int ENEMY_INSTANCE_NUM=300;//敵の最大数
	//ウェーブのステート
	enum State{
		start=0
		,wave1_mob
		,wave2_mob
		,wave3_mobAll
		,wave4_boss
		,max
	};
	State state;//現在のステート
	State stateNext;//次のステート
	std::string dispStr = "Wave ";//表示文字
	int fontHandle;//描画ハンドル
	int cosCount;//cos用カウント
	bool standing;//演出（帯の出現
}

void WaveInit(){
	state = State::start;
	stateNext = State::start;
	fontHandle = LoadFontDataToHandle("data/font/なつめもじ.dft");
	assert(fontHandle>0);
	cosCount = 0;
	standing = true;
}
void WaveUpdate(){
	if (standing) 
	{
		//演出が入っているならCosを動かす
		++cosCount;

		//Cosの結果が1から０になったら
		if (cosCount > 90) 
		{
			//色々初期化
			standing = false;
			int stateNum = (int)(state)+1;
			stateNext = (State)(stateNum);
			cosCount = 0;
			ResetInstanceNum();
		}

	}

	
	int instanceCount = GetInstanceNum();//生成数
	bool instance = instanceCount < ENEMY_INSTANCE_NUM;//生成数が一定量を超えていたら

	//ステートの切替があったら
	if (state != stateNext) 
	{
		state = stateNext;
	}

	//ステートに合った敵生成関数を呼ぶ
	if (instance) 
	{
		switch (state)
		{
			case State::start:
				break;
			case State::wave1_mob:
				EnemyMovePattarn(EnemyMovePatternState::right);
				break;
			case State::wave2_mob:
				EnemyMovePattarn(EnemyMovePatternState::left);
				break;
			case State::wave3_mobAll:
				EnemyMovePattarn(EnemyMovePatternState::top);
				break;
			case State::wave4_boss:
				//boss
				//todo:これをボスに変えておく
				ChangeScene(Scene::result);
				break;
			case State::max:
				//今はなし
				break;
			default:
				assert(false);
				break;
		}
	}

	//Release Buildでは通らない デファイン（define）　デバッグ用
#ifdef _DEBUG
	if (CheckHitKey(KEY_INPUT_SPACE) && CheckHitKey(KEY_INPUT_LSHIFT))
	{
		//次のwaveへ
		standing = true;
	}
#endif

	//生成が終わっており、演出がしていない時 
	if (!standing && !instance) 
	{
		//演出をtrueに
		standing = GetActiveEnemy() <= 0;
	}
}

void WaveDraw(){
	//演出がないなら
	if (!standing) 
	{
		//早期リターン
		return;
	}

	float cosValue = (float)std::abs(std::cos((cosCount)*DX_PI / 180));//cosの値
	int feed = (int)(255 * cosValue);//255に掛けた結果
	//SetDrawBlendMode(DX_BLENDMODE_ALPHA, feed);//デバッグ用


	std::string disp = dispStr + std::to_string((int)(state) + 1);//描画用 文字
	int widNum = GetDrawFormatStringWidthToHandle(fontHandle,disp.c_str());//文字の横幅
	int heiNum = GetFontSizeToHandle(fontHandle);//文字の縦幅
	
	int y = SCREEN_HEIGHT / 2;//真ん中
	int fontsize = heiNum;//文字の高さ  処理を書いていたけど結局これになった
	SetDrawBlendMode(DX_BLENDMODE_ALPHA,(int)(255/3 *cosValue));
		//文字用座布団 黒色 0x0
	DrawBoxAA(0,y-fontsize*2.f,SCREEN_WIDTH,y+fontsize*1.5f,0x0,TRUE);

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, feed);
		//描画文字 白色 0xffffff
	DrawFormatStringToHandle(SCREEN_WIDTH/2 -widNum/2,SCREEN_HEIGHT/2 -heiNum,0xffffff,fontHandle,disp.c_str());

	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

void WaveDelete(){
	//-1が入っていたら ハンドルあり
	if (fontHandle > 0)
	{
		//ハンドルを消す
		DeleteFontToHandle(fontHandle);
	}
	//何が入っているかわからないので エラーの値を代入
	fontHandle = -1;
}