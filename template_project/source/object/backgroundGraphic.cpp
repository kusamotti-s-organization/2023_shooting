#include "backgroundGraphic.h"

#include<DxLib.h>
#include<cassert>
#include"../main/config.h"

namespace {
	int backgraphic;//画像ハンドル
}

void BackgroundGraphicInit(){
	//メモリに読み込み
	backgraphic = LoadGraph("data/texture/背景写真補完の会/mirai1.jpg");
	//-1が入っていたら読み込みエラー
	assert(backgraphic > 0);
}

void BackgroundGraphicUpdate(){
	//使わなかった
	//動かすなら使う
}

void BackgroundGraphicDraw(){
	//輝度の設定
	SetDrawBright(255/3,255/3,255);
	//背景を画面全体に
	DrawExtendGraph(0,0,SCREEN_WIDTH,SCREEN_HEIGHT,backgraphic,TRUE);
	//輝度を戻す
	SetDrawBright(255,255,255);

}

void BackgroundGraphicDelete(){
	//読み込んだら消す
	if(backgraphic>0)
		DeleteGraph(backgraphic);
	backgraphic = -1;
}
