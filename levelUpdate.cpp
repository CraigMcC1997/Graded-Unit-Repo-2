#include "levelUpdate.h"

void levelUpdate::update(SDL_Event _event)
{
	player->update(_event);
	cUpdate->update(_event);
}