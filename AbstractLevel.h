#pragma once
#include "AbstractWindow.h"
#include "AbstractDisplay.h"
#include "AbstractUpdate.h"
class AbstractLevel
{
protected:
	AbstractDisplay* display;
	AbstractUpdate* update;
public:
	virtual ~AbstractLevel()	//	destructor
	{
		delete display;
		delete update;
	}

	virtual void input(SDL_Event _event) = 0;
	virtual void print(SDL_Window* window) = 0;
	virtual void init() = 0;
};