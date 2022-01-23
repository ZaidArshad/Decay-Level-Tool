#include "Application.h"

void hello() { std::cout << "pp\n"; }

Application::Application() {
	background.setSize(Vector2f(WIDTH, HEIGHT));
	background.setFillColor(BACKGROUND_COLOR);
	levelArea = new Canvas(
		LEVEL_WIDTH, LEVEL_HEIGHT,
		LEVEL_MARGIN, LEVEL_MARGIN,
		LEVEL_BACKGROUND_COLOR);


	generateButtons();
	generateProperties();
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
	drawPropertiesArea(window);

	// Must set draw the platforms before enabling their clickablility
	for (int i = platforms.size()-1; i >= 0; i--) {
		platforms[i]->draw(window);
	}
	for (int i = 0; i < platforms.size(); i++) {
		platforms[i]->draggable(window);
	}
}

void Application::addPlatform(Platform* platform) {
	platforms.insert(platforms.begin(), platform);
}

void Application::removePlatform(Platform* platform) {
	for (int i = 0; i < platforms.size(); i++) {
		if (platform == platforms[i]) {
			platforms.erase(platforms.begin() + i);
			break;
		}
	}
}

void Application::movePlatformForward(Platform* platform) {
	for (int i = 0; i < platforms.size(); i++) {
		if (platform == platforms[i]) {
			platforms.erase(platforms.begin() + i);
			platforms.insert(platforms.begin(), platform);
			break;
		}
	}
}

void Application::movePlatformBack(Platform* platform) {
	for (int i = 0; i < platforms.size(); i++) {
		if (platform == platforms[i]) {
			platforms.erase(platforms.begin() + i);
			platforms.push_back(platform);
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

void Application::generateButtons() {
	buttonsArea = new Canvas(
		SIDE_WIDTH, BUTTON_AREA_HEIGHT,
		LEVEL_WIDTH + (2 * LEVEL_MARGIN), LEVEL_MARGIN,
		SIDE_BACKGROUND_COLOR);

	Button* addButton = new Button(
		buttonsArea->getBound().getLeft() + HALF_BUTTON_SIZE + BUTTON_MARGIN,
		buttonsArea->getCenterPosition().y,
		"add.png", [](Application* self) {
			self->addPlatform(new Platform(self->getLevelArea(), 0));
		});

	Button* removeButton = new Button(
		buttonsArea->getBound().getLeft() + 3*HALF_BUTTON_SIZE + 2*BUTTON_MARGIN,
		buttonsArea->getCenterPosition().y,
		"remove.png", [](Application* self) {
			self->removePlatform((Platform*) self->getLevelArea()->getLastClicked());
			self->getLevelArea()->setLastClicked(nullptr);
		});

	Button* moveUpButton = new Button(
		buttonsArea->getBound().getLeft() + 5*HALF_BUTTON_SIZE + 3*BUTTON_MARGIN,
		buttonsArea->getCenterPosition().y,
		"move_up.png", [](Application* self) {
			self->movePlatformForward((Platform*)self->getLevelArea()->getLastClicked());
		});

	Button* moveBackButton = new Button(
		buttonsArea->getBound().getLeft() + 7*HALF_BUTTON_SIZE + 4*BUTTON_MARGIN,
		buttonsArea->getCenterPosition().y,
		"move_down.png", [](Application* self) {
			self->movePlatformBack((Platform*)self->getLevelArea()->getLastClicked());
		});


	buttons.push_back(addButton);
	buttons.push_back(removeButton);
	buttons.push_back(moveUpButton);
	buttons.push_back(moveBackButton);
}

void Application::drawPropertiesArea(RenderWindow& window) {
	window.draw(propArea->getBackground());
	if (levelArea->getLastClicked() != nullptr) {
		slider->drawSliderBar(window, (Platform*)levelArea->getLastClicked());
		slider->draw(window);
	}
}

void Application::generateProperties() {
	propArea = new Canvas(
		SIDE_WIDTH, PROP_HEIGHT,
		LEVEL_WIDTH + (2 * LEVEL_MARGIN), 2 * LEVEL_MARGIN + BUTTON_AREA_HEIGHT,
		SIDE_BACKGROUND_COLOR);

	slider = new Slider(propArea->getBound().getLeft() + BUTTON_MARGIN,
		propArea->getBound().getTop() + BUTTON_MARGIN, SIDE_WIDTH - 2 * BUTTON_MARGIN,
		"Health", 8);
}