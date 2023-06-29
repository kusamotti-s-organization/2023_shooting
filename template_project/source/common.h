#pragma once

struct Position {
	float x, y;
};

struct Circle{
	Position m_position;
	float radius;
};

inline Circle GetCircle(float x,float y,float radius) {
	return Circle{ Position{x,y},radius };
}

inline bool CircleCollision(Circle c1,Circle c2) {
	Position vector = {};
	vector.x = c1.m_position.x - c2.m_position.x;
	vector.y = c1.m_position.y - c2.m_position.y;
	float lenght = c1.radius + c2.radius;

	bool anser = (vector.x * vector.x + vector.y * vector.y) <= (lenght * lenght);
	

	return anser;
}