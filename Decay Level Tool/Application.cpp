#include "Application.h"

Application::Application() {
	background.setSize(Vector2f(WIDTH, HEIGHT));
	background.setFillColor(BACKGROUND_COLOR);
	levelArea = new Canvas(
		LEVEL_WIDTH, LEVEL_HEIGHT,
		LEVEL_MARGIN, LEVEL_MARGIN,
		LEVEL_BACKGROUND_COLOR);
	setGuideLines();
}

Application::~Application() {
	for (RectangleShape* line : guideLines) delete line;
	delete levelArea;
}

void Application::setGuideLines() {
	int rows = LEVEL_HEIGHT / 10;
	int cols = LEVEL_WIDTH / 10;

	RectangleShape* guideLine;
	for (int i = 0; i <= rows; i++) {
		guideLine = new RectangleShape();
		guideLine->setFillColor(LEVEL_GUIDELINE_COLOR);
		guideLine->setSize(Vector2f(LEVEL_WIDTH, LEVEL_GUIDELINE_WIDTH));
		guideLine->setPosition(10, i * 10 + 10);
		guideLines.push_back(guideLine);
	}
	for (int i = 0; i <= cols; i++) {
		guideLine = new RectangleShape();
		guideLine->setFillColor(LEVEL_GUIDELINE_COLOR);
		guideLine->setSize(Vector2f(LEVEL_GUIDELINE_WIDTH, LEVEL_HEIGHT));
		guideLine->setPosition(i * 10 + 10, 10);
		guideLines.push_back(guideLine);
	}
}

void Application::drawLevelArea(RenderWindow& window) {
	window.draw(levelArea->getBackground());
	for (RectangleShape* guideLine : guideLines) {
		window.draw(*guideLine);
	}
}

Canvas* Application::getCanvas() {
	return levelArea;
}

void Application::draw(RenderWindow& window) {
	window.draw(background);
	drawLevelArea(window);
}
