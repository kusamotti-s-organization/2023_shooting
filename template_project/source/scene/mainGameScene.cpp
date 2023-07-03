#include"mainGameScene.h"

#include<DxLib.h>
#include<cmath>
#include"../main/config.h"
#include"../object/player.h"
#include"../object/enemy.h"
#include"../object/bullet.h"
#include"../object/backgroundGraphic.h"
#include"../object/destroyEffect.h"
#include"../object/wave.h"

namespace {
	int count;//カウンタ
	bool feedoutEnd;//フェードしているか
}

void MainGameSceneInit(){
	count = 0;
	feedoutEnd = false;

	//それぞれの関数を呼び出す

	BackgroundGraphicInit();
	EnemyInit();
	PlayerInit();
	BulletInit();

	DestroyEffectInit();
	WaveInit();
}

void MainGameSceneUpdate(){
	//フェード開始していないなら
	if ( !feedoutEnd) 
	{
		//カウンタ
		++count;

		//カウンタが90より大きいなら
		if (count > 90) 
		{
			//フェード開始
			feedoutEnd = true;
		}

		//早期リターン
		return;
	}

	//それぞれの関数Ｕｐｄａｔｅ処理

	PlayerUpdate();
	BulletUpdate();
	WaveUpdate();
	EnemyUpdate();
	BackgroundGraphicUpdate();

	DestroyEffectUpdate();
}

void MainGameSceneDraw(){
	//それぞれの関数Draw処理

	BackgroundGraphicDraw();
	DestroyEffectDraw();
	EnemyDraw();
	BulletDraw();
	PlayerDraw();
	WaveDraw();

	//フェード開始していないなら
	if (!feedoutEnd)
	{
		//cosの値
		float cosValue = (float)std::abs(std::cos((count)*DX_PI / 180));
		//フェードの値
		int feed = (int)(255 * cosValue);
		//半透明の設定
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, feed);
		//黒画面の描画 黒0x0
		DrawBox(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, 0x0, TRUE);
		//半透明の解除
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}
}

void MainGameSceneDelete(){
	//それぞれの関数メモリ開放処理

	BackgroundGraphicDelete();
	PlayerDelete();
	EnemyDelete();
	BulletDelete();

	DestroyEffectDelete();
	WaveDelete();
}
