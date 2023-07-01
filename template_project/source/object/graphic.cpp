#include "graphic.h"

#include<DxLib.h>

namespace {

}

void GraphicInit(){

}

void GraphicUpdate(){

}

void GraphicDraw(){

}

void GraphicDelete(){

}

void TargetGraphicDrawColor(float x, float y, float r) {
	//îí
	DrawCircleAA(x, y, r*5/5.f, 22,0xfdfdfd);
	//çï
	DrawCircleAA(x, y, r*4/5.f, 22, 0x000000);
	//ê¬
	DrawCircleAA(x, y, r*3/5.f, 22, 0x6666fd);
	//ê‘
	DrawCircleAA(x, y, r*2/5.f, 22, 0xfd0000);
	//â©
	DrawCircleAA(x, y, r*1/5.f, 22, 0xfdfd66);
}

void TargetGraphicDrawMono(float x,float y,float r) {
	//çï
	DrawCircleAA(x,y,r*6/6.f,22,0x0);
	//îí
	DrawCircleAA(x,y,r*5/6.f,22,0xffffff);
	//çï
	DrawCircleAA(x,y,r*4/6.f,22,0x0);
	//îí
	DrawCircleAA(x,y,r*3.3f/6.f,22,0xffffff);
	//çï
	DrawCircleAA(x,y,r*2/6.f,22,0x0);
	//îí
	DrawCircleAA(x,y,r*1/6.f,22,0xffffff);
}
