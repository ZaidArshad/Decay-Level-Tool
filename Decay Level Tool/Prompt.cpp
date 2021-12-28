#include "Prompt.h"

Prompt::Prompt(float xPos, float yPos, string fontName, int fSize, string text, sf::Color color) {
	xPosition = xPos;
	yPosition = yPos;
	textString = text;
	textColor = color;
	fontSize = fSize;

	font = loadFont(fontName);

	textObj.setFont(font);
	textObj.setString(textString);
	textObj.setCharacterSize(fontSize);
	textObj.setFillColor(sf::Color(color.r, color.g, color.b, alpha));
	textObj.setPosition(xPosition, yPosition);

	textObj.setOrigin(textObj.getLocalBounds().width / 2, textObj.getLocalBounds().height / 2);
}


sf::Text Prompt::getText() { return textObj; }
sf::Font Prompt::getFont() { return font; }
sf::Color Prompt::getColor() { return Color(fontR, fontG, fontB, alpha); }

void Prompt::setColor(sf::Color c) {
	textObj.setFillColor(c);
}

void Prompt::textColorShifter() {
	if (iterator < 255 && iterator >= 0) {
		fontR++;
		fontB--;
	}
	else if (iterator < 510 && iterator >= 255) {
		fontG++;
		fontR--;
	}
	else if (iterator < 765 && iterator >= 510) {
		fontB++;
		fontG--;
	}
	else { iterator = -1; }
	iterator++;
	textObj.setFillColor(Color(fontR, fontG, fontB, alpha));

}

void Prompt::blink() {
	if (alpha == 255 || alpha == 0) {
		colorIncrementer *= -1;
	}
	alpha += colorIncrementer * 5;
	textObj.setFillColor(Color(fontR, fontG, fontB, alpha));
}

void Prompt::setString(string words) {
	textString = words;
	textObj.setString(words);
}

void Prompt::setPosition(float xPos, float yPos) {
	xPosition = xPos;
	yPosition = yPos;
	textObj.setOrigin(textObj.getLocalBounds().width / 2, textObj.getLocalBounds().height / 2);
	textObj.setPosition(xPos, yPos);
}

Font Prompt::loadFont(string fontFileName) {
	Font font;
	// If the font does not load
	if (!font.loadFromFile("fonts/" + fontFileName))
		std::cout << "did not load\n";
	else { return font; }
}