#include "titleScene.h"
#include <DxLib.h>
#include "app.h"

void TitleSceneInit()
{
}

void TitleSceneUpdate()
{
	if (CheckHitKey(KEY_INPUT_P)) {
		ChangeScene(PLAY_SCENE);
	}
}

void TitleSceneDraw()
{
	DrawString(10, 10, "TITLE SCENE", GetColor(255,255,255));
	DrawString(10, 500, "Push [P] Key To Play", GetColor(255,255,255));
}

void TitleSceneRelease()
{
}
