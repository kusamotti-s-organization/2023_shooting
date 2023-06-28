#include"switchControl.h"
#include<DxLib.h>

OnOff::OnOff() {
	keystop = false;
	oneflag = false;
}
//TRUEになる度に帰ってくる値が切り替わる
bool OnOff::SwitchControl(bool keyflag) {
	if (keyflag&&!keystop) {
		if (oneflag) {
			oneflag = false;
		}
		else if(!oneflag){
			oneflag = true;
		}
		keystop = true;
	}
	else if (!keyflag)keystop = false;
	
	return oneflag;
}
//現在のTRUE FALSEをリセットする
void OnOff::ResetControl() {
	keystop = false;
	oneflag = false;
}