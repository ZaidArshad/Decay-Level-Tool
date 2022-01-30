#pragma once
#include <SFML/Graphics.hpp>
#include "Prompt.h"
#include "Platform.h"
#include "Button.h"

using namespace sf;
using namespace std;

class EditText {
public:
	EditText(float x, float y, float w, string font,
		string t, int fSize, float mi, float ma);
	~EditText();

	void draw(RenderWindow &window, float *v, int d);
	Bound getBound();
	void add();
	void subtract();

	const Color TEXT_COLOR = Color::White;
	const Color BACKGROUND_COLOR = Color(100, 100, 100);
	const int MARGIN = 5;
	const int BUTTON_SIZE = 58;

private:
	float xPos;
	float yPos;
	float width;
	Bound bound;

	float max;
	float min;

	RectangleShape test;
	Prompt* title;
	Prompt* edit;

	Button<EditText>* plus;
	Button<EditText>* minus;
	RectangleShape editBackground;
	float* value;
};

