#include"gameover.h"
#include<DxLib.h>
#include"common.h"
#include"config.h"
namespace {

}

void GameoverInit() {
	

}
void GameoverUpdate() {

}
void GameoverDraw() {
	SetFontSize(64);
	DrawFormatString(SCREEN_WIDTH/3+1,SCREEN_HEIGHT/3,GetColor(150,150,150),"game over");
	DrawFormatString(SCREEN_WIDTH/3-1,SCREEN_HEIGHT/3,GetColor(150,150,150),"game over");
	DrawFormatString(SCREEN_WIDTH/3,SCREEN_HEIGHT/3+1,GetColor(150,150,150),"game over");
	DrawFormatString(SCREEN_WIDTH/3,SCREEN_HEIGHT/3-1,GetColor(150,150,150),"game over");
	DrawFormatString(SCREEN_WIDTH/3,SCREEN_HEIGHT/3,GetColor(50,50,200),"game over");
	SetFontSize(16);
}
void GameoverDelete() {

}
