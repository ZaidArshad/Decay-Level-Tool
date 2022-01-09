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
	static const int TOP_LEFT = 0;
	static const int TOP_RIGHT = 1;
	static const int BOT_LEFT = 2;
	static const int BOT_RIGHT = 3;

	Resizer(Canvas* c, Platform* p, int t, float x, float y);
	void draggable(RenderWindow& window);
	void setPosition(Vector2f position);
	void setPos(float x, float y);
	void resize(RenderWindow& window);
	bool getClicked();

private:
	int type;
	Platform* parent;
	RectangleShape rectangleShape;
	bool min = false;
	bool isHeld = false;
	Color COLOR = Color(255, 0, 0);
};

