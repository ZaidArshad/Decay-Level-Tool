#include "Draggable.h"
#include "PlayerStart.h"
#include <iostream>

void Draggable::draw(RenderWindow& window) {
	draggable(window);
	window.draw(*drawable);
}

void Draggable::setCanvasBound() {
	Bound b = canvas->getBound();
	float top = b.getTop() + transformable->getOrigin().y;
	float left = b.getLeft() + transformable->getOrigin().x;
	float right = b.getRight() - width + transformable->getOrigin().x;
	float bot = b.getBot() - height + transformable->getOrigin().y;
	canvasBound = Bound(top, left, right, bot);
}

void Draggable::setClickableBound() {
	float top = yPos - transformable->getOrigin().y;
	float left = xPos - transformable->getOrigin().x;
	float right = xPos + width - transformable->getOrigin().x;
	float bot = yPos + height - transformable->getOrigin().y;
	clickableBound = Bound(top, left, right, bot);
}


void Draggable::isDrawableClicked(Vector2i position) {
	bool pressed = Mouse::isButtonPressed(Mouse::Left);
	Draggable* clickedDraggable = canvas->getClickedDraggable();

	if (pressed) {
		if (position.x > clickableBound.getLeft() &&
			position.x < clickableBound.getRight() &&
			position.y > clickableBound.getTop() &&
			position.y < clickableBound.getBot()) {

			if (clickedDraggable == nullptr) {
				if (!isClicked) {
					transformable->setOrigin(
						position.x - clickableBound.getLeft(),
						position.y - clickableBound.getTop());
				}
				clickedDraggable = this;
				isClicked = true;
			}
		}
	}
	else {
		if (clickedDraggable == this) clickedDraggable = nullptr;
		isClicked = false;
	}

	canvas->setClickedDraggable(clickedDraggable);
	setCanvasBound();
	setClickableBound();

}

void Draggable::draggable(RenderWindow& window) {
	Vector2i position = Mouse::getPosition(window);
	isDrawableClicked(position);
	if (isClicked) {
		setPosition(Vector2f(position.x, position.y));
	}
}

void Draggable::setPosition(Vector2f position) {
	float x = position.x;
	float y = position.y;

	float originX = transformable->getOrigin().x;
	float originY = transformable->getOrigin().y;


	if (x < canvasBound.getLeft()) x = canvasBound.getLeft();
	else if (x > canvasBound.getRight()) x = canvasBound.getRight();

	if (y < canvasBound.getTop()) y = canvasBound.getTop();
	else if (y > canvasBound.getBot()) y = canvasBound.getBot();


	xPos = x;
	yPos = y;
	transformable->setPosition(x, y);
}