#pragma once
#include"SFML\System.hpp"
#include"SFML\Graphics.hpp"
#include <iostream>

class Application;

using namespace std;
using namespace sf;

class Button {
public:
	//------Constructors------//
	Button(float x, float y, string fileName, void(*onClick)(Application*));

	// Draws the entire button the screen
	void draw(RenderWindow& window);

	// Allows the mouse to interact with the button (highlights and when clicked return true)
	bool mouseInteract(RenderWindow& window, Application* application);

private:
	float xPos;
	float yPos;
	float width;
	float height;
	bool isClicked = false;
	void (*onClickFunction)(Application*);

	Texture buttonTexture;
	Sprite buttonSprite;
	RectangleShape border;
	RectangleShape inside;
};

