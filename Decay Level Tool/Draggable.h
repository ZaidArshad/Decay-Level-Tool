#pragma once
#include <SFML/Graphics.hpp>
#include "Bound.h"
#include "Canvas.h"

using namespace sf;
using namespace std;

// Sub classes of this type can be clicked and dragged
class Draggable {
public:
	//------Child-Class-Types------//
	const static int PLAYER = 0;
	const static int PLATFORM = 1;
	const static int RESIZER = 2;
	const static int SLIDER = 3;

	//------Getters------//
	Canvas* getCanvas();
	Bound getClickableBound();

	//------Setters------//
	void setPosition(Vector2f position);

	//------Functions------//
	void draw(RenderWindow& window);
	void draggable(RenderWindow& window);

protected:
	int type;
	float* xPos;
	float* yPos;
	float* width;
	float* height;
	Draggable* self;
	Canvas* canvas;
	Drawable* drawable;
	Transformable* transformable;
	bool isClicked;
	bool isHovered;
	Bound canvasBound;
	Bound clickableBound;

	void alloc();
	void updateCanvasBound();
	void updateClickableBound();
	void isDrawableClicked(Vector2i position);
};

