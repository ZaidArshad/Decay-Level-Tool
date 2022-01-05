#pragma once
#include <SFML/Graphics.hpp>
#include "Bound.h"
#include "Canvas.h"

using namespace sf;
using namespace std;

class Draggable {
public:
	void draw(RenderWindow& window);
	void draggable(RenderWindow& window);

protected:
	Draggable* self;
	Canvas* canvas;
	Drawable* drawable;
	Transformable* transformable;
	float xPos;
	float yPos;
	float width;
	float height;
	bool isClicked;
	Bound canvasBound;
	Bound clickableBound;

	void setCanvasBound();
	void setClickableBound();
	void isDrawableClicked(Vector2i position);
	void setPosition(Vector2f position);
};

