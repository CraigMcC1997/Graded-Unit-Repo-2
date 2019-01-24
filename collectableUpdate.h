#pragma once
#include "AbstractUpdate.h"
#include "PlayerDisplay.h"
#include "LevelDisplay.h"
#include "CollectableDisplay.h"
#include "player.h"

class collectableUpdate : public AbstractUpdate
{
private:
	PlayerDisplay* pDisplay;
	LevelDisplay* lDisplay;
	CollectableDisplay* cDisplay;
	Player* player;
public:
	collectableUpdate(PlayerDisplay* pDisplay, CollectableDisplay* cDisplay, LevelDisplay* lDisplay) : pDisplay(pDisplay), cDisplay(cDisplay), lDisplay(lDisplay) {}
	void update(SDL_Event _event);
};
