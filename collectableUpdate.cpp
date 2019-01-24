#include "collectableUpdate.h"


void collectableUpdate::update(SDL_Event _event)
{
	if (pDisplay->playerPos.x == cDisplay->collectablePos.x)
	{
		if (pDisplay->playerPos.z == cDisplay->collectablePos.z)
		{
			cout << "collision" << endl;
			cDisplay->collectablePos.x = 20.0f;
		}
	}
}