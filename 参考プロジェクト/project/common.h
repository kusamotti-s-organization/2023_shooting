#pragma once

struct POSITION {
	double x;
	double y;
};

struct CIRCLE {
	int x, y; // ���S���W
	int r; // ���a
};

// �~�Ɖ~�̓����蔻����s��
// �������Ă����true��Ԃ�
bool CircleCollision(CIRCLE c1, CIRCLE c2);