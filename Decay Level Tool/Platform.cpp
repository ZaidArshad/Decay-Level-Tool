#include "Platform.h"
#include "Resizer.h"
#include <iostream>

Platform::Platform(Canvas* c, int h) {
	self = this;
	canvas = c;
	health = h;
	width = 100;
	height = 20;
	rectangleShape.setSize(Vector2f(width, height));
	rectangleShape.setOrigin(width / 2, height / 2);
	rectangleShape.setFillColor(HEALTH_INDEX[health]);

	drawable = &rectangleShape;
	transformable = &rectangleShape;

	Vector2f position = c->getCenterPosition();
	xPos = position.x;
	yPos = position.y;
	isClicked = false;
	canvasBound = c->getBound();
	setClickableBound();

	rectangleShape.setPosition(xPos, yPos);
	generateResizers();
}

Platform::~Platform() {
	resizers.clear();
}

void Platform::draw(RenderWindow& window) {
	draggable(window);

	if (isShowingResizers) {
		updateResizers();
		for (Resizer* resizer : resizers) {
			resizer->draggable(window);
			resizer->draw(window);
		}
	}

	if (canvas->getLastClicked() == this) {
		setClicked(window);
	}
	else {
		isShowingResizers = false;
	}

	window.draw(*drawable);
}

void Platform::setWidth(int w) {
	width = w;
	rectangleShape.setSize(Vector2f(width, height));
}

void Platform::setHeight(int h) {
	height = h;
	rectangleShape.setSize(Vector2f(width, height));
}

float Platform::getX() { return xPos; }
float Platform::getY() { return yPos; }

void Platform::setClicked(RenderWindow& window) {
	if (!isShowingResizers) {
		isShowingResizers = true;
	}
}

void Platform::updateResizers() {
	float offset = Resizer::SIZE / 2;

	Resizer* tl = resizers[0];

	tl->setPos(
		clickableBound.getLeft() - offset, clickableBound.getTop() - offset);

	Resizer* tr = resizers[1];
	tr->setPos(
		clickableBound.getRight() + offset, clickableBound.getTop() - offset);

	Resizer* bl = resizers[2];
	bl->setPos(
		clickableBound.getLeft() - offset, clickableBound.getBot() + offset);

	Resizer* br = resizers[3];
	br->setPos(
		clickableBound.getRight() + offset, clickableBound.getBot() + offset);
}

void Platform::generateResizers() {
	float offset = Resizer::SIZE / 2;

	Resizer* tl = new Resizer(canvas, this,
		clickableBound.getLeft() - offset, clickableBound.getTop() - offset);
	Resizer* tr = new Resizer(canvas, this,
		clickableBound.getRight() + offset, clickableBound.getTop() - offset);
	Resizer* bl = new Resizer(canvas, this,
		clickableBound.getLeft() - offset, clickableBound.getBot() + offset);
	Resizer* br = new Resizer(canvas, this,
		clickableBound.getRight() + offset, clickableBound.getBot() + offset);

	resizers.push_back(tl);
	resizers.push_back(tr);
	resizers.push_back(bl);
	resizers.push_back(br);
}