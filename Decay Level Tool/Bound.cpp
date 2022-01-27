#include "Bound.h"

Bound::Bound(float t, float l, float r, float b) {
	top = t;
	left = l;
	right = r;
	bot = b;
}

Bound::Bound() {
	top = 0;
	left = 0;
	right = 0;
	bot = 0;
}

float Bound::getTop() { return top; }
float Bound::getLeft() { return left; }
float Bound::getRight() { return right; }
float Bound::getBot() { return bot; }

bool Bound::contains(Vector2i position) {
	return (position.x > left && position.x < right &&
		position.y > top && position.y < bot);
}

Vector2f Bound::getCenter() {
	float x = (right + left) / 2;
	float y = (bot + top) / 2;
	return Vector2f(x, y);
}