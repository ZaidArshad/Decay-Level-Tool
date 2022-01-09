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
	const static int WIDTH = 1400;
	const static int HEIGHT = 820;
	const static int MARGIN = 25;
	const Color BACKGROUND_COLOR = Color(100, 100, 100);

	const static int LEVEL_WIDTH = 1001;
	const static int LEVEL_HEIGHT = 801;
	const static int LEVEL_MARGIN = 10;
	const static int LEVEL_GUIDELINE_WIDTH = 1;
	const Color LEVEL_BACKGROUND_COLOR = Color(0, 0, 0);
	const Color LEVEL_GUIDELINE_COLOR = Color(255, 255, 255, 100);

	const static int SIDE_WIDTH = WIDTH - LEVEL_WIDTH - (3*LEVEL_MARGIN);
	const Color SIDE_BACKGROUND_COLOR = Color(150, 150, 150);

	const static int BUTTONS_HEIGHT = 100;
	const static int BUTTON_SIZE = 100;

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

