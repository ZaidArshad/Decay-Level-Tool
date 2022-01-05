#include "Resizer.h"


Resizer::Resizer(Canvas* c, Platform* p, float x, float y) {
	self = p;
	parent = p;
	canvas = c;
	width = SIZE;
	height = SIZE;
	rectangleShape.setSize(Vector2f(width, height));
	rectangleShape.setOrigin(width / 2, height/ 2);
	rectangleShape.setFillColor(COLOR);

	drawable = &rectangleShape;
	transformable = &rectangleShape;

	xPos = x;
	yPos = y;
	isClicked = false;
	canvasBound = c->getBound();
	setClickableBound();

	rectangleShape.setPosition(xPos, yPos);
}

void Resizer::setPos(float x, float y) {
	setPosition(Vector2f(x, y));
	rectangleShape.setOrigin(width / 2, height / 2);
}