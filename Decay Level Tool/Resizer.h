#pragma once
#include <SFML/Graphics.hpp>
#include "Bound.h"
#include "Canvas.h"
#include "Draggable.h"
#include "Platform.h"

using namespace sf;
using namespace std;

class Resizer : public Draggable {
public:
	static const int SIZE = 5;
	static const int TOP = 0;
	static const int BOT = 1;
	static const int LEFT = 0;
	static const int RIGHT = 1;

	Resizer(Canvas* c, Platform* p, int yT, int xT, float x, float y);
	void draggable(RenderWindow& window);
	void setPosition(Vector2f position);
	void setPos(float x, float y);
	void resize(RenderWindow& window);
	bool getClicked();

private:
	int yType;
	int xType;
	Platform* parent;
	RectangleShape rectangleShape;
	bool min = false;
	bool isHeld = false;
	Color COLOR = Color(255, 0, 0);
};

