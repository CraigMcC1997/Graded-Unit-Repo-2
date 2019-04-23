#pragma once
#include "Entity.h"

//	#########################################
//	A flag used throughout the game for 
//	different purposes
//	#########################################

class EndPoint : public Entity
{
private:
	glm::vec3 position;
	glm::vec3 scale = glm::vec3(1.0f, 3.0f, 1.0f);
	int flagType;

public:
	EndPoint(int flagType) : flagType(flagType)  {}

	void init();
	void update();
	void draw(SDL_Window* window);
	glm::vec3 getPosition();
	glm::vec3 getCollisionBox();

	glm::vec3 getScale();

	void setPosition(glm::vec3);
};

