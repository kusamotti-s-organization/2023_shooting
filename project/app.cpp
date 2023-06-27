#include "app.h"
#include "titleScene.h"
#include "playScene.h"

namespace {
	SCENE_ID currentScene;
	SCENE_ID nextScene;
};

void AppInit()
{
	currentScene = TITLE_SCENE;
	nextScene = currentScene;
	switch (currentScene) {
	case TITLE_SCENE:
		TitleSceneInit();
		break;
	case PLAY_SCENE:
		PlaySceneInit();
		break;
	}
}

void AppUpdate()
{
	if (nextScene!=currentScene) {
		switch (currentScene) {
		case TITLE_SCENE:
			TitleSceneRelease();
			break;
		case PLAY_SCENE:
			PlaySceneRelease();
			break;
		}
		currentScene = nextScene;
		switch (currentScene) {
		case TITLE_SCENE:
			TitleSceneInit();
			break;
		case PLAY_SCENE:
			PlaySceneInit();
			break;
		}
	}
	switch (currentScene) {
	case TITLE_SCENE:
		TitleSceneUpdate();
		break;
	case PLAY_SCENE:
		PlaySceneUpdate();
		break;
	}
}

void AppDraw()
{
	switch (currentScene) {
	case TITLE_SCENE:
		TitleSceneDraw();
		break;
	case PLAY_SCENE:
		PlaySceneDraw();
		break;
	}
}

void AppRelease()
{
	switch (currentScene) {
	case TITLE_SCENE:
		TitleSceneRelease();
		break;
	case PLAY_SCENE:
		PlaySceneRelease();
		break;
	}
}

void ChangeScene(SCENE_ID scene)
{
	nextScene = scene;
}
