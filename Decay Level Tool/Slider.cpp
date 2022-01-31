#include "Slider.h"
#include <math.h>

Slider::Slider(float x, float y, float bW, string title, int values) {
	type = SLIDER;
	self = this;
	numOfValues = values - 1;
	alloc();
	*width = MARKER_WIDTH;
	*height = MARKER_HEIGHT;
	marker.setSize(Vector2f(*width, *height));
	marker.setFillColor(MARKER_COLOR);
	drawable = &marker;
	transformable = &marker;
	*xPos = x;
	*yPos = y + TITLE_SIZE;
	canvas = new Canvas(
		bW, MARKER_HEIGHT, *xPos, *yPos, Color::Transparent);
	isClicked = false;
	canvasBound = canvas->getBound();
	updateClickableBound();
	marker.setPosition(*xPos, *yPos);
	barWidth = bW - MARKER_WIDTH;

	titlePrompt = new Prompt(canvas->getCenterPosition().x,
		y + MARGIN, "bulkypix.ttf", TITLE_SIZE, title, BAR_COLOR);

	generateBar();
	generateGuideLines();
}

Slider::~Slider() {
	guideLines.clear();
	guideLines.shrink_to_fit();
	titleValues.clear();
	titleValues.shrink_to_fit();
	delete titlePrompt;
}

void Slider::drawSliderBar(RenderWindow& window, Platform* p) {
	if (p == platform) {
		newPlat = false;
	}
	else {
		platform = p;
		newPlat = true;
		isClicked = false;
	}

	window.draw(canvas->getBackground());
	window.draw(bar);
	window.draw(titlePrompt->getText());

	for (int i = 0; i <= numOfValues; i++) {
		window.draw(*guideLines[i]);
		window.draw(titleValues[i]->getText());
	}

	draggable(window);
	snapToGuide();
}

void Slider::snapToGuide() {
	if (newPlat) {
		marker.setOrigin(*width / 2, marker.getOrigin().y);
		*xPos = guideLines[platform->getHealth()]->getPosition().x + MARKER_WIDTH / 2;
		marker.setPosition(*xPos, *yPos);
	}

	if (isClicked) {
		int health = round(-1 * (bar.getPosition().x - *xPos) / (barWidth / numOfValues));
		platform->setHealth(health);
		isSnappedToGuide = false;
	}

	if (!isSnappedToGuide) {
		if (!isClicked) {
			//Snapping Action when let go of slider
			isSnappedToGuide = true;
			marker.setOrigin(*width / 2, marker.getOrigin().y);
			*xPos = guideLines[platform->getHealth()]->getPosition().x + MARKER_WIDTH / 2;
			marker.setPosition(*xPos, *yPos);
		}
	}
}

void Slider::generateBar() {
	bar.setSize(Vector2f(barWidth, BAR_HEIGHT));
	bar.setOrigin(0, BAR_HEIGHT / 2);
	bar.setFillColor(BAR_COLOR);
	bar.setPosition(*xPos + MARKER_WIDTH / 2, *yPos + *height / 2);
}

void Slider::generateGuideLines() {
	RectangleShape* guideLine;
	Prompt* titleValue;
	for (int i = 0; i <= numOfValues; i++) {
		guideLine = new RectangleShape();
		guideLine->setFillColor(GUIDELINE_COLOR);
		guideLine->setSize(Vector2f(MARKER_WIDTH, MARKER_HEIGHT));
		guideLine->setPosition(*xPos + i * (barWidth / numOfValues), *yPos);
		titleValue = new Prompt(*xPos + i * (barWidth / numOfValues) + MARKER_WIDTH/2,
			*yPos + MARKER_HEIGHT + MARGIN,"bulkypix.ttf", VALUES_SIZE, to_string(i), BAR_COLOR);
		titleValues.push_back(titleValue);
		guideLines.push_back(guideLine);
	}
}