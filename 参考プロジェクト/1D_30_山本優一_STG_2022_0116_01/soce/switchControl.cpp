#include"switchControl.h"
#include<DxLib.h>

OnOff::OnOff() {
	keystop = false;
	oneflag = false;
}
//TRUE�ɂȂ�x�ɋA���Ă���l���؂�ւ��
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
//���݂�TRUE FALSE�����Z�b�g����
void OnOff::ResetControl() {
	keystop = false;
	oneflag = false;
}