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
		updateResizers(window);
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

int Platform::getWidth() { return width; }
int Platform::getHeight() { return height; }

float Platform::getX() { return rectangleShape.getPosition().x; }
float Platform::getY() { return rectangleShape.getPosition().y; }

void Platform::setOrigin(Vector2f origin) {
	rectangleShape.setOrigin(origin);
}
Vector2f Platform::getOrigin() { return rectangleShape.getOrigin(); }

void Platform::setClicked(RenderWindow& window) {
	if (!isShowingResizers) {
		isShowingResizers = true;
	}
}

void Platform::updateResizers(RenderWindow& window) {
	int size = Resizer::SIZE;

	Resizer* tl = resizers[0];
	if (!tl->getClicked()) {
		tl->setPos(
			clickableBound.getLeft(), clickableBound.getTop());
	}
	else {
		tl->resize(window);
	}

	Resizer* tr = resizers[1];
	if (!tr->getClicked()) {
		tr->setPos(clickableBound.getRight()+size, clickableBound.getTop());
	}
	else {
		tr->resize(window);
	}

	Resizer* bl = resizers[2];
	if (!bl->getClicked()) {
		bl->setPos(clickableBound.getLeft(), clickableBound.getBot()+size);
	}
	else {
		bl->resize(window);
	}

	Resizer* br = resizers[3];
	if (!br->getClicked()) {
		br->setPos(clickableBound.getRight()+size, clickableBound.getBot()+size);
	}
	else {
		br->resize(window);
	}
}

void Platform::generateResizers() {
	float offset = Resizer::SIZE / 2;

	Resizer* tl = new Resizer(canvas, this, Resizer::TOP_LEFT,
		clickableBound.getLeft() - offset, clickableBound.getTop() - offset);
	Resizer* tr = new Resizer(canvas, this, Resizer::TOP_RIGHT,
		clickableBound.getRight() + offset, clickableBound.getTop() - offset);
	Resizer* bl = new Resizer(canvas, this, Resizer::BOT_LEFT,
		clickableBound.getLeft() - offset, clickableBound.getBot() + offset);
	Resizer* br = new Resizer(canvas, this, Resizer::BOT_RIGHT,
		clickableBound.getRight() + offset, clickableBound.getBot() + offset);

	resizers.push_back(tl);
	resizers.push_back(tr);
	resizers.push_back(bl);
	resizers.push_back(br);
}