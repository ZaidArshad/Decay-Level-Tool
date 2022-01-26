#pragma once
#include <SFML/Graphics.hpp>
#include "Bound.h"
#include "Canvas.h"

using namespace sf;
using namespace std;

class Draggable {
public:
	const static int PLAYER = 0;
	const static int PLATFORM = 1;
	const static int RESIZER = 2;
	const static int SLIDER = 3;

	void draw(RenderWindow& window);
	void draggable(RenderWindow& window);
	void setPosition(Vector2f position);
	Canvas* getCanvas();
	Bound getClickableBound();

protected:
	int type;
	Draggable* self;
	Canvas* canvas;
	Drawable* drawable;
	Transformable* transformable;
	float* xPos;
	float* yPos;
	float* width;
	float* height;
	bool isClicked;
	bool isHovered;
	Bound canvasBound;
	Bound clickableBound;

	void alloc();
	void setCanvasBound();
	void setClickableBound();
	void isDrawableClicked(Vector2i position);
};

