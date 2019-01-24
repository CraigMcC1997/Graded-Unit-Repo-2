#include "AbstractDisplay.h"
#include "loadTexture.h"
#include "Move.h"

#pragma once
class PlayerDisplay : public AbstractDisplay
{
private:
public:
	void print(SDL_Window* window);
	void init();
};