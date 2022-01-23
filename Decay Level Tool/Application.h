#pragma once
#include <iostream>
#include "Button.h"
#include "Canvas.h"
#include "Draggable.h"
#include "Platform.h"
#include "Slider.h"

using namespace sf;
using namespace std;

class Application {
public:
	const static int WIDTH = 1360;
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
	const static int BUTTON_AREA_HEIGHT = 100;
	const Color SIDE_BACKGROUND_COLOR = Color(150, 150, 150);
	const static int BUTTON_SIZE = 70;
	const static int HALF_BUTTON_SIZE = BUTTON_SIZE/2;
	const static int BUTTON_MARGIN = 10;

	const static int PROP_HEIGHT = HEIGHT - BUTTON_AREA_HEIGHT - 3*LEVEL_MARGIN;
	const static int PROP_TITLE_SIZE = 50;

	Application();
	~Application();
	Canvas* getLevelArea();

	void draw(RenderWindow& window);
	void addPlatform(Platform* platforn);
	void removePlatform(Platform* platforn);
	void movePlatformForward(Platform* platform);
	void movePlatformBack(Platform* platform);

	vector<Platform*> platforms;

private:
	RectangleShape background;

	Canvas* levelArea;
	vector<RectangleShape*> guideLines;

	Canvas* buttonsArea;
	vector<Button*> buttons;

	Canvas* propArea;
	Slider* slider;

	void setGuideLines();
	void drawLevelArea(RenderWindow& window);

	void drawButtonsArea(RenderWindow& window);
	void generateButtons();

	void drawPropertiesArea(RenderWindow& window);
	void generateProperties();
};

