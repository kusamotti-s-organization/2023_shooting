#include"common.h"
#include<DxLib.h>
#include"config.h"
namespace {
	int mousex=SCREEN_WIDTH /2, 
		mousey=SCREEN_HEIGHT/2;
}

bool SquareCollision(SQUAREPOS my,SQUAREPOS en) {
	bool	 left	=my.tl.x<en.br.x,
			right	=my.br.x>en.tl.x, 
			up		=my.tl.y<en.br.y, 
			down	=my.br.y>en.tl.y;
	bool collision = left && right && up && down;
	return collision;

}
bool CircleCollision(POS _p1,double _size1,POS _p2,double _size2) {
	double x=_p1.x-_p2.x;//íÍï”
	double y=_p1.y-_p2.y;//çÇÇ≥
	double r=_size1+_size2;//éŒï”
	bool collision=(x*x+y*y<=r*r);

	return collision;
}
POS PosAdd(POS a, POS b) {
	POS e;
	e.x = a.x + b.x;
	e.y = a.y + b.y;
	return e;
}
POS PosSub(POS a,POS b) {
	POS e;
	e.x=a.x-b.x;
	e.y=a.y-b.y;
	return e;
}

void MouseUpdate() {
	GetMousePoint(&mousex,&mousey);
}
int GetMouseX() {
	return mousex;
}
int GetMouseY() {
	return mousey;
}