#pragma once
#include"SFML\System.hpp"
#include"SFML\Graphics.hpp"
#include <iostream>
using namespace std;
using namespace sf;

class Prompt {
public:
	Prompt(float xPos, float yPos, string fontName, int fSize, string text, Color color);
	Text getText();
	Font getFont();
	void textColorShifter();
	void blink();
	Color getColor();
	void setColor(Color c);
	void setString(string words);
	void setPosition(float xPos, float yPos);

private:
	float xPosition;
	float yPosition;
	string textString;
	sf::Color textColor;
	int fontSize;
	sf::Text textObj;
	sf::Font font;
	int fontR = 0;
	int fontG = 0;
	int fontB = 255;
	int alpha = 255;
	int colorIncrementer = 1;
	int iterator = 0;

	Font loadFont(string fontFileName);
};

