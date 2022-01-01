#include "Application.h"
#include "Button.h"

Application::Application() {
	background.setSize(Vector2f(WIDTH, HEIGHT));
	background.setFillColor(BACKGROUND_COLOR);
	levelArea = new Canvas(
		LEVEL_WIDTH, LEVEL_HEIGHT,
		LEVEL_MARGIN, LEVEL_MARGIN,
		LEVEL_BACKGROUND_COLOR);

	buttonsArea = new Canvas(
		SIDE_WIDTH, BUTTONS_HEIGHT,
		LEVEL_WIDTH+(2*LEVEL_MARGIN), LEVEL_MARGIN,
		SIDE_BACKGROUND_COLOR);

	setGuideLines();
}

Application::~Application() {
	for (RectangleShape* line : guideLines) delete line;
	delete levelArea;
}

Canvas* Application::getLevelArea() {
	return levelArea;
}

void Application::draw(RenderWindow& window, vector<Draggable*> draggables) {
	window.draw(background);
	drawLevelArea(window);
	drawButtonsArea(window);

	for (int i = 0; i < draggables.size(); i++) {
		draggables[i]->draggable(window);
		draggables[draggables.size() - i - 1]->draw(window);
	}
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

void Application::drawButtonsArea(RenderWindow& window) {
	window.draw(buttonsArea->getBackground());
	Button button(
		buttonsArea->getBound().getLeft()+BUTTON_SIZE/2, buttonsArea->getCenterPosition().y,
		"can.png");
	button.mouseInteract(window);
	button.draw(window);
	//cout << buttonsArea->getBound().getLeft() << " " << buttonsArea->yPos << endl;
}