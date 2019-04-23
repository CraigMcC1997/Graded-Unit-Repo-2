#pragma once
#include "Entity.h"

//	#########################################
//	Used for drawing boxes in the opening
//	window which will be used as buttons
//	#########################################

class Box : public Entity
{
private:
	glm::vec3 position;
	glm::vec3 scale;
	GLuint texture;

public:
	Box(GLuint texture) : texture(texture) {}

	void init();
	void update();
	void draw(SDL_Window* window);
	glm::vec3 getCollisionBox();
	glm::vec3 getPosition();

	glm::vec3 getScale();

	void setPosition(glm::vec3);
	void setScale(glm::vec3);
};

