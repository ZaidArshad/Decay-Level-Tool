#pragma once
class Bound {
public:
	Bound(float x, float y, float width, float height);
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

