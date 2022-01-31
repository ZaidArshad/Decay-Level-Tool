#pragma once
#include <iostream>
#include <fstream>
#include "Button.h"
#include "Canvas.h"
#include "Draggable.h"
#include "Platform.h"
#include "Slider.h"
#include "EditText.h"
#include "PlayerStart.h"

using namespace sf;
using namespace std;

// Controls I/O and hold all the properties during runtime
class Application {
public:
	//------Window-Constants------//
	const static int WIDTH = 1360;
	const static int HEIGHT = 820;
	const static int MARGIN = 25;
	const Color BACKGROUND_COLOR = Color(100, 100, 100);

	//------Level-Area-Constants------//
	const static int LEVEL_WIDTH = 1001;
	const static int LEVEL_HEIGHT = 801;
	const static int LEVEL_MARGIN = 10;
	const static int LEVEL_GUIDELINE_WIDTH = 1;
	const Color LEVEL_BACKGROUND_COLOR = Color(0, 0, 0);
	const Color LEVEL_GUIDELINE_COLOR = Color(255, 255, 255, 100);

	//------Side-Area-Constants------//
	const static int SIDE_WIDTH = WIDTH - LEVEL_WIDTH - (3*LEVEL_MARGIN);
	const static int BUTTON_AREA_HEIGHT = 100;
	const Color SIDE_BACKGROUND_COLOR = Color(150, 150, 150);
	const static int BUTTON_SIZE = 70;
	const static int HALF_BUTTON_SIZE = BUTTON_SIZE/2;
	const static int BUTTON_MARGIN = 10;

	//------Properties-Area-Constants------//
	const static int PROP_HEIGHT = HEIGHT - BUTTON_AREA_HEIGHT - 3*LEVEL_MARGIN;
	const static int PROP_TITLE_SIZE = 40;
	const Color PROP_TITLE_COLOR = Color::White;

	// File that opens up with level details
	const char* EXPORT_FILE = "Generated_Level.txt";

	//------Constructors------//
	Application(RenderWindow* window);
	~Application();

	//------Getters------//
	Canvas* getLevelArea();
	RenderWindow* getWindow();

	//------Functions------//
	void draw();
	void addPlatform(Platform* platforn);
	void removePlatform(Platform* platforn);
	void movePlatformForward(Platform* platform);
	void movePlatformBack(Platform* platform);
	void exportLevel();

private:
	RenderWindow* window;
	RectangleShape background;

	// Draggable objects
	PlayerStart* playerStart;
	vector<Platform*> platforms;

	Canvas* levelArea;
	vector<RectangleShape*> guideLines;

	Canvas* buttonsArea;
	vector<Button<Application>*> buttons;
	Button<Application>* exportBtn;

	Canvas* propArea;
	Slider* slider;
	vector<EditText*> editTexts;

	bool isExporting = false;

	void setGuideLines();
	void drawLevelArea();

	void drawButtonsArea();
	void generateButtons();

	void drawPropertiesArea();
	void generateProperties();
};

