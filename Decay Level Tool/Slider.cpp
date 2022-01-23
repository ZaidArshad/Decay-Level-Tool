#include "Slider.h"
#include <math.h>

Slider::Slider(float x, float y, float bW, int values) {
	self = this;
	canvas = new Canvas(
		bW, MARKER_HEIGHT, x, y, Color::Transparent);

	values = values - 1;

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

	barWidth = bW - MARKER_WIDTH;
	bar.setSize(Vector2f(barWidth, BAR_HEIGHT));
	bar.setOrigin(0, BAR_HEIGHT / 2);
	bar.setFillColor(BAR_COLOR);
	bar.setPosition(x+MARKER_WIDTH/2, y+height/2);

	RectangleShape* guideLine;
	for (int i = 0; i <= values; i++) {
		guideLine = new RectangleShape();
		guideLine->setFillColor(GUIDELINE_COLOR);
		guideLine->setSize(Vector2f(MARKER_WIDTH, MARKER_HEIGHT));
		guideLine->setPosition(x + i * (barWidth / values), y);
		guideLines.push_back(guideLine);
	}
	numOfValues = values;
}

void Slider::drawSliderBar(RenderWindow& window, Platform* p) {
	if (p == platform) {
		newPlat = false;
	}
	else {
		platform = p;
		newPlat = true;
	}
	window.draw(canvas->getBackground());
	window.draw(bar);
	for (RectangleShape* guideLine : guideLines) window.draw(*guideLine);
	draggable(window);
	snapToGuide();
}

void Slider::snapToGuide() {
	if (newPlat) {
		marker.setOrigin(width / 2, marker.getOrigin().y);
		xPos = guideLines[platform->getHealth()]->getPosition().x + MARKER_WIDTH / 2;
		marker.setPosition(xPos, yPos);
	}

	if (isClicked) {
		int health = round(-1 * (bar.getPosition().x - xPos) / (barWidth / numOfValues));
		platform->setHealth(health);
		isSnappedToGuide = false;
	}

	if (!isSnappedToGuide) {
		if (!isClicked) {
			//Snapping Action when let go of slider
			isSnappedToGuide = true;
			marker.setOrigin(width / 2, marker.getOrigin().y);
			xPos = guideLines[platform->getHealth()]->getPosition().x + MARKER_WIDTH / 2;
			marker.setPosition(xPos, yPos);
		}
	}
}