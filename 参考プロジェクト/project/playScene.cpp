#include "playScene.h"
#include <DxLib.h>
#include "app.h"
#include "player.h"
#include "stones.h"
#include "enemies.h"
#include "score.h"

void PlaySceneInit()
{
	PlayerInit();
	StonesInit();
	EnemiesInit();
	ScoreInit();
}

void PlaySceneUpdate()
{
	if (CheckHitKey(KEY_INPUT_T)) {
		ChangeScene(TITLE_SCENE);
	}
	PlayerUpdate();
	StonesUpdate();
	EnemiesUpdate();
}

void PlaySceneDraw()
{
	EnemiesDraw();
	PlayerDraw();
	StonesDraw();
	ScoreDraw();
	DrawString(600, 10, "PLAY SCENE", GetColor(255, 255, 255));
	DrawString(10, 500, "Push [T] Key To Title", GetColor(255, 255, 255));
}

void PlaySceneRelease()
{
	PlayerRelease();
	StonesRelease();
	EnemiesRelease();
}