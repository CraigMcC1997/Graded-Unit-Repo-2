//	#########################################
//	A class for holding all of the players
//	information, variables & functions
//	#########################################

#pragma once
#include "Entity.h"
#include "PlaySound.h"
#include "Collision.h"
#include "md2model.h"

class Player : public Entity
{
private:
	bool allowJumpSound = true, allowDamage = true;
	bool noPlatformCollision = true, jumping = false, noEnemyCollision = true, noProjectileCollision = true;
	HSAMPLE *samples = NULL;
	glm::vec3 position = glm::vec3(-3.0f, 5.0f, 0.0f);
	int playerLives = 5;
	GLfloat rotate = 90.0f;
	glm::vec3 scale = glm::vec3(0.1f, 0.1f, 0.1f);
	glm::vec3 chekPointPos;
	int collectablesFound = 0;
	TTF_Font* font;
	glm::vec3 camPos = camera::getEye();
	
	// Current Animaiton Intializer That Sets The Players Current Animation To Idle.
	md2model tmpModel; // Initializes The Model For The Player
	int currentAnimation = 0;

public:
	Player() {}
	void init();
	void update();
	void draw(SDL_Window* window);
	void setPlayerPosition(glm::vec3);
	glm::vec3 getPosition();
	void setPlayerRotate(GLfloat);
	glm::vec3 getScale();
	void setJump(bool);
	void takeDamage();
	void setCheckPoint(glm::vec3);
	bool getAllowDamage();
	void setAllowDamage(bool);
	int getCollectablesFound();
	void addCollectable();
	glm::vec3 getCollisionBox();
	bool getPlatformCollision();
	bool getEnemyCollision();
	bool getProjectileCollision();
	bool getJumping();

	void setPlatformCollision(bool);
	void setEnemyCollision(bool);
	void setProjectileCollision(bool);
	void setJumping(bool);
};