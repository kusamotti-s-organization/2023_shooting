#include "titleScene.h"

#include<DxLib.h>
#include"../main/config.h"
#include"../sceneManager.h"


namespace {
	bool keystop=true;
	bool onKey = false;
}

void TitleSceneInit(){
	keystop = true;
	onKey = false;
}

void TitleSceneUpdate(){
	
	keystop = onKey;
	onKey = CheckHitKey(KEY_INPUT_RETURN);
	
	if (onKey && !keystop) {
		ChangeScene(Scene::mainGame);
	}
}

void TitleSceneDraw(){
	DrawFormatString(SCREEN_WIDTH/2,SCREEN_HEIGHT/2,0x0fffff,"Title");


}

void TitleSceneDelete(){

}
