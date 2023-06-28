#include"clear.h"
#include<DxLib.h>
#include"common.h"
#include"config.h"
#include<string>
#include<vector>
using namespace std;
namespace {
	vector<string>str={ "G","a","m","e"," ","Åô"," ","C","l","e","a","r","!","!"};
	string s = {"thanks for playing"};
	int dispcount=0;
	int c = 0;
	int cc[7] = {};
	double  x=0.0f,
			y=0.0f;
}

void ClearInit() {
	for(int i=0;i<7;i++)
	cc[i] = GetColor(GetRand(155) + 100, GetRand(155) + 100, GetRand(155) + 100);
	dispcount = 0;
	c=0; 
	x = ((SCREEN_WIDTH/2)-((9*64)/2));
	y = SCREEN_HEIGHT/2-64;
}
void ClearUpdate() {
	dispcount++;
	if (dispcount % 17 == 0)
		for(int i=0;i<7;i++)
		cc[i] = GetColor(GetRand(155) + 100, GetRand(155) + 100, GetRand(155) + 100);
}
void ClearDraw() {
	SetFontSize(64);

	for (int i = 0; i < str.size(); i++) {

		//àÍå¬àÍå¬
		if (dispcount < i * 10)
			continue;
		//êFë÷Ç¶
		c = GetColor(255, 255, 255);
		if (i > 6 ) {
			c =cc[i-7];
		}

		//ï\é¶
		DrawFormatString(x + i * 48, y, c, str.at(i).c_str());
	}
	SetFontSize(16);

	if (dispcount > str.size() * 10) {
		DrawFormatString(20, SCREEN_HEIGHT - SCREEN_HEIGHT / 3, GetColor(255, 255, 200), s.c_str());
	}
}
void ClearDelete() {

}
