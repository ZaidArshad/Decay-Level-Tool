#include "Application.h"

void hello() { std::cout << "pp\n"; }

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

	Button* addButton = new Button(
		buttonsArea->getBound().getLeft() + BUTTON_SIZE / 2, buttonsArea->getCenterPosition().y,
		"add.png", [](Application* self){
			self->addPlatform(new Platform(self->getLevelArea(), 4));
		});

	Button* removeButton = new Button(
		buttonsArea->getBound().getLeft() + BUTTON_SIZE / 2 + BUTTON_SIZE,
		buttonsArea->getCenterPosition().y,
		"remove.png", [](Application* self) {
			self->removePlatform((Platform*) self->getLevelArea()->getLastClicked());
		});

	buttons.push_back(addButton);
	buttons.push_back(removeButton);

	setGuideLines();
}

Application::~Application() {
	for (RectangleShape* line : guideLines) delete line;
	delete levelArea;
}

Canvas* Application::getLevelArea() {
	return levelArea;
}

void Application::draw(RenderWindow& window) {
	window.draw(background);
	drawLevelArea(window);
	drawButtonsArea(window);

	for (int i = 0; i < platforms.size(); i++) {
		platforms[i]->draggable(window);
		platforms[platforms.size() - i - 1]->draw(window);
	}
}

void Application::addPlatform(Platform* platform) {
	platforms.push_back(platform);
}

void Application::removePlatform(Platform* platform) {
	for (int i = 0; i < platforms.size(); i++) {
		if (platform == platforms[i]) {
			platforms.erase(platforms.begin() + i);
			break;
		}
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
	for (Button* button : buttons) {
		button->mouseInteract(window, this);
		button->draw(window);
	}
}