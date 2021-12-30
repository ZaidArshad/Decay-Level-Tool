#pragma once
#include <SFML/Graphics.hpp>
#include "Bound.h"
#include "Canvas.h"
#include "Draggable.h"

using namespace sf;
using namespace std;

class PlayerStart : public Draggable {
public:
	PlayerStart(Canvas* c);

private:
	Texture playerTexture;
	Sprite playerSprite;
};

