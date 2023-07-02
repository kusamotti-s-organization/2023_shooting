#include "sceneManager.h"

#include"scene/titleScene.h"
#include"scene/mainGameScene.h"

namespace {
	int sceneNumber=0;
	int sceneChangeNumber = 0;

}

void Init_SceneManager(){
	sceneNumber = Scene::start;
	sceneChangeNumber = Scene::title;


}

void Updata_SceneManager(){

	//�����A�V�[���ύX���������Ă�����
	if (sceneNumber != sceneChangeNumber) {

		sceneNumber = sceneChangeNumber;

		//�V�[���ؑւ̉������
		switch (sceneNumber) {
		case Scene::start:
			break;
		case Scene::title:
			TitleSceneDelete();
			break;
		case Scene::mainGame:
			MainGameSceneDelete();
			break;
		case Scene::result:
			break;
		case Scene::staff:
			break;
		default:
			break;
		}
		//�V�[���ؑւ̏�����
		switch (sceneNumber) {
		case Scene::start:
			break;
		case Scene::title:
			TitleSceneInit();
			break;
		case Scene::mainGame:
			MainGameSceneInit();
			break;
		case Scene::result:
			break;
		case Scene::staff:
			break;
		default:
			break;
		}


	}

	//update
	switch (sceneNumber){
	case Scene::start:
		break;
	case Scene::title:
		TitleSceneUpdate();
		break;
	case Scene::mainGame:
		MainGameSceneUpdate();
		break;
	case Scene::result:
		break;
	case Scene::staff:
		break;
	default:
		break;
	}

}

void Draw_SceneManager(){
	//darw
	switch (sceneNumber) {
	case Scene::start:
		break;
	case Scene::title:
		TitleSceneDraw();
		break;
	case Scene::mainGame:
		MainGameSceneDraw();
		break;
	case Scene::result:
		break;
	case Scene::staff:
		break;
	default:
		break;
	}

}

void Delete_SceneManager(){

}

bool ChangeScene(Scene scene){
	//0�ȉ��Ȃ�V�[���ύX�ł��Ȃ�
	if ((int)scene < (int)Scene::start)
		return false;
	//������V�[�����傫�������͎w��ł��Ȃ�
	if ((int)scene >= ((int)Scene::max) - 1 )
		return false;


	sceneChangeNumber = (int)scene;
	return true;
}
