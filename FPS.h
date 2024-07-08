#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

class FPS
{
private:

public:
	Clock fpsClock;
	Time time;

	FPS();
	void logic();
};

