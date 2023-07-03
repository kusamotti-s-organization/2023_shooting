#include "backgroundGraphic.h"

#include<DxLib.h>
#include<cassert>
#include"../main/config.h"

namespace {
	int backgraphic;
}

void BackgroundGraphicInit(){
	backgraphic = LoadGraph("data/texture/背景写真補完の会/mirai1.jpg");
	assert(backgraphic > 0);
}

void BackgroundGraphicUpdate(){

}

void BackgroundGraphicDraw(){
	SetDrawBright(255/3,255/3,255);
	DrawExtendGraph(0,0,SCREEN_WIDTH,SCREEN_HEIGHT,backgraphic,TRUE);
	SetDrawBright(255,255,255);

}

void BackgroundGraphicDelete(){
	if(backgraphic>0)
		DeleteGraph(backgraphic);
	backgraphic = -1;
}
