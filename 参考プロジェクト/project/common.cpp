#include "common.h"

bool CircleCollision(CIRCLE c1, CIRCLE c2)
{
	int dx = c1.x - c2.x;
	int dy = c1.y - c2.y;
	int rs = c1.r + c2.r;
	if (dx*dx + dy*dy <= rs*rs)
		return true;
	return false;
}
