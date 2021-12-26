#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Bound.h"
using namespace sf;
using namespace std;

class Canvas {
public:
	int WIDTH = 1001;
	int HEIGHT = 801;
	int MARGIN = 10;
	int GUIDELINE_WIDTH = 1;
	Color BACKGROUND_COLOR = Color(0, 0, 0);
	Color GUIDELINE_COLOR = Color(255, 255, 255, 120);

	Canvas();
	~Canvas();
	Vector2f getCenterPosition();
	RectangleShape getBackground();
	vector<RectangleShape*> getGuideLines();
	Bound getBound();

private:
	RectangleShape background;
	vector<RectangleShape*> guideLines;
	Bound bound;

	void setGuideLines();
};

