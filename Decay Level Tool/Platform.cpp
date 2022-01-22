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
	if (isShowingResizers) {
		updateResizers(window);
		for (Resizer* resizer : resizers) {
			resizer->draggable(window);
			resizer->draw(window);
		}
	}
	window.draw(*drawable);

	if (canvas->getLastClicked() == this) {
		setClicked(window);
	}
	else {
		isShowingResizers = false;
	}
}

void Platform::setWidth(int w) {
	float x = xPos - rectangleShape.getOrigin().x;
	if (x + w > canvas->getBound().getRight()) {
		w = canvas->getBound().getRight() - x;
	}
	else if (w < MIN_WIDTH) {
		w = MIN_WIDTH;
	}
	width = w;
	rectangleShape.setSize(Vector2f(width, height));
}

void Platform::setHeight(int h) {
	float y = yPos - rectangleShape.getOrigin().y;
	if (y + h > canvas->getBound().getBot()) {
		h = canvas->getBound().getBot() - y;
	}
	else if (h < MIN_HEIGHT) {
		h = MIN_HEIGHT;
	}
	height = h;
	rectangleShape.setSize(Vector2f(width, height));
}

int Platform::getWidth() { return rectangleShape.getSize().x; }
int Platform::getHeight() { return rectangleShape.getSize().y; }

int Platform::getHealth() { return health; }

float Platform::getX() { return rectangleShape.getPosition().x - rectangleShape.getOrigin().x; }
float Platform::getY() { return rectangleShape.getPosition().y - rectangleShape.getOrigin().y; }

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

	Resizer* tl = new Resizer(canvas, this, Resizer::TOP, Resizer::LEFT,
		clickableBound.getLeft() - offset, clickableBound.getTop() - offset);
	Resizer* tr = new Resizer(canvas, this, Resizer::TOP, Resizer::RIGHT,
		clickableBound.getRight() + offset, clickableBound.getTop() - offset);
	Resizer* bl = new Resizer(canvas, this, Resizer::BOT, Resizer::LEFT,
		clickableBound.getLeft() - offset, clickableBound.getBot() + offset);
	Resizer* br = new Resizer(canvas, this, Resizer::BOT, Resizer::RIGHT,
		clickableBound.getRight() + offset, clickableBound.getBot() + offset);

	resizers.push_back(tl);
	resizers.push_back(tr);
	resizers.push_back(bl);
	resizers.push_back(br);
}