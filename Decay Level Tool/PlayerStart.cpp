#include "PlayerStart.h"
#include <iostream>

PlayerStart::PlayerStart(Canvas* c) {
	if (!playerTexture.loadFromFile("images/can.png")) {
		std::cout << "Load failed\n";
		system("pause");
	}
	canvas = c;
	width = playerTexture.getSize().x;
	height = playerTexture.getSize().y;
	playerSprite.setTexture(playerTexture);
	playerSprite.setOrigin(width / 2, height / 2);

	Vector2f position = c->getCenterPosition();
	xPos = position.x;
	yPos = position.y;
	isClicked = false;
	canvasBound = c->getBound();
	setCanBound();

	playerSprite.setPosition(position.x, position.y);
}

void PlayerStart::draw(RenderWindow& window) {
	draggable(window);
	window.draw(playerSprite);
}

void PlayerStart::setCanvasBound() {
	Bound b = canvas->getBound();
	float top = b.getTop() + playerSprite.getOrigin().y;
	float left = b.getLeft() + playerSprite.getOrigin().x;
	float right = b.getRight() - width + playerSprite.getOrigin().x;
	float bot = b.getBot() - height + playerSprite.getOrigin().y;
	canvasBound = Bound(top, left, right, bot);
}

void PlayerStart::setCanBound() {
	float top = yPos - playerSprite.getOrigin().y;
	float left = xPos - playerSprite.getOrigin().x;
	float right = xPos + width - playerSprite.getOrigin().x;
	float bot = yPos + height - playerSprite.getOrigin().y;
	canBound = Bound(top, left, right, bot);
}


void PlayerStart::isCanClicked(Vector2i position) {
	bool pressed = Mouse::isButtonPressed(Mouse::Left);
	if (pressed) {
		if (position.x > canBound.getLeft() &&
			position.x < canBound.getRight() &&
			position.y > canBound.getTop() &&
			position.y < canBound.getBot()) {
			if (!isClicked) {
				playerSprite.setOrigin(
					position.x - canBound.getLeft(), position.y - canBound.getTop());
			}
			isClicked = true;
		}
	}
	else {
		isClicked = false;
	}
	setCanvasBound();
	setCanBound();
	
}

void PlayerStart::draggable(RenderWindow& window) {
	Vector2i position = Mouse::getPosition(window);
	isCanClicked(position);
	if (isClicked) {
		setPosition(Vector2f(position.x, position.y));
	}
}

void PlayerStart::setPosition(Vector2f position) {
	float x = position.x;
	float y = position.y;

	float originX = playerSprite.getOrigin().x;
	float originY = playerSprite.getOrigin().y;


	if (x < canvasBound.getLeft()) x = canvasBound.getLeft() ;
	else if (x > canvasBound.getRight()) x = canvasBound.getRight();

	if (y < canvasBound.getTop()) y = canvasBound.getTop();
	else if (y > canvasBound.getBot()) y = canvasBound.getBot();


	xPos = x;
	yPos = y;
	playerSprite.setPosition(x, y);
}