#pragma once
#include <SFML/Graphics.hpp>
#include "Prompt.h"
#include "Platform.h"

using namespace sf;
using namespace std;

class EditText {
public:
	EditText(float x, float y, float w, string font, string t, int fSize);
	void draw(RenderWindow &window, int v);
	Bound getBound();

	const Color TEXT_COLOR = Color::White;
	const Color BACKGROUND_COLOR = Color(100, 100, 100);
	const int MARGIN = 5;

private:
	float xPos;
	float yPos;
	float width;
	Bound bound;

	RectangleShape test;

	Prompt* title;
	Prompt* edit;
	RectangleShape editBackground;
	Platform* platform = nullptr;
	int value;
};

