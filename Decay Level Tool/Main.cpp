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
	Platform platform(application->getLevelArea(), 0);
	PlayerStart playerStart(application->getLevelArea());

	vector<Draggable*> draggables;
	draggables.push_back(&platform);
	draggables.push_back(&playerStart);
	

	Event event;
	window.setFramerateLimit(60);

	bool space = false;

	while (window.isOpen()) {

		while (window.pollEvent(event)) {

			if (event.type == Event::Closed) {

				window.close();
			}
		}

		if (Keyboard::isKeyPressed(Keyboard::Space)) {
			if (!space) {
				space = true;
				Platform* platform2 = new Platform(application->getLevelArea(), 4);
				draggables.push_back(platform2);
			}
		}
		else {
			space = false;
		}

		window.clear();
		application->draw(window, draggables);
		window.display();
	}

	delete application;
	return 0;
}
