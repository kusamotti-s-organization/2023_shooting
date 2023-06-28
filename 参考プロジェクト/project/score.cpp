#include "score.h"
#include <DxLib.h>

namespace {
	int score;
};

void ScoreInit()
{
	score = 0;
}

void ScoreDraw()
{
	DrawFormatString(10, 10, GetColor(255,255,255), "SCORE: %7d", score);
}

void ScoreAdd(int val)
{
	score += val;
}
