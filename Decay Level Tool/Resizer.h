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

	Resizer(Canvas* c, Platform* p, float x, float y);
	void setPos(float x, float y);
	void resize(RenderWindow& window);
	bool getClicked();

private:
	Platform* parent;
	RectangleShape rectangleShape;
	Color COLOR = Color(255, 0, 0);
};

