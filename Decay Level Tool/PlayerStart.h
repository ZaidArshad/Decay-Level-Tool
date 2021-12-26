#pragma once
#include <SFML/Graphics.hpp>
#include "Bound.h"
#include "Canvas.h"

using namespace sf;
using namespace std;

class PlayerStart {
public:
	PlayerStart(Canvas canvas);
	void draw(RenderWindow& window);

private:
	Texture playerTexture;
	Sprite playerSprite;
	float xPos;
	float yPos;
	float width;
	float height;
	bool isClicked;
	Bound canvasBound;
	Bound canBound;

	void setCanvasBound(Bound b);
	void setCanBound();
	void isCanClicked(Vector2i position);
	void draggable(RenderWindow& window);
	void setPosition(Vector2f position);

};

