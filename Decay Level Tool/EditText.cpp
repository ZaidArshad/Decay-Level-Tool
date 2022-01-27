#include "EditText.h"
#include "Button.cpp"

EditText::EditText(float x, float y, float w, string font,
	string t, int fSize, float mi, float ma) {
	xPos = x;
	yPos = y;
	width = w;
	min = mi;
	max = ma;

	title = new Prompt(xPos, yPos, font, fSize, t, TEXT_COLOR);
	edit = new Prompt(xPos-width/4, yPos+2*fSize-5*MARGIN, font, fSize, "8888", TEXT_COLOR);

	bound = Bound(yPos-fSize/2, xPos-width/2, x+w/2, yPos + 2*fSize + MARGIN);

	editBackground.setPosition(xPos - width / 2 + MARGIN, yPos + fSize);
	editBackground.setSize(Vector2f(width / 2, fSize + MARGIN));
	editBackground.setFillColor(BACKGROUND_COLOR);

	/*test.setPosition(bound.getLeft() ,bound.getTop());
	test.setSize(Vector2f(bound.getRight() - bound.getLeft(),
		bound.getBot() - bound.getTop()));
	test.setFillColor(Color(255,255,255,100));*/
	plus = new Button<EditText>(
		bound.getCenter().x + 4*MARGIN + BUTTON_SIZE/2,
		bound.getCenter().y + BUTTON_SIZE / 2,
		"plus.png", [](EditText* self) {
			self->add();
		});

	minus = new Button<EditText>(
		bound.getCenter().x + 7*MARGIN + (1.5)*BUTTON_SIZE,
		bound.getCenter().y + BUTTON_SIZE / 2,
		"minus.png", [](EditText* self) {
			self->subtract();
		});

}

void EditText::draw(RenderWindow& window, float* v, int d) {
	value = v;
	edit->setString(to_string(d));
	window.draw(editBackground);
	window.draw(title->getText());
	window.draw(edit->getText());
	plus->draw(window);
	plus->mouseInteract(window, this);
	minus->draw(window);
	minus->mouseInteract(window, this);
	//window.draw(test);
}

Bound EditText::getBound() { return bound; }

void EditText::add() {
	if (*value < max) (*value)++;
}

void EditText::subtract() {
	if (*value > min) (*value)--;
}