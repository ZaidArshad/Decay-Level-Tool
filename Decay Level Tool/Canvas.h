#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Bound.h"
#include <iostream>

using namespace std;

class Draggable;

using namespace sf;
using namespace std;

class Canvas {
public:
	int width;
	int height;
	float xPos;
	float yPos;
	Color backgroundColor;

	Canvas(int w, int h, float x, float y, Color bg);
	Vector2f getCenterPosition();
	RectangleShape getBackground();
	Bound getBound();
	Draggable* getClickedDraggable();
	void setClickedDraggable(Draggable* draggable);

private:
	RectangleShape background;
	Bound bound;
	Draggable* clickedDraggable;
};

