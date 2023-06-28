#pragma once
class OnOff {
	bool keystop = false;
	bool oneflag = false;
public:
	OnOff();
	bool SwitchControl(bool keyflag);
	void ResetControl();
};