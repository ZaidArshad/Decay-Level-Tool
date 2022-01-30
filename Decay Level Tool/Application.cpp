#include "Application.h"
#include "Button.cpp"

void hello() { std::cout << "pp\n"; }

Application::Application(RenderWindow* w) {
	window = w;
	background.setSize(Vector2f(WIDTH, HEIGHT));
	background.setFillColor(BACKGROUND_COLOR);
	
	levelArea = new Canvas(
		LEVEL_WIDTH, LEVEL_HEIGHT,
		LEVEL_MARGIN, LEVEL_MARGIN,
		LEVEL_BACKGROUND_COLOR);

	playerStart = new PlayerStart(levelArea);

	generateProperties();
	generateButtons();
	setGuideLines();
}

Application::~Application() {
	delete playerStart;
	delete levelArea;
	guideLines.clear();
	guideLines.shrink_to_fit();
	delete buttonsArea;
	buttons.clear();
	buttons.shrink_to_fit();
	delete exportBtn;
	delete propArea;
	delete slider;
	editTexts.clear();
	editTexts.shrink_to_fit();
}

Canvas* Application::getLevelArea() {
	return levelArea;
}

RenderWindow* Application::getWindow() { return window; }

void Application::draw() {
	if (isExporting) {
		system(EXPORT_FILE);
		isExporting = false;
	}

	window->draw(background);
	playerStart->draggable(*window);
	drawLevelArea();
	drawPropertiesArea();
	drawButtonsArea();

	// Must set draw the platforms before enabling their clickablility
	for (int i = platforms.size()-1; i >= 0; i--) {
		platforms[i]->draw(*window);
	}
	for (int i = 0; i < platforms.size(); i++) {
		platforms[i]->draggable(*window);
	}
	playerStart->draw(*window);

	exportBtn->mouseInteract(*window, this);
	exportBtn->draw(*window);
}

void Application::addPlatform(Platform* platform) {
	platforms.insert(platforms.begin(), platform);
}

void Application::removePlatform(Platform* platform) {
	for (int i = 0; i < platforms.size(); i++) {
		if (platform == platforms[i]) {
			delete platforms[i];
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

void Application::exportLevel() {

	RectangleShape notInFocus(Vector2f(WIDTH, HEIGHT));
	notInFocus.setPosition(0 , 0);
	notInFocus.setFillColor(Color(255,255,255,100));
	window->draw(notInFocus);

	Prompt fileOpen(levelArea->getCenterPosition().x, 
		levelArea->getCenterPosition().y, "ka1.ttf", 100, "Exported", Color::Red);
	window->draw(fileOpen.getText());

	ofstream file(EXPORT_FILE);
	file << playerStart->getClickableBound().getLeft() - LEVEL_MARGIN << " ";
	file << playerStart->getClickableBound().getTop() - LEVEL_MARGIN << endl;

	for (Platform* platform : platforms) {
		file << platform->getHealth() << " " << platform->getWidth() << " " << platform->getHeight() <<
			" " << platform->getClickableBound().getLeft() - LEVEL_MARGIN <<
			" " << platform->getClickableBound().getTop() - LEVEL_MARGIN << endl;
	}
	file.close();

	// Enables the prompt to actually show up
	isExporting = true;
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

void Application::drawLevelArea() {
	window->draw(levelArea->getBackground());
	for (RectangleShape* guideLine : guideLines) {
		window->draw(*guideLine);
	}
}

void Application::drawButtonsArea() {
	window->draw(buttonsArea->getBackground());
	for (Button<Application>* button : buttons) {
		button->mouseInteract(*window, this);
		button->draw(*window);
	}
}

void Application::generateButtons() {
	buttonsArea = new Canvas(
		SIDE_WIDTH, BUTTON_AREA_HEIGHT,
		LEVEL_WIDTH + (2 * LEVEL_MARGIN), LEVEL_MARGIN,
		SIDE_BACKGROUND_COLOR);

	Button<Application>* addButton = new Button<Application>(
		buttonsArea->getBound().getLeft() + HALF_BUTTON_SIZE + BUTTON_MARGIN,
		buttonsArea->getCenterPosition().y,
		"add.png", [](Application* self) {
			self->addPlatform(new Platform(self->getLevelArea(), 0));
		});

	Button<Application>* removeButton = new Button<Application>(
		buttonsArea->getBound().getLeft() + 3*HALF_BUTTON_SIZE + 2*BUTTON_MARGIN,
		buttonsArea->getCenterPosition().y,
		"remove.png", [](Application* self) {
			self->removePlatform((Platform*) self->getLevelArea()->getLastClicked());
			self->getLevelArea()->setLastClicked(nullptr);
		});

	Button<Application>* moveUpButton = new Button<Application>(
		buttonsArea->getBound().getLeft() + 5*HALF_BUTTON_SIZE + 3*BUTTON_MARGIN,
		buttonsArea->getCenterPosition().y,
		"move_up.png", [](Application* self) {
			self->movePlatformForward((Platform*)self->getLevelArea()->getLastClicked());
		});

	Button<Application>* moveBackButton = new Button<Application>(
		buttonsArea->getBound().getLeft() + 7*HALF_BUTTON_SIZE + 4*BUTTON_MARGIN,
		buttonsArea->getCenterPosition().y,
		"move_down.png", [](Application* self) {
			self->movePlatformBack((Platform*)self->getLevelArea()->getLastClicked());
		});

	exportBtn = new Button<Application>(propArea->getCenterPosition().x,
		propArea->getBound().getBot() - BUTTON_SIZE,
		"Export", "bulkypix.ttf", [](Application* self) {
			self->exportLevel();
		});

	buttons.push_back(addButton);
	buttons.push_back(removeButton);
	buttons.push_back(moveUpButton);
	buttons.push_back(moveBackButton);
}

void Application::drawPropertiesArea() {
	window->draw(propArea->getBackground());
	if (levelArea->getLastClicked() != nullptr) {
		Platform* plat = (Platform*) levelArea->getLastClicked();
		slider->drawSliderBar(*window, plat);
		slider->draw(*window);
		editTexts[0]->draw(*window, plat->getXP(), plat->getClickableBound().getLeft() - LEVEL_MARGIN);
		editTexts[1]->draw(*window, plat->getYP(), plat->getClickableBound().getTop() - LEVEL_MARGIN);
		editTexts[2]->draw(*window, plat->getWP(), plat->getWidth());
		editTexts[3]->draw(*window, plat->getHP(), plat->getHeight());
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

	EditText* xEdit = new EditText(propArea->getCenterPosition().x,
		slider->getCanvas()->getBound().getBot() + BUTTON_MARGIN + PROP_TITLE_SIZE,
		SIDE_WIDTH - 2*BUTTON_MARGIN, "bulkypix.ttf", "X Position", PROP_TITLE_SIZE,
		0, LEVEL_WIDTH-MARGIN);

	EditText* yEdit = new EditText(propArea->getCenterPosition().x,
		xEdit->getBound().getBot() + PROP_TITLE_SIZE/2,
		SIDE_WIDTH - 2 * BUTTON_MARGIN, "bulkypix.ttf", "Y Position", PROP_TITLE_SIZE,
		0, LEVEL_HEIGHT);

	EditText* wEdit = new EditText(propArea->getCenterPosition().x,
		yEdit->getBound().getBot() + PROP_TITLE_SIZE / 2,
		SIDE_WIDTH - 2 * BUTTON_MARGIN, "bulkypix.ttf", "Width", PROP_TITLE_SIZE,
		0, LEVEL_WIDTH);

	EditText* hEdit = new EditText(propArea->getCenterPosition().x,
		wEdit->getBound().getBot() + PROP_TITLE_SIZE / 2,
		SIDE_WIDTH - 2 * BUTTON_MARGIN, "bulkypix.ttf", "Height", PROP_TITLE_SIZE,
		0, LEVEL_HEIGHT);

	editTexts.push_back(xEdit);
	editTexts.push_back(yEdit);
	editTexts.push_back(wEdit);
	editTexts.push_back(hEdit);
}