#pragma once
#include "Entity.h"

class Projectile : public Entity
{
private:
	glm::vec3 position;
	GLfloat rotate = 0.0f;
	GLfloat spin = 0.0f;
public:
	Projectile() {}

	void init();
	void update();
	void draw(SDL_Window*);
	glm::vec3 getPosition();
	glm::vec3 getCollisionBox();

	void setPosition(glm::vec3);
};

