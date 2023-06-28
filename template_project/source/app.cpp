#include"app.h"

#include<DxLib.h>

#include"config.h"

namespace APP {
	void Init() {

	}
	void Update() {

	}
	void Draw() {

	}
	void Delete() {

	}

	bool GameEnd() {
		if (CheckHitKey(KEY_INPUT_ESCAPE)) 
			return true;

		if (CheckHitKey(KEY_INPUT_W) && CheckHitKey(KEY_INPUT_LCONTROL))
			return true;

		return false;
	}
}
