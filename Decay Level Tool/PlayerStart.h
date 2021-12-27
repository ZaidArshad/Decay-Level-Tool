#pragma once
#include <SFML/Graphics.hpp>
#include "Bound.h"
#include "Canvas.h"

using namespace sf;
using namespace std;

class PlayerStart {
public:
	PlayerStart(Canvas* c);
	void draw(RenderWindow& window);

private:
	Canvas* canvas;
	Texture playerTexture;
	Sprite playerSprite;
	float xPos;
	float yPos;
	float width;
	float height;
	bool isClicked;
	Bound canvasBound;
	Bound canBound;

	void setCanvasBound();
	void setCanBound();
	void isCanClicked(Vector2i position);
	void draggable(RenderWindow& window);
	void setPosition(Vector2f position);

};

