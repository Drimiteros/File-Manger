#include "FPS.h"

FPS::FPS()
{

}

void FPS::logic()
{
	time = fpsClock.getElapsedTime();
	fpsClock.restart().asSeconds();
	cout << "FPS: " << 1.0f / time.asSeconds() << endl;
}