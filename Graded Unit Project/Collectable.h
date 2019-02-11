#pragma once
#include "loadTexture.h"
#include "drawableEntity.h"

class Collectable : public DrawableEntity
{
private:
	glm::vec3 collectablePos;
	GLfloat rotationValue = - 1.0f;

public:
	Collectable() {}
	void init();
	void update(SDL_Event _event);
	void draw(SDL_Window* window);
};
