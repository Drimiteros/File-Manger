#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

class MouseCursor
{
private:
	Texture texture;

public:
	Sprite cursor;
	bool selected = false;
	Clock selectedClock;
	int state = 0;

	MouseCursor();
	void logic(RenderWindow& window);
	void draw(RenderWindow& window);
};

