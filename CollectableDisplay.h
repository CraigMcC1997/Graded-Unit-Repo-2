#pragma once
#include "AbstractDisplay.h"
#include "loadTexture.h"
#include "PlayerDisplay.h"

class CollectableDisplay : public AbstractDisplay
{
private:
	PlayerDisplay* pDisplay;
public:
	CollectableDisplay(PlayerDisplay* pDisplay) : pDisplay(pDisplay) {}
	void print(SDL_Window* window);
	void init();
};