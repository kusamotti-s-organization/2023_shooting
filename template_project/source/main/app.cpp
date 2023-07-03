#include"app.h"

#include<DxLib.h>

#include"config.h"
#include"../sceneManager.h"

namespace APP {
	void Init() {
		Init_SceneManager();
	}
	void Update() {
		Updata_SceneManager();
	}
	void Draw() {
		Draw_SceneManager();
	}
	void Delete() {
		Delete_SceneManager();
	}

	bool GameEnd() {
		if (CheckHitKey(KEY_INPUT_ESCAPE)) 
			return true;

		if (CheckHitKey(KEY_INPUT_W) && CheckHitKey(KEY_INPUT_LCONTROL))
			return true;

		return false;
	}
}
