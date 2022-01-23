#include "Slider.h"

Slider::Slider(float x, float y, float bW, int values) {
	self = this;

	canvas = new Canvas(
		bW, MARKER_HEIGHT, x, y, Color::Transparent);

	width = MARKER_WIDTH;
	height = MARKER_HEIGHT;
	marker.setSize(Vector2f(width, height));
	marker.setFillColor(MARKER_COLOR);
	drawable = &marker;
	transformable = &marker;
	xPos = x;
	yPos = y;
	isClicked = false;
	canvasBound = canvas->getBound();
	setClickableBound();
	marker.setPosition(xPos, yPos);

	bar.setSize(Vector2f(bW-MARKER_WIDTH, BAR_HEIGHT));
	bar.setOrigin(0, BAR_HEIGHT / 2);
	bar.setFillColor(BAR_COLOR);
	bar.setPosition(x+MARKER_WIDTH/2, y+height/2);

	RectangleShape* guideLine;
	for (int i = 0; i <= values; i++) {
		guideLine = new RectangleShape();
		guideLine->setFillColor(GUIDELINE_COLOR);
		guideLine->setSize(Vector2f(MARKER_WIDTH, MARKER_HEIGHT));
		guideLine->setPosition(x + i * ((bW-MARKER_WIDTH) / values), y);
		guideLines.push_back(guideLine);
	}
}

void Slider::drawSliderBar(RenderWindow& window) {
	window.draw(canvas->getBackground());
	window.draw(bar);
	for (RectangleShape* guideLine : guideLines) window.draw(*guideLine);
	draggable(window);
}