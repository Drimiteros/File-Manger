#include "MouseCursor.h"

MouseCursor::MouseCursor()
{
	texture.loadFromFile("Files/Textures/cursor.png");
	cursor.setTexture(texture);
	cursor.setScale(0.78, 0.78);
}

void MouseCursor::logic(RenderWindow& window)
{
	cursor.setPosition(window.mapPixelToCoords(Vector2i(Mouse::getPosition(window))));
	if (state == 0)
		cursor.setTextureRect(IntRect(0, 0, 18, 18));
	if (state == 1)
		cursor.setTextureRect(IntRect(19, 0, 18, 18));
}

void MouseCursor::draw(RenderWindow& window)
{
	window.draw(cursor);
}