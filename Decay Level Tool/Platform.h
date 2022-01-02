#pragma once
#include <SFML/Graphics.hpp>
#include "Bound.h"
#include "Canvas.h"
#include "Draggable.h"

class Platform : public Draggable {
public:
	Platform(Canvas* c, int h);
	virtual void draw(RenderWindow& window);

private:
	RectangleShape rectangleShape;
	int health;
	Color healthIndex[8] = {
		Color::White,
		Color::Red,
		Color(255, 128, 0),
		Color::Yellow,
		Color::Green,
		Color::Blue,
		Color(75,0,130),
		Color(148,0,211) };

	void setClicked(RenderWindow& window);
};

