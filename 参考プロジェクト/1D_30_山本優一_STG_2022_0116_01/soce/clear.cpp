#include"clear.h"
#include<DxLib.h>
#include"common.h"
#include"config.h"
#include<string>
#include<vector>
#include"item.h"
using namespace std;
namespace {
	vector<string>str={ "G","a","m","e"," ","☆"," ","C","l","e","a","r","!","!"};
	string s = {"thanks for playing"};
	int dispcount=0;
	int c = 0;
	int cc[7] = {};
	double  x=0.0f,
			y=0.0f;

	int itemnum[3] = {0,0,0};
}

void ClearInit() {
	for(int i=0;i<7;i++)
	cc[i] = GetColor(GetRand(155) + 100, GetRand(155) + 100, GetRand(155) + 100);
	dispcount = 0;
	c=0; 
	x = ((SCREEN_WIDTH/2)-((9*64)/2));
	y = SCREEN_HEIGHT/2.5f-64;

	for (int i = 0; i < 3; i++) {
		itemnum[i] = 0;
	}
}
void ClearUpdate() {
	itemnum[0]=ItemGetR();
	itemnum[1]=ItemGetG();
	itemnum[2]=ItemGetB();
	dispcount++;
	if (dispcount % 17 == 0)
		for(int i=0;i<7;i++)
		cc[i] = GetColor(GetRand(155) + 100, GetRand(155) + 100, GetRand(155) + 100);
}
void ClearDraw() {
	SetFontSize(64);

	for (int i = 0; i < str.size(); i++) {

		//一個一個
		if (dispcount < i * 10)
			continue;
		//色替え
		c = GetColor(255, 255, 255);
		if (i > 6 ) {
			c =cc[i-7];
		}

		//表示
		DrawFormatString(x + i * 48, y, c, str.at(i).c_str());
	}
	SetFontSize(16);

	if (dispcount > (int)str.size() * 10) {
		SetFontSize(20);
		DrawFormatString(SCREEN_WIDTH / 1.3f, SCREEN_HEIGHT / 7.0f, GetColor(200, 200, 200), "獲得アイテム数\n 赤：%d\n 緑：%d\n 青：%d", itemnum[0], itemnum[1], itemnum[2]);
		SetFontSize(16);
		DrawFormatString(20, SCREEN_HEIGHT - SCREEN_HEIGHT / 3, GetColor(255, 255, 200), s.c_str());
	}
}
void ClearDelete() {

}
