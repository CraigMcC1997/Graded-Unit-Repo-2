#pragma once
#include <glm/glm.hpp>
#include "loadTexture.h"
#include "Move.h"
#include "PlaySound.h"
#include "drawableEntity.h"
#include "Model.h"
#include "Camera.h"

class Player : public DrawableEntity
{
private:
	glm::vec3 playerPos;	//player position
	bool done = false, allowJumpSound = true, doJump = false;
	HSAMPLE *samples = NULL;	//Used by BASS library
	GLfloat rotationValue;
	Shader* shader;
	Model* myModel;
	Camera* camera;

	glm::mat4x4 model;

public:
	Player() {}
	void init();
	glm::vec3 getPlayerPos();
	void setPlayerPos(glm::vec3 pos);

	void update(SDL_Event _event);
	void draw(SDL_Window* window);
};