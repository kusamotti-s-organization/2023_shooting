#include "graphic.h"

#include<DxLib.h>

namespace {
	//変数用
	//namespaceは他の使い方もあり
}

void GraphicInit(){
	//使わなかった
}

void GraphicUpdate(){
	//使わなかった

}

void GraphicDraw(){
	//使わなかった

}

void GraphicDelete(){
	//使わなかった

}

void TargetGraphicDrawColor(float x, float y, float r) {
	//白
	DrawCircleAA(x, y, r*5/5.f, 22,0xfdfdfd);
	//黒
	DrawCircleAA(x, y, r*4/5.f, 22, 0x000000);
	//青
	DrawCircleAA(x, y, r*3/5.f, 22, 0x6666fd);
	//赤
	DrawCircleAA(x, y, r*2/5.f, 22, 0xfd0000);
	//黄
	DrawCircleAA(x, y, r*1/5.f, 22, 0xfdfd66);
}

void TargetGraphicDrawMono(float x,float y,float r) {
	//黒
	DrawCircleAA(x,y,r*6/6.f,22,0x0);
	//白
	DrawCircleAA(x,y,r*5/6.f,22,0xffffff);
	//黒
	DrawCircleAA(x,y,r*4/6.f,22,0x0);
	//白
	DrawCircleAA(x,y,r*3.3f/6.f,22,0xffffff);
	//黒
	DrawCircleAA(x,y,r*2/6.f,22,0x0);
	//白
	DrawCircleAA(x,y,r*1/6.f,22,0xffffff);
}

void ArrowGraphicDrawUp(float x,float y,float s){
	float tenTree=3/10.f;
	float tenTreeSize = s*tenTree;
	//羽
	for (int i = 6; i >= 0; --i) {
		float offset = 1 / 10.f *i;

		//概ね灰色 と白色
		DrawTriangleAA(x, y+s -(s * i / 10)-offset, x - tenTreeSize, y + s - offset, x + tenTreeSize, y + s - offset, 0xdddddd * (i % 2), TRUE);
	}
	//矢の柄のほう 概ね黄色 0xdddd99
	DrawBoxAA(x-s/10,y-s*9/10.f ,x+s/10,y+s,0xdddd99,TRUE);

	//矢じり
	float yArrowHead = y - s;
	float yArrowHeadEnd = yArrowHead+ tenTreeSize;
	//概ね灰色 0xaaaaaa
	DrawTriangleAA(x,yArrowHead,x- tenTreeSize, yArrowHeadEnd,x+ tenTreeSize, yArrowHeadEnd,0xaaaaaa,TRUE);
	
}

void PlayerGraphicDraw(float x, float y, float s,int color){
	float halfSize = s / 2.f;
	DrawCircleAA(x - (halfSize-s/10.f)-1,y-s/50.f,s/2.5f,22,color);
	DrawCircleAA(x + (halfSize-s/10.f),y-s/50.f,s/2.5f,22,color);
	DrawTriangleAA(x,y + s,x- (s-s/10.f),y,x + (s-s/10),y,color,TRUE);
}
