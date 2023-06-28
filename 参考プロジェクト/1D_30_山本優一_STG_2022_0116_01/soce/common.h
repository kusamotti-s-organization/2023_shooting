#pragma once

struct VEC {
	float vx;
	float vy;
};

struct POS {
	double x;
	double y;
};

struct SQUAREPOS {
	POS tl;//Top Left
	POS br;//Bottom Right
};
struct COLOR {
	int r, g, b;
};
bool SquareCollision(SQUAREPOS my, SQUAREPOS en);
bool CircleCollision(POS _p1,double _size1,POS _p2,double _size2);
void MouseUpdate();
int GetMouseX();
int GetMouseY();
POS PosAdd(POS a, POS b);
POS PosSub(POS a, POS b);
