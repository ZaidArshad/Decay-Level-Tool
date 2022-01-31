#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;

// Holds the positions of each edge
class Bound {
public:
	//------Constructors------//
	Bound(float t, float l, float r, float b);
	Bound();

	//------Getters------//
	float getTop();
	float getLeft();
	float getRight();
	float getBot();
	Vector2f getCenter();

	//------Functions------//
	bool contains(Vector2i position);

private:
	float top;
	float left;
	float right;
	float bot;
};

