#pragma once
#include <glm/glm.hpp>
#include "AbstractDisplay.h"
#include "loadTexture.h"
#include "Move.h"
#include "PlaySound.h"
#include "AbstractDisplay.h"

class Player : public AbstractDisplay
{
private:
	glm::vec3 playerPos;	//player position
	bool done = false, allowJumpSound = true, doJump = false;	//	booleans for sound code

public:
	Player() {}
	void init();
	void update(SDL_Event _event);
	void display(SDL_Window* window);

	glm::vec3 getPlayerPos();
	void setPlayerPos(glm::vec3 pos);
};