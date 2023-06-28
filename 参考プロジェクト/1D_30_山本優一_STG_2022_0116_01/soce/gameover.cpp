#include"gameover.h"
#include<DxLib.h>
#include"common.h"
#include"config.h"
#include"randquake.h"
namespace {
	VECTOR pos = {0,0,0};
	VECTOR spos = {0,0,0};
}

void GameoverInit() {
	pos.x= SCREEN_WIDTH / 3.0f;
	pos.y= SCREEN_HEIGHT / 3.0f;
	spos = pos;
}
void GameoverUpdate() {
	if (RandQuakeGetActive()) {
	VECTOR p = RandQuakeMove();
	VectorAdd(&pos,&pos,&p);
	}
	else {
		pos = spos;
	}

}
void GameoverDraw() {
	SetFontSize(64);
	DrawFormatString(pos.x+1,pos.y  ,GetColor(150,150,150),"game over");
	DrawFormatString(pos.x-1,pos.y  ,GetColor(150,150,150),"game over");
	DrawFormatString(pos.x  ,pos.y+1,GetColor(150,150,150),"game over");
	DrawFormatString(pos.x  ,pos.y-1,GetColor(150,150,150),"game over");
	DrawFormatString(pos.x  ,pos.y  ,GetColor(50,50,200),"game over");
	SetFontSize(16);
}
void GameoverDelete() {

}
