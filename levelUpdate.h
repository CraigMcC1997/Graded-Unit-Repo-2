#pragma once
#include "AbstractUpdate.h"
#include "playerUpdate.h"
#include "collectableUpdate.h"
#include "LevelDisplay.h"

class levelUpdate : public AbstractUpdate
{
private:
	playerUpdate* player;
	collectableUpdate* cUpdate;
	LevelDisplay* lDisplay;
public:
	levelUpdate(playerUpdate* player, collectableUpdate* cUpdate, LevelDisplay* lDisplay) : player(player), cUpdate(cUpdate), lDisplay(lDisplay) {}
	void update(SDL_Event _event);
};
