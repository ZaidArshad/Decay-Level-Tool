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

void Platform::draw(RenderWindow& window) {
	draggable(window);
	if (canvas->getLastClicked() == this) {
		setClicked(window);
	}
	window.draw(*drawable);
}

void Platform::setClicked(RenderWindow& window) {
	RectangleShape tl = RectangleShape(Vector2f(5, 5));
	tl.setPosition(clickableBound.getLeft() - 5, clickableBound.getTop() - 5);
	tl.setFillColor(Color(255, 0, 0));
	window.draw(tl);

	RectangleShape tr = RectangleShape(Vector2f(5, 5));
	tr.setPosition(clickableBound.getRight(), clickableBound.getTop() - 5);
	tr.setFillColor(Color(255, 0, 0));
	window.draw(tr);

	RectangleShape bl = RectangleShape(Vector2f(5, 5));
	bl.setPosition(clickableBound.getLeft() - 5, clickableBound.getBot());
	bl.setFillColor(Color(255, 0, 0));
	window.draw(bl);

	RectangleShape br = RectangleShape(Vector2f(5, 5));
	br.setPosition(clickableBound.getRight(), clickableBound.getBot());
	br.setFillColor(Color(255, 0, 0));
	window.draw(br);
}