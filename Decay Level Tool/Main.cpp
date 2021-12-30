#include"SFML\Graphics.hpp"
#include "Application.h"
#include "PlayerStart.h"
#include "Platform.h"
#include "Prompt.h"

using namespace sf;

int main() {
	Application* application = new Application();
	RenderWindow window(VideoMode(application->WIDTH, application->HEIGHT),
		"DECAY Level Tool", sf::Style::Titlebar | sf::Style::Close);
	Platform platform(application->getCanvas(), 0);
	PlayerStart playerStart(application->getCanvas());

	vector<Draggable*> draggables;
	draggables.push_back(&platform);
	draggables.push_back(&playerStart);
	

	Event event;
	window.setFramerateLimit(60);

	while (window.isOpen()) {

		while (window.pollEvent(event)) {

			if (event.type == Event::Closed) {

				window.close();
			}
		}

		window.clear();
		application->draw(window, draggables);
		window.display();
	}

	delete application;
	return 0;
}
