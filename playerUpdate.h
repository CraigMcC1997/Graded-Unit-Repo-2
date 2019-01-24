#pragma once
#include "AbstractUpdate.h"
#include "Move.h"
#include "PlayerDisplay.h"
#include "PlaySound.h"

using namespace std;

class playerUpdate : public AbstractUpdate
{
private:


public:
	playerUpdate(PlayerDisplay* display) : display(display) {}
	void update(SDL_Event _event);
	void init();
};