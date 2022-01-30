#include "Canvas.h"

Canvas::Canvas(int w, int h, float x, float y, Color bg) {
	width = w;
	height = h;
	xPos = x;
	yPos = y;
	backgroundColor = bg;
	clickedDraggable = nullptr;

	background.setSize(Vector2f(width, height));
	background.setFillColor(backgroundColor);
	background.setPosition(xPos, yPos);
	bound = Bound(yPos, xPos, width+xPos, height+yPos);
}

Canvas::~Canvas() {

}

Vector2f Canvas::getCenterPosition() {
	float x = (width / 2) + xPos;
	float y = (height / 2) + yPos;
	return Vector2f(x, y);
}

RectangleShape Canvas::getBackground() { return background; }
Bound Canvas::getBound() { return bound; }

void Canvas::setClickedDraggable(Draggable* draggable) { clickedDraggable = draggable; }
Draggable* Canvas::getClickedDraggable() { return clickedDraggable; }

void Canvas::setLastClicked(Draggable* draggable) { lastClicked = draggable; }
Draggable* Canvas::getLastClicked() { return lastClicked; }
