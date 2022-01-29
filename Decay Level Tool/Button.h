#pragma once
#include"SFML\System.hpp"
#include"SFML\Graphics.hpp"
#include <iostream>

class Application;

using namespace std;
using namespace sf;

template <class T>
class Button {
public:
	const int TXT_MARGIN = 50; //Space around text from button
	const int BORDER_WIDTH = 10; //Border width
	const int IMG_MARGIN = 10; //Space around text from button

	//------Constructors------//
	Button(float x, float y, string fileName, void(*onClick)(T*));
	Button(float x, float y, string title, string fontName, void(*onClick)(T*));
	// Draws the entire button the screen
	void draw(RenderWindow& window);

	// Allows the mouse to interact with the button (highlights and when clicked return true)
	bool mouseInteract(RenderWindow& window, T* temp);

private:
	float xPos;
	float yPos;
	float width;
	float height;
	bool isClicked = false;
	bool isHovered = false;
	void (*onClickFunction)(T*);

	// Visual attributes
	string name;
	Text text;
	Font font;

	Texture buttonTexture;
	Sprite buttonSprite;
	RectangleShape border;
	RectangleShape inside;
	void createShape();
};

