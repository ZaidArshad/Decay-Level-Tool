#include "Resizer.h"


Resizer::Resizer(Canvas* c, Platform* p, int t, float x, float y) {
	type = t;
	self = p;
	parent = p;
	canvas = c;
	width = SIZE;
	height = SIZE;
	rectangleShape.setSize(Vector2f(width, height));
	rectangleShape.setOrigin(width / 2, height/ 2);
	rectangleShape.setFillColor(COLOR);

	drawable = &rectangleShape;
	transformable = &rectangleShape;

	xPos = x;
	yPos = y;
	isClicked = false;
	canvasBound = c->getBound();
	setClickableBound();

	rectangleShape.setPosition(xPos, yPos);
}

void Resizer::setPos(float x, float y) {
	Vector2f offset = rectangleShape.getOrigin();
	isHeld = false;
	x = x - (SIZE - offset.x);
	y = y - (SIZE - offset.y);
	setPosition(Vector2f(x, y));
}

void Resizer::resize(RenderWindow &window) {
	Vector2i mousePos = Mouse::getPosition(window);
	int mouseX = mousePos.x;
	int mouseY = mousePos.y;

	Vector2f platOrigin = parent->getOrigin();
	int platW = parent->getWidth();
	int platH = parent->getHeight();
	float platX = parent->getX();
	float platY = parent->getY();

	Vector2f offset = rectangleShape.getOrigin();

	// Left 
	//platW = platW + (platX - mouseX - offset);
	if (type == TOP_LEFT) {
		parent->setOrigin(Vector2f(0, 0));
		if (isHeld) {
			platW = platW + (platX - (mouseX + SIZE - offset.x));
			platH = platH + (platY - (mouseY + SIZE - offset.y));
		}
		platX = mouseX + (SIZE - offset.x);
		platY = mouseY + (SIZE - offset.y);
		isHeld = true;
	}
	else if (type == TOP_RIGHT) {
		// platW = (mouseX - offset.x) - platX;
		// platX = mouseX - (offset.x);
		// platY = mouseY + (SIZE - offset.y);
	}


	//cout << "X: " << mouseX << endl;
	//cout << "W: " << platW << " H: " << platH << " X: " << platX << " Y: " << platY << endl;

	parent->setWidth(platW);
	parent->setHeight(platH);
	parent->setPosition(Vector2f(platX, platY));
}

bool Resizer::getClicked() { return isClicked; }