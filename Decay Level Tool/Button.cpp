#include "Button.h"

Button::Button(float x, float y, string fileName) {

	// Position and size data
	xPos = x;
	yPos = y;
	const int MARGIN = 10; //Space around text from button
	const int BORDER_WIDTH = 10; //Border width

	if (!buttonTexture.loadFromFile("images/" + fileName)) {
		std::cout << "Load failed\n";
		system("pause");
	}

	buttonSprite.setTexture(buttonTexture);
	width = buttonTexture.getSize().x;
	height = buttonTexture.getSize().y;
	buttonSprite.setOrigin(width / 2, height / 2);
	buttonSprite.setPosition(x, y);

	// Building border around button
	border.setSize(sf::Vector2f(width +MARGIN+ BORDER_WIDTH, height + MARGIN + BORDER_WIDTH));
	border.setFillColor(Color::White);
	border.setOrigin(border.getLocalBounds().width / 2, border.getLocalBounds().height / 2);
	border.setPosition(xPos, yPos);
	border.setFillColor(Color::White);

	// Building inner portion of button
	inside.setSize(sf::Vector2f(width + MARGIN, height + MARGIN));
	inside.setFillColor(Color::Blue);
	inside.setOrigin(inside.getLocalBounds().width / 2, inside.getLocalBounds().height / 2);
	inside.setPosition(xPos, yPos);
	inside.setFillColor(Color::Black);

}

// Draws the entire button the screen
void Button::draw(RenderWindow& window) {
	window.draw(border);
	window.draw(inside);
	window.draw(buttonSprite);
}

// Allows the mouse to interact with the button (highlights and when clicked return true)
bool Button::mouseInteract(RenderWindow& window) {
	// Gets current mouse attributes
	Mouse mouse;

	// If the button is in contact with the mouse color it
	if (border.getGlobalBounds().contains(mouse.getPosition(window).x, mouse.getPosition(window).y)) {
		border.setFillColor(Color::Black);
		inside.setFillColor(Color::White);

		// If left mouse button is clicked
		if (mouse.isButtonPressed(Mouse::Button::Left))
			return true;
	}
	else {
		// Sets the button's color to the default
		border.setFillColor(Color::White);
		inside.setFillColor(Color::Black);
		return false;
	}
}