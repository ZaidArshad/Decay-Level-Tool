#include "Resizer.h"


Resizer::Resizer(Canvas* c, Platform* p, int yT, int xT, float x, float y) {
	type = RESIZER;
	canvas = c;
	self = p;
	parent = p;
	yType = yT;
	xType = xT;
	alloc();
	*width = SIZE;
	*height = SIZE;
	rectangleShape.setSize(Vector2f(*width, *height));
	rectangleShape.setOrigin(*width / 2, *height/ 2);
	rectangleShape.setFillColor(COLOR);

	drawable = &rectangleShape;
	transformable = &rectangleShape;

	*xPos = x;
	*yPos = y;
	isClicked = false;
	canvasBound = c->getBound();
	updateClickableBound();

	rectangleShape.setPosition(*xPos, *yPos);
}

Resizer::~Resizer() {
	delete xPos;
	delete yPos;
	delete width;
	delete height;
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

	if (x < canvasBound.getLeft() - SIZE) x = canvasBound.getLeft() - (SIZE - originX);
	else if (x > canvasBound.getRight() + SIZE) x = canvasBound.getRight();

	if (y < canvasBound.getTop() - SIZE) y = canvasBound.getTop() - (SIZE - originY);
	else if (y > canvasBound.getBot() + SIZE) y = canvasBound.getBot();

	if (yType == TOP) {
		if (y + (SIZE - originY) > parent->getClickableBound().getTop())
			y = parent->getClickableBound().getTop() - (SIZE - originY);
	}
	else if (yType == BOT) {
		if (y - originY < parent->getClickableBound().getBot())
			y = parent->getClickableBound().getBot() + originY;
	}

	if (xType == LEFT) {
		if (x + (SIZE - originX) > parent->getClickableBound().getLeft())
			x = parent->getClickableBound().getLeft() - (SIZE - originX);
	}
	else if (xType == RIGHT) {
		if (x - originX < parent->getClickableBound().getRight())
			x = parent->getClickableBound().getRight() + originX;
	}

	*xPos = x;
	*yPos = y;
	transformable->setPosition(x, y);
}

void Resizer::setPos(float x, float y) {
	Vector2f offset = rectangleShape.getOrigin();
	isHeld = false;
	x = x - (SIZE - offset.x);
	y = y - (SIZE - offset.y);
	setPosition(Vector2f(x, y));
}

Vector2i Resizer::constrainMousePosition(RenderWindow& window, Canvas* canvas) {
	Vector2i mousePos = Mouse::getPosition(window);
	int mouseX = mousePos.x;
	int mouseY = mousePos.y;
	float originX = transformable->getOrigin().x;
	float originY = transformable->getOrigin().y;
	Bound bound = canvas->getBound();

	if (mouseX < bound.getLeft() - SIZE) {
		mouseX = bound.getLeft() - SIZE + originX;
	}
	else if (bound.getRight() + SIZE < mouseX) {
		mouseX = bound.getRight() + originX;
	}

	if (mouseY < bound.getTop() - SIZE) {
		mouseY = bound.getTop() - SIZE + originY;
	}
	else if (bound.getBot() + SIZE < mouseY) {
		mouseY = bound.getBot() + originY;
	}
	return Vector2i(mouseX, mouseY);
}

void Resizer::resize(RenderWindow &window) {
	Vector2i mousePos = constrainMousePosition(window, parent->getCanvas());
	int mouseX = mousePos.x;
	int mouseY = mousePos.y;

	int platW = parent->getWidth();
	int platH = parent->getHeight();
	float platX = parent->getX();
	float platY = parent->getY();

	Vector2f offset = rectangleShape.getOrigin();
	parent->setOrigin(Vector2f(0, 0));

	/*rect.setPosition(platX, platY);
	rect.setSize(Vector2f(10, 10));
	rect.setOrigin(width / 2, height / 2);
	rect.setFillColor(COLOR);
	window.draw(rect);*/

	if (yType == TOP) {
		platH = platH + (platY - (mouseY + SIZE - offset.y));
		if (platH > Platform::MIN_HEIGHT) {
			platY = mouseY + (SIZE - offset.y);
		}
	}
	else if (yType == BOT) {
		platH = mouseY - platY - offset.y;	
	}
	
	if (xType == LEFT) {
		platW = platW + (platX - (mouseX + SIZE - offset.x));
		if (platW > Platform::MIN_WIDTH) {
			platX = mouseX + (SIZE - offset.x);
		}
	}
	else if (xType == RIGHT) {
		platW = mouseX - platX - offset.x;
	}

	//cout << "X: " << mouseX << endl;
	//cout << "W: " << platW << " H: " << platH << " X: " << platX << " Y: " << platY << endl;
	parent->setPosition(Vector2f(platX, platY));
	parent->setWidth(platW);
	parent->setHeight(platH);
}

bool Resizer::getClicked() { return isClicked; }