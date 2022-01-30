#include"SFML\Graphics.hpp"
#include "Application.h"
#include "PlayerStart.h"
#include "Platform.h"
#include "Prompt.h"

using namespace sf;

int main() {
	
	RenderWindow* window = new RenderWindow(VideoMode(Application::WIDTH, Application::HEIGHT),
		"DECAY Level Tool", sf::Style::Titlebar | sf::Style::Close);
	Application* application = new Application(window);
	
	Event event;
	window->setFramerateLimit(60);

	while (window->isOpen()) {
		while (window->pollEvent(event)) {
			if (event.type == Event::Closed) {
				window->close();
			}
		}
		window->clear();
		application->draw();
		window->display();
	}

	delete application;
	delete window;
	return 0;
}
