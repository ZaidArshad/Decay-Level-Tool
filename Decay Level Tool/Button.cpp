#include "Button.h"

template <class T>
Button<T>::Button(float x, float y, string fileName, void(*onClick)(T*)) {

	// Position and size data
	xPos = x;
	yPos = y;
	onClickFunction = onClick;

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
	border.setSize(sf::Vector2f(width +IMG_MARGIN+ BORDER_WIDTH, height +
		IMG_MARGIN + BORDER_WIDTH));
	border.setFillColor(Color::White);
	border.setOrigin(border.getLocalBounds().width / 2, border.getLocalBounds().height / 2);
	border.setPosition(xPos, yPos);
	border.setFillColor(Color::White);

	// Building inner portion of button
	inside.setSize(sf::Vector2f(width + IMG_MARGIN, height + IMG_MARGIN));
	inside.setFillColor(Color::Blue);
	inside.setOrigin(inside.getLocalBounds().width / 2, inside.getLocalBounds().height / 2);
	inside.setPosition(xPos, yPos);
	inside.setFillColor(Color::Black);

}

template <class T>
Button<T>::Button(float x, float y, string title, string fontName, void(*onClick)(T*)) {

	// Position and size data
	xPos = x;
	yPos = y;
	onClickFunction = onClick;

	// Loads font in scope
	// If the font does not load
	if (!font.loadFromFile("fonts/" + fontName)) std::cout << "did not load\n";

	// Setting Attributes
	name = title;

	// Building text object
	text.setString(name);
	text.setCharacterSize(50);
	text.setFont(font);
	text.setFillColor(Color::White);

	// Adjusting the total width/height to match the button's with margin
	width = text.getLocalBounds().width + TXT_MARGIN;
	height = text.getLocalBounds().height + TXT_MARGIN;

	// Setting the origin to the middle of the button
	text.setOrigin(text.getLocalBounds().width / 2, text.getLocalBounds().height / 2);

	createShape();

	// Set the position of the text into the middle of the button
	text.setPosition(inside.getPosition().x, inside.getPosition().y - 5);
}

template <class T>
void Button<T>::createShape() {
	// Building border around button
	border.setSize(sf::Vector2f(width + BORDER_WIDTH, height + BORDER_WIDTH));
	border.setFillColor(Color::White);
	border.setOrigin(border.getLocalBounds().width / 2, border.getLocalBounds().height / 2);
	border.setPosition(xPos, yPos);
	border.setFillColor(Color::White);

	// Building inner portion of button
	inside.setSize(sf::Vector2f(width, height));
	inside.setFillColor(Color::Blue);
	inside.setOrigin(inside.getLocalBounds().width / 2, inside.getLocalBounds().height / 2);
	inside.setPosition(xPos, yPos);
	inside.setFillColor(Color::Black);
}

// Draws the entire button the screen
template <class T>
void Button<T>::draw(RenderWindow& window) {
	window.draw(border);
	window.draw(inside);
	window.draw(buttonSprite);
	window.draw(text);
}

// Allows the mouse to interact with the button (highlights and when clicked return true)
template <class T>
bool Button<T>::mouseInteract(RenderWindow& window, T* temp) {
	// Gets current mouse attributes
	Mouse mouse;

	// If the button is in contact with the mouse color it
	if (border.getGlobalBounds().contains(mouse.getPosition(window).x, mouse.getPosition(window).y)) {
		border.setFillColor(Color::Black);
		inside.setFillColor(Color::White);
		text.setFillColor(Color::Black);

		// If left mouse button is clicked
		if (mouse.isButtonPressed(Mouse::Button::Left)) {
			if (!isClicked && isHovered) {
				isClicked = true;
				onClickFunction(temp);
			}

			return true;
		}
		else {
			isHovered = true;
			isClicked = false;
		}
	}
	else {
		// Sets the button's color to the default
		isHovered = false;
		border.setFillColor(Color::White);
		inside.setFillColor(Color::Black);
		text.setFillColor(Color::White);
		return false;
	}
}