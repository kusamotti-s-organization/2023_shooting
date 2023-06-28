#pragma once

struct POSITION {
	double x;
	double y;
};

struct CIRCLE {
	int x, y; // ’†SÀ•W
	int r; // ”¼Œa
};

// ‰~‚Æ‰~‚Ì“–‚½‚è”»’è‚ğs‚¤
// “–‚½‚Á‚Ä‚¢‚ê‚Îtrue‚ğ•Ô‚·
bool CircleCollision(CIRCLE c1, CIRCLE c2);