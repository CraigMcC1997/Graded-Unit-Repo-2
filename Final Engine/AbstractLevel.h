#pragma once
#include "AbstractDisplay.h"
#include "AbstractLevelUpdate.h"
#include "Collision.h"
#include "PlaySound.h"
class AbstractLevel
{
protected:
	AbstractDisplay* display;
	AbstractLevelUpdate* lUpdate;
	HSAMPLE *samples = new HSAMPLE[5];
public:
	virtual ~AbstractLevel()
	{
		delete display;
		delete lUpdate;
	}

	virtual void init() = 0;
	virtual void draw(SDL_Window* window) = 0;
	virtual void update(AbstractLevel** level) = 0;
};