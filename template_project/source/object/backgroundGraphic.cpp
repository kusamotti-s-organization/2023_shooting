#include "backgroundGraphic.h"

#include<DxLib.h>
#include<cassert>
#include"../main/config.h"

namespace {
	int backgraphic;
}

void backgroundGraphicInit(){
	backgraphic = LoadGraph("data/texture/�w�i�ʐ^�⊮�̉�/mirai1.jpg");
	assert(backgraphic > 0);
}

void backgroundGraphicUpdate(){

}

void backgroundGraphicDraw(){
	DrawExtendGraph(0,0,SCREEN_WIDTH,SCREEN_HEIGHT,backgraphic,TRUE);
}

void backgroundGraphicDelete(){
	if(backgraphic>0)
		DeleteGraph(backgraphic);
	backgraphic = -1;
}
