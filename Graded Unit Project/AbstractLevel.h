#pragma once
#include "AbstractWindow.h"
#include "AbstractDisplay.h"
#include "AbstractUpdate.h"
class AbstractLevel
{
public:
	AbstractLevel(){}
	virtual void input(SDL_Event _event) = 0;
	virtual void display(SDL_Window* window) = 0;
	virtual void init() = 0;
};