#include"SFML\Graphics.hpp"
#include "Application.h"

using namespace sf;

int main() {
	Application* application = new Application();
	RenderWindow window(VideoMode(application->WIDTH, application->HEIGHT),
		"DECAY Level Tool", sf::Style::Titlebar | sf::Style::Close);

	Event event;
	window.setFramerateLimit(60);

	while (window.isOpen()) {

		while (window.pollEvent(event)) {

			if (event.type == Event::Closed) {

				window.close();
			}
		}

		window.clear();
		application->drawApplication(window);
		window.display();
	}

	return 0;
}
