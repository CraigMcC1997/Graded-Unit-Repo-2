#pragma once
#include "Entity.h"
#include "Projectile.h"

class Projectile_Enemy : public Entity
{
private:
	Projectile* projectile = new Projectile();
	GLfloat rotate = 0.0f;
	glm::vec3 position;
	
	glm::vec3 scale = glm::vec3(1.0f, 1.0f, 1.0f);
	glm::vec3 minRange;
	glm::vec3 maxRange;
	bool flag = true, choseRotate = false;
	float velocity = 0.125f;	

public:
	Projectile_Enemy() {}
	void init();
	void update();
	void draw(SDL_Window*);
	glm::vec3 getCollisionBox();

	void setEnemyPosition(glm::vec3);
	void setMinRange(glm::vec3);
	void setMaxRange(glm::vec3);
	glm::vec3 getPosition();
	void setEnemyRotate(GLfloat);
	glm::vec3 getScale();
	void shoot();
	void stopShooting();
	Projectile* getProjectile();
	bool bulletActive = false;
};

