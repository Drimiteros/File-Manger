#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "FilePath.h"
#include "MouseCursor.h"

using namespace sf;
using namespace std;

class Options
{
private:
	Font font;
	double scale[5] = { 0, 0, 0, 0, 0 };
	int scaleVal = 50;
	int theme = 0;
	Clock scaleClock;
	Texture texture[2];
	Texture arrowTexture[2];
	RectangleShape lightTheme;
	RectangleShape darkTheme;

public:
	Text optionsText;
	Text text[24];
	Text closeText;
	Sprite sel;
	Sprite optionsWindow;
	Sprite arrow[2];

	Options();
	void scaleMenu(FilePath& fp, vector <FilePath>& fps, FileIcon& fi, vector<FileIcon>& fis,
		int& scrollCounter, int& scroll, MouseCursor& mc, bool& isOpen, Color& appliedColor, int& theme);
	void draw(RenderWindow& window);
};

