#pragma once
#include "SDL2/SDL.h"
class AbstractUpdate
{
public:
	virtual void update(SDL_Event _event) = 0;
};