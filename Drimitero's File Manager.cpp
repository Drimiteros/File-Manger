#include <iostream>
#include <SFML/Graphics.hpp>
#include "FilePath.h"
#include "MouseCursor.h"
#include "Options.h"
#include "FPS.h"

using namespace sf;
using namespace std;

int main()
{
	//DEFINE WINDOW AND PROPERTIES
	RenderWindow window(VideoMode(900, 610), "Drimitero's File Explorer", Style::Close);
	Event eve;
	bool focused = true;
	Color appliedColor(255, 255, 255);
	int theme = 0;

	//MOUSE CURSOR
	MouseCursor mc;
	bool instructionClick = false;
	int scroll = 0;
	int scrollCounter = 0;

	//AUDIO
	string soundPath;

	//DISK INFO
	DiskSize ds;
	vector<DiskSize> dss;
	ds.getDiskCount(ds, dss);

	//FILE PATH
	FilePath fl;
	vector<FilePath> fls;
	FileIcon fi;
	vector<FileIcon> fis;
	int fileCount = 0;

	//TYPE TEXT
	string enterFilePath;
	string enterFilePath_a;
	bool isKeyPressed = false;
	bool enter = false;

	//OPTIONS
	Options opt;
	bool isOpen = false;

	//FPS
	FPS fps;

	while (window.isOpen())
	{
		while (window.pollEvent(eve))
		{
			if (eve.type == Event::Closed)
				window.close();

			//FOCUS EVENT
			if (eve.type == Event::GainedFocus)
				focused = true;
			else if (eve.type == Event::LostFocus)
				focused = false;

			//TEXT EVENT
			{
				//ENTER TEXT
				if (eve.type == Event::TextEntered && !Keyboard::isKeyPressed(Keyboard::Enter))
				{
					enterFilePath = enterFilePath + eve.text.unicode;
					isKeyPressed = true;
				}
				else
					isKeyPressed = false;
				//BACKSPACE
				if (Keyboard::isKeyPressed(Keyboard::Backspace))
				{
					enterFilePath_a = enterFilePath.substr(0, enterFilePath.length() - 1);
					enterFilePath = enterFilePath_a;
				}
				if (Keyboard::isKeyPressed(Keyboard::Backspace) && Keyboard::isKeyPressed(Keyboard::LShift))
				{
					enterFilePath_a = "";
					enterFilePath = enterFilePath_a;
				}
				//ENTER
				if (Keyboard::isKeyPressed(Keyboard::Enter) && enter == false)
					enter = true;
			}

			//MOUSE WEEL EVENTS
			if (eve.type == Event::MouseWheelScrolled)
			{
				if (eve.mouseWheelScroll.delta > 0)
					scroll = 1;
				else if (eve.mouseWheelScroll.delta < 0)
					scroll = -1;
			}
		}

		//WINDOW PROPERTIES
		//window.setFramerateLimit(60);
		window.setMouseCursorVisible(false);
		fps.logic();

		//CLEAR FRAMES
		window.clear(appliedColor);

		//DISK INFO
		//FOCUS CHECK
		if (focused && !isOpen)
			ds.logic(dss, ds, fl, fls, mc, enterFilePath, enter, isKeyPressed, fi, fis, instructionClick, scrollCounter, fileCount, theme);
		ds.draw(ds, dss, window, mc);

		//FIND FILE PATH
		//FOCUS CHECK
		if (focused && !isOpen)
			fl.findFile(enterFilePath, isKeyPressed, enter, mc, fi, fis, instructionClick, scroll, scrollCounter, fileCount, theme, fps);
		fl.draw(window, fi, fis, mc, isOpen);

		//OPTIONS
		//FOCUS CHECK
		if (focused)
			opt.scaleMenu(fl, fls, fi, fis, scrollCounter, scroll, mc, isOpen, appliedColor, theme);
		opt.draw(window);

		//MOUSE CURSOR
		//FOCUS CHECK
		if (focused)
			mc.logic(window);
		mc.draw(window);

		//DISPLAY FRAMES
		window.display();
	}
}