#pragma once
#include <SFML/Graphics.hpp>
#include "Bound.h"
#include "Canvas.h"
#include "Draggable.h"
#include "Platform.h"

using namespace sf;
using namespace std;

class Slider : public Draggable {
public:
	const static int MARKER_WIDTH = 10;
	const static int MARKER_HEIGHT = 30;
	const Color MARKER_COLOR = Color(255,0,0,150);
	const Color GUIDELINE_COLOR = Color(0, 0, 0, 150);
	const static int BAR_HEIGHT = 10;
	const Color BAR_COLOR = Color::White;

	Slider(float x, float y, float bW, int values);
	void drawSliderBar(RenderWindow& window, Platform* platform);

private:
	RectangleShape bar;
	RectangleShape marker;
	Platform* platform;
	int numOfValues;
	float barWidth;

	vector<RectangleShape*> guideLines;
	bool isSnappedToGuide = false;
	bool newPlat = true;

	void snapToGuide();
};

