#pragma once
#include "Entity.h"
class Tree : public Entity
{
public:
	void init();
	void update();
	void draw(SDL_Window* window);
	glm::vec3 getCollisionBox();
	glm::vec3 getPosition();
};