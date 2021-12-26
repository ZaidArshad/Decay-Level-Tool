#include"SFML\Graphics.hpp"
#include "Application.h"
#include "PlayerStart.h"

using namespace sf;

int main() {
	Application* application = new Application();
	RenderWindow window(VideoMode(application->WIDTH, application->HEIGHT),
		"DECAY Level Tool", sf::Style::Titlebar | sf::Style::Close);
	PlayerStart playerStart(application->getCanvas());

	Event event;
	window.setFramerateLimit(60);

	while (window.isOpen()) {

		while (window.pollEvent(event)) {

			if (event.type == Event::Closed) {

				window.close();
			}
		}

		window.clear();
		application->draw(window);
		playerStart.draw(window);
		window.display();
	}

	return 0;
}