#pragma once
#include <SFML/Graphics.hpp>
#include "Bound.h"
#include "Canvas.h"
#include "Draggable.h"

class Resizer;

class Platform : public Draggable {
public:
	const static int MIN_WIDTH = 10;
	const static int MIN_HEIGHT = 10;

	Platform(Canvas* c, int h);
	~Platform();
	virtual void draw(RenderWindow& window);
	void update();

	void setWidth(int w);
	void setHeight(int h);
	void setHealth(int h);
	int getWidth();
	int getHeight();
	int getHealth();
	float getX();
	float getY();

	float* getWP();
	float* getHP();
	float* getXP();
	float* getYP();

	void setOrigin(Vector2f origin);
	Vector2f getOrigin();

private:
	RectangleShape rectangleShape;
	int health;

	bool isShowingResizers = false;
	vector<Resizer*> resizers;

	Color HEALTH_INDEX[8] = {
		Color::White,
		Color::Red,
		Color(255, 128, 0),
		Color::Yellow,
		Color::Green,
		Color::Blue,
		Color(75,0,130),
		Color(148,0,211) };

	void setClicked(RenderWindow& window);
	void generateResizers();
	void updateResizers(RenderWindow& window);
};

