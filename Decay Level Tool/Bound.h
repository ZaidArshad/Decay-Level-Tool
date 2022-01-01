#pragma once
class Bound {
public:
	Bound(float t, float l, float r, float b);
	Bound();
	float getTop();
	float getLeft();
	float getRight();
	float getBot();

private:
	float top;
	float left;
	float right;
	float bot;
};

