#pragma once
#include "AbstractLevel.h"
#include "Window.h"
#include "LevelDisplay.h"
#include "PlayerDisplay.h"
#include "levelUpdate.h"
#include "playerUpdate.h"
#include "CollectableDisplay.h"

class Level : public AbstractLevel
{
public:
	Level(PlayerDisplay* player, playerUpdate* playerUpdate, CollectableDisplay* cDisplay, collectableUpdate* cUpdate, LevelDisplay* lDisplay)
	{
		display = new LevelDisplay(player, cDisplay);
		update = new levelUpdate(playerUpdate, cUpdate, lDisplay);
	}

	virtual ~Level() {}

	void input(SDL_Event _event);
	void print(SDL_Window* window);
	void init();
};