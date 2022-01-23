#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;

class Bound {
public:
	Bound(float t, float l, float r, float b);
	Bound();
	float getTop();
	float getLeft();
	float getRight();
	float getBot();
	bool contains(Vector2i position);

private:
	float top;
	float left;
	float right;
	float bot;
};

