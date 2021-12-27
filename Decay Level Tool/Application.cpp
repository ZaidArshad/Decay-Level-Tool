#include "Application.h"

Application::Application() {
	background.setSize(Vector2f(WIDTH, HEIGHT));
	background.setFillColor(BACKGROUND_COLOR);
	canvas = new Canvas();
}

Application::~Application() {
	delete canvas;
}

void Application::drawCanvas(RenderWindow& window) {
	window.draw(canvas->getBackground());
	for (RectangleShape* guideLine : canvas->getGuideLines()) {
		window.draw(*guideLine);
	}
}

Canvas* Application::getCanvas() {
	return canvas;
}

void Application::draw(RenderWindow& window) {
	window.draw(background);
	drawCanvas(window);
}
