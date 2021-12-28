#include "Canvas.h"

Canvas::Canvas(int w, int h, float x, float y, Color bg) {
	width = w;
	height = h;
	xPos = x;
	yPos = y;
	backgroundColor = bg;

	background.setSize(Vector2f(width, height));
	background.setFillColor(backgroundColor);
	background.setPosition(xPos, yPos);
	bound = Bound(xPos, yPos, width+xPos, height+yPos);
}

Vector2f Canvas::getCenterPosition() {
	float x = (width / 2) + xPos;
	float y = (height / 2) + yPos;
	return Vector2f(x, y);
}

RectangleShape Canvas::getBackground() { return background; }
Bound Canvas::getBound() { return bound; }

