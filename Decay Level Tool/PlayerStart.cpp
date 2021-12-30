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

	drawable = &playerSprite;
	transformable = &playerSprite;

	Vector2f position = c->getCenterPosition();
	xPos = position.x;
	yPos = position.y;
	isClicked = false;
	canvasBound = c->getBound();
	setClickableBound();

	playerSprite.setPosition(position.x, position.y);
}