#pragma once
#include <iostream>
#include "Button.h"
#include "Canvas.h"
#include "Draggable.h"
#include "Platform.h"

using namespace sf;
using namespace std;

class Application {
public:
	int WIDTH = 1400;
	int HEIGHT = 820;
	int MARGIN = 25;
	Color BACKGROUND_COLOR = Color(100, 100, 100);

	int LEVEL_WIDTH = 1001;
	int LEVEL_HEIGHT = 801;
	int LEVEL_MARGIN = 10;
	int LEVEL_GUIDELINE_WIDTH = 1;
	Color LEVEL_BACKGROUND_COLOR = Color(0, 0, 0);
	Color LEVEL_GUIDELINE_COLOR = Color(255, 255, 255, 100);

	int SIDE_WIDTH = WIDTH - LEVEL_WIDTH - (3*LEVEL_MARGIN);
	Color SIDE_BACKGROUND_COLOR = Color(150, 150, 150);

	int BUTTONS_HEIGHT = 100;
	int BUTTON_SIZE = 100;

	Application();
	~Application();
	Canvas* getLevelArea();

	void draw(RenderWindow& window, vector<Platform*> platforms);

private:
	RectangleShape background;

	Canvas* levelArea;
	vector<RectangleShape*> guideLines;

	Canvas* buttonsArea;
	Button* button;

	void setGuideLines();
	void drawLevelArea(RenderWindow& window);

	void drawButtonsArea(RenderWindow& window);
};

