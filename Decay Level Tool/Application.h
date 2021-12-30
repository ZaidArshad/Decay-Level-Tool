#pragma once
#include "Canvas.h"

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

	Application();
	~Application();
	Canvas* getCanvas();
	void draw(RenderWindow& window);

private:
	Canvas* levelArea;
	vector<RectangleShape*> guideLines;


	RectangleShape background;

	void setGuideLines();
	void drawLevelArea(RenderWindow& window);
};

