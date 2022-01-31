#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Bound.h"
#include <iostream>

using namespace std;

class Draggable;

using namespace sf;
using namespace std;

// Hold other interactable objects bounded by this object
class Canvas {
public:
	//------Constructors------//
	Canvas(int w, int h, float x, float y, Color bg);
	~Canvas();

	//------Getters------//
	Vector2f getCenterPosition();
	RectangleShape getBackground();
	Bound getBound();
	Draggable* getClickedDraggable();
	Draggable* getLastClicked();

	//------Setters------//
	void setClickedDraggable(Draggable* draggable);
	void setLastClicked(Draggable* draggable);

private:
	int width;
	int height;
	float xPos;
	float yPos;

	Bound bound;
	Color backgroundColor;
	RectangleShape background;
	Draggable* clickedDraggable;
	Draggable* lastClicked;
};

