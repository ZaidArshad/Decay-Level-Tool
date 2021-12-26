#pragma once
#include "Canvas.h"
using namespace sf;
using namespace std;

class Application {
private:
	Canvas* canvas;
	RectangleShape background;

	void drawCanvas(RenderWindow& window);
public:
	int WIDTH = 1400;
	int HEIGHT = 820;
	int MARGIN = 25;
	Color BACKGROUND_COLOR = Color(100, 100, 100);

	Application();
	~Application();
	void drawApplication(RenderWindow& window);
};

