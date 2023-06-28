#include"backimg.h"
#include<DxLib.h>
#include"common.h"
#include"config.h"
#include"player.h"

namespace {
	enum LINE {
		lu,//¶ã‚©‚ç‰E‰º
		ld,//¶‰º‚©‚ç‰Eã
		maxlinepattern,
	};

	const int linenum = 25;
	struct LINES {
		POS fastpos[maxlinepattern] = {};
		POS endpos[maxlinepattern] = {};
		POS syokifastpos = {};
		POS syokiendpos = {};
		int pattern = -1;
	};
	LINES line[linenum];
}

void LuReset() {
	for (int i = 0; i < linenum ; i++) {
	line[i].fastpos[lu].x = 0					+SCREEN_WIDTH+SCREEN_WIDTH/(i+1)+i*50;
	line[i].fastpos[lu].y = 0					;
	line[i].endpos[lu].x = (SCREEN_WIDTH / 3)	+SCREEN_WIDTH+SCREEN_WIDTH/(i+1)+i*50;
	line[i].endpos[lu].y = 0 + SCREEN_HEIGHT	;
	}
}
void LdReset() {
	for (int i = 0; i < linenum; i++) {
	line[i].fastpos[ld].x = 0					+SCREEN_WIDTH+SCREEN_WIDTH/(i+1)+i*50;
	line[i].fastpos[ld].y = 0 + SCREEN_HEIGHT	;
	line[i].endpos [ld].x = (SCREEN_WIDTH / 3)	+SCREEN_WIDTH+SCREEN_WIDTH/(i+1)+i*50;
	line[i].endpos [ld].y = 0					;
	}
}

void BackimgInit() {
			LuReset();
			LdReset();
	for (int i = 0; i < linenum; i++) {
		//line[i] = {};
		line[i].pattern = i % 2;
		line[i].syokifastpos = line[i].fastpos[line[i].pattern];
		line[i].syokiendpos = line[i].endpos[line[i].pattern];

	}
}

void BackimgUpdate() {
	for (int i = 0; i < linenum; i++) {
		int p=line[i].pattern;
		POS pv = GetPlayerVX();
		line[i].fastpos[p].x +=pv.x;
		line[i].endpos[p] .x +=pv.x;

			line[i].fastpos[p].x += -20;
			line[i].endpos [p].x += -20;
		
		
		if (line[i].endpos[p].x < 0) {
			line[i].fastpos[p] = line[i].syokifastpos;
			line[i].endpos[p] = line[i].syokiendpos;
		}
	}

}
void BackimgDraw() {
	SetDrawBlendMode(DX_BLENDMODE_ALPHA,100);
	
	for (int i = 0; i < linenum; i++) {
		int p=line[i].pattern;
			DrawLine(	line[i].fastpos[p].x, line[i].fastpos[p].y,
						line[i].endpos [p].x, line[i].endpos [p].y,
				GetColor(255, 255, 255), 5);
	}
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

}
void BackimgDelete() {

}

