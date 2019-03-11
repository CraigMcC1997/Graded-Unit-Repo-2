#pragma once
#include "loadTexture.h"
#include "drawableEntity.h"
#include "Model.h"
#include "Camera.h"

class Collectable : public DrawableEntity
{
private:
	glm::vec3 collectablePos;
	GLfloat rotationValue = -1.0f;

	Shader* shader;
	Model* myModel;
	Camera* camera;

public:
	Collectable() {}
	void init();
	void update(SDL_Event _event);
	void draw(SDL_Window* window);
};
