#pragma once
#include "Entity.h"

class Basic_Enemy : public Entity
{
private:
	glm::vec3 position;
	GLfloat rotate = 0.0f;
	glm::vec3 scale = glm::vec3(1.0f, 1.0f, 1.0f);
	glm::vec3 minRange;
	glm::vec3 maxRange;
	bool flag = true;
	float velocity = 0.125f;

public:
	Basic_Enemy() {}
	void init();
	void update();
	void draw(SDL_Window* window);
	glm::vec3 getPosition();
	glm::vec3 getCollisionBox();

	void setEnemyPosition(glm::vec3);
	void setMinRange(glm::vec3);
	void setMaxRange(glm::vec3);
	
	void setEnemyRotate(GLfloat);
	glm::vec3 getScale();
};