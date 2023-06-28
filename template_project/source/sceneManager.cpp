#include "sceneManager.h"

namespace {

	int sceneNumber=0;
	int sceneChangeNumber = 0;

}

void Init_SceneManager(){
	sceneNumber = Scene::start;
	sceneChangeNumber = sceneNumber;

}

void Updata_SceneManager(){

	//�����A�V�[���ύX���������Ă�����
	if (sceneNumber != sceneChangeNumber) {

		sceneNumber = sceneChangeNumber;

		//�V�[���ؑւ̏�����
		switch (sceneNumber) {
		case Scene::start:
			break;
		case Scene::title:
			break;
		case Scene::mainGame:
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
		break;
	case Scene::mainGame:
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
		break;
	case Scene::mainGame:
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
