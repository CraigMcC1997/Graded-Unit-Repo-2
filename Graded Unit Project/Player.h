#pragma once
#include <glm/glm.hpp>
#include "loadTexture.h"
#include "Move.h"
#include "PlaySound.h"
#include "drawableEntity.h"

class Player : public DrawableEntity
{
private:
	glm::vec3 playerPos = glm::vec3(1.0f, 1.0f, -20.0f);
	bool done = false, allowJumpSound = true, doJump = false;
	HSAMPLE *samples = NULL;	//Used by BASS library
	GLfloat rotationValue;

public:
	Player() {};
	void init();
	glm::vec3 getPlayerPos();
	void setPlayerPos(glm::vec3 pos);

	void update(SDL_Event _event);
	void draw(SDL_Window* window);
};