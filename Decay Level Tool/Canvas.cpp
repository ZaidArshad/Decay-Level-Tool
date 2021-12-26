#include "Canvas.h"

Canvas::Canvas() {
	background.setSize(Vector2f(WIDTH, HEIGHT));
	background.setFillColor(BACKGROUND_COLOR);
	background.setPosition(MARGIN, MARGIN);
	setGuideLines();

	bound = Bound(MARGIN, MARGIN, WIDTH+MARGIN, HEIGHT+MARGIN);
}

Canvas::~Canvas() {
	guideLines.clear();
}

Vector2f Canvas::getCenterPosition() {
	float width = (WIDTH / 2) + MARGIN;
	float height = (HEIGHT / 2) + MARGIN;
	return Vector2f(width, height);
}

void Canvas::setGuideLines() {
	int rows = HEIGHT / 10;
	int cols = WIDTH / 10;

	RectangleShape* guideLine;
	for (int i = 0; i <= rows; i++) {
		guideLine = new RectangleShape();
		guideLine->setFillColor(GUIDELINE_COLOR);
		guideLine->setSize(Vector2f(WIDTH, GUIDELINE_WIDTH));
		guideLine->setPosition(10, i * 10 + 10);
		guideLines.push_back(guideLine);
	}
	for (int i = 0; i <= cols; i++) {
		guideLine = new RectangleShape();
		guideLine->setFillColor(GUIDELINE_COLOR);
		guideLine->setSize(Vector2f(GUIDELINE_WIDTH, HEIGHT));
		guideLine->setPosition(i * 10 + 10, 10);
		guideLines.push_back(guideLine);
	}
}

RectangleShape Canvas::getBackground() { return background; }
vector<RectangleShape*> Canvas::getGuideLines() { return guideLines; }
Bound Canvas::getBound() { return bound; }

