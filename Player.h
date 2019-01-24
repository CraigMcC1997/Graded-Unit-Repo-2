#pragma once
#include <glm/glm.hpp>

class Player 
{

private:
	glm::vec3 playerPos;	//player position
	PlayerDisplay* display;
	bool done = false, allowJumpSound = true, doJump = false;	//	booleans for sound code

public:
	void init();
	void update(SDL_Event _event);
	void display();

	glm::vec3 getPlayerPos();
	void setPlayerPos(glm::vec3 pos);
};