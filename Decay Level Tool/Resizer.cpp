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

void Resizer::draggable(RenderWindow& window) {
	Vector2i position = Mouse::getPosition(window);
	isDrawableClicked(position);
	if (isClicked) {
		setPosition(Vector2f(position.x, position.y));
	}
}

void Resizer::setPosition(Vector2f position) {
	float x = position.x;
	float y = position.y;

	float originX = transformable->getOrigin().x;
	float originY = transformable->getOrigin().y;


	if (x < canvasBound.getLeft() - SIZE) x = canvasBound.getLeft();
	else if (x > canvasBound.getRight() + SIZE) x = canvasBound.getRight();

	if (y < canvasBound.getTop() - SIZE) y = canvasBound.getTop();
	else if (y > canvasBound.getBot() + SIZE) y = canvasBound.getBot();

	if (type == TOP_LEFT) {
		if (x + (SIZE - originX) > parent->getClickableBound().getLeft())
			x = parent->getClickableBound().getLeft() - (SIZE - originX);
		if (y + (SIZE - originY) > parent->getClickableBound().getTop())
			y = parent->getClickableBound().getTop() - (SIZE - originY);
	}

	xPos = x;
	yPos = y;
	transformable->setPosition(x, y);
}

void Resizer::setPos(float x, float y) {
	Vector2f offset = rectangleShape.getOrigin();
	isHeld = false;
	x = x - (SIZE - offset.x);
	y = y - (SIZE - offset.y);
	setPosition(Vector2f(x, y));
}

Vector2i constrainMousePosition(RenderWindow& window, Canvas* canvas) {
	Vector2i mousePos = Mouse::getPosition(window);
	int mouseX = mousePos.x;
	int mouseY = mousePos.y;
	Bound bound = canvas->getBound();

	if (mouseX < bound.getLeft()) {
		mouseX = bound.getLeft();
	}
	else if (bound.getRight() < mouseX) {
		mouseX = bound.getRight();
	}

	if (mouseY < bound.getTop()) {
		mouseY = bound.getTop();
	}
	else if (bound.getBot() < mouseY) {
		mouseY = bound.getBot();
	}
	return Vector2i(mouseX, mouseY);
}

void Resizer::resize(RenderWindow &window) {
	Vector2i mousePos = constrainMousePosition(window, parent->getCanvas());
	int mouseX = mousePos.x;
	int mouseY = mousePos.y;

	Vector2f platOrigin = parent->getOrigin();
	int platW = parent->getWidth();
	int platH = parent->getHeight();
	float platX = parent->getX();
	float platY = parent->getY();

	Vector2f offset = rectangleShape.getOrigin();

	// Left 
	if (type == TOP_LEFT) {
		parent->setOrigin(Vector2f(0, 0));
		if (isHeld) {
			platW = platW + (platX - (mouseX + SIZE - offset.x));
			platH = platH + (platY - (mouseY + SIZE - offset.y));
		}
		if (platW > Platform::MIN_WIDTH) {
			platX = mouseX + (SIZE - offset.x);
		}
		if (platH > Platform::MIN_HEIGHT) {
			platY = mouseY + (SIZE - offset.y);
		}
		isHeld = true;
	}
	else if (type == TOP_RIGHT) {
		// platW = (mouseX - offset.x) - platX;
		// platX = mouseX - (offset.x);
		// platY = mouseY + (SIZE - offset.y);
	}

	//cout << "X: " << mouseX << endl;
	//cout << "W: " << platW << " H: " << platH << " X: " << platX << " Y: " << platY << endl;
	parent->setPosition(Vector2f(platX, platY));
	parent->setWidth(platW);
	parent->setHeight(platH);
}

bool Resizer::getClicked() { return isClicked; }