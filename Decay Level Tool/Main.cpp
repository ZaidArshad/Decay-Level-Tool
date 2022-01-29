#include"SFML\Graphics.hpp"
#include "Application.h"
#include "PlayerStart.h"
#include "Platform.h"
#include "Prompt.h"

using namespace sf;

int main() {
	
	RenderWindow* window = new RenderWindow(VideoMode(Application::WIDTH, Application::HEIGHT),
		"DECAY Level Tool", sf::Style::Titlebar | sf::Style::Close );
	Application* application = new Application(window);
	Platform platform(application->getLevelArea(), 0);
	
	Event event;
	window->setFramerateLimit(60);

	bool space = false;

	while (window->isOpen()) {
		while (window->pollEvent(event)) {
			if (event.type == Event::Closed) {
				window->close();
			}
		}

		if (Keyboard::isKeyPressed(Keyboard::Space)) {
			if (!space) {
				space = true;
				application->addPlatform(new Platform(application->getLevelArea(), 4));
			}
		}
		else {
			space = false;
		}

		window->clear();
		application->draw();
		window->display();
	}

	delete application;
	return 0;
}
