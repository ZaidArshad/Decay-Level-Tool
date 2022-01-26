#include "EditText.h"

EditText::EditText(float x, float y, float w, string font, string t, int fSize) {
	xPos = x;
	yPos = y;
	width = w;

	title = new Prompt(xPos, yPos, font, fSize, t, TEXT_COLOR);
	edit = new Prompt(xPos-width/4, yPos+2*fSize-5*MARGIN, font, fSize, "8888", TEXT_COLOR);

	bound = Bound(yPos-fSize/2, xPos-width/2, x+w/2, yPos + 2*fSize + MARGIN);

	editBackground.setPosition(xPos - width / 2, yPos + fSize);
	editBackground.setSize(Vector2f(width / 2, fSize + MARGIN));
	editBackground.setFillColor(BACKGROUND_COLOR);

	/*test.setPosition(bound.getLeft() ,bound.getTop());
	test.setSize(Vector2f(bound.getRight() - bound.getLeft(),
		bound.getBot() - bound.getTop()));
	test.setFillColor(Color(255,255,255,100));*/
}

void EditText::draw(RenderWindow& window, int v) {
	value = v;
	edit->setString(to_string(value));
	window.draw(editBackground);
	window.draw(title->getText());
	window.draw(edit->getText());
	//window.draw(test);
}

Bound EditText::getBound() { return bound; }

void EditText::add() {
	(value)++;
}

void EditText::subtract() {
	(value)--;
}