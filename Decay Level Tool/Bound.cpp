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