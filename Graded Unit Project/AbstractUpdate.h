#pragma once
#include <SDL.h>
class AbstractUpdate
{
public:
	virtual void update(SDL_Event _event) = 0;
};