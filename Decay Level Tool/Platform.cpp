#include "Platform.h"
#include <iostream>

Platform::Platform(Canvas* c, int h) {
	canvas = c;
	health = h;
	width = 100;
	height = 20;
	rectangleShape.setSize(Vector2f(width, height));
	rectangleShape.setOrigin(width / 2, height / 2);
	rectangleShape.setFillColor(healthIndex[health]);

	drawable = &rectangleShape;
	transformable = &rectangleShape;

	Vector2f position = c->getCenterPosition();
	xPos = position.x;
	yPos = position.y;
	isClicked = false;
	canvasBound = c->getBound();
	setClickableBound();

	rectangleShape.setPosition(position.x, position.y);
}