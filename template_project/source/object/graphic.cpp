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
	//��
	DrawCircleAA(x, y, r*5/5.f, 22,0xfdfdfd);
	//��
	DrawCircleAA(x, y, r*4/5.f, 22, 0x000000);
	//��
	DrawCircleAA(x, y, r*3/5.f, 22, 0x6666fd);
	//��
	DrawCircleAA(x, y, r*2/5.f, 22, 0xfd0000);
	//��
	DrawCircleAA(x, y, r*1/5.f, 22, 0xfdfd66);
}

void TargetGraphicDrawMono(float x,float y,float r) {
	//��
	DrawCircleAA(x,y,r*6/6.f,22,0x0);
	//��
	DrawCircleAA(x,y,r*5/6.f,22,0xffffff);
	//��
	DrawCircleAA(x,y,r*4/6.f,22,0x0);
	//��
	DrawCircleAA(x,y,r*3.3f/6.f,22,0xffffff);
	//��
	DrawCircleAA(x,y,r*2/6.f,22,0x0);
	//��
	DrawCircleAA(x,y,r*1/6.f,22,0xffffff);
}

void ArrowGraphicDrawUp(float x,float y,float s){
	float tenTree=3/10.f;
	float tenTreeSize = s*tenTree;
	//�H
	for (int i = 6; i >= 0; --i) {
		float offset = 1 / 10.f *i;

		
		DrawTriangleAA(x, y+s -(s * i / 10)-offset, x - tenTreeSize, y + s - offset, x + tenTreeSize, y + s - offset, 0xdddddd * (i % 2), TRUE);
	}
	//��̕��̂ق�
	DrawBoxAA(x-s/10,y-s*9/10.f ,x+s/10,y+s,0xdddd99,TRUE);

	//���
	float yArrowHead = y - s;
	float yArrowHeadEnd = yArrowHead+ tenTreeSize;
	DrawTriangleAA(x,yArrowHead,x- tenTreeSize, yArrowHeadEnd,x+ tenTreeSize, yArrowHeadEnd,0xaaaaaa,TRUE);
	
}
