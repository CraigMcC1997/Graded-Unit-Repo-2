#include "Level.h"

void Level::init()
{
	display->init();
}

void Level::print(SDL_Window* window)
{
	display->print(window);
}

void Level::input(SDL_Event _event)
{
	update->update(_event);
}