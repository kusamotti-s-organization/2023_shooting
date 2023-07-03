#include"app.h"

#include<DxLib.h>

#include"config.h"
#include"../sceneManager.h"

//メインに書く用
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
		//エスケープキーを押したら
		if (CheckHitKey(KEY_INPUT_ESCAPE))
		{
			//早期リターン
			return true;
		}
		//左CtrlとWキーを押したら
		if (CheckHitKey(KEY_INPUT_W) && CheckHitKey(KEY_INPUT_LCONTROL))
		{
			//早期リターン
			return true;
		}

		//結果を返す
		return false;
	}
}
