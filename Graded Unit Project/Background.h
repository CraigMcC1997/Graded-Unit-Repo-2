#pragma once
#include "drawableEntity.h"
#include "loadTexture.h"

class Background : public DrawableEntity {
private:
	glm::vec3 position;	//use for passing in position
	GLuint texture;
	std::stack<glm::mat4> *_mvStack;

	//Shader* shader;
	//Model* myModel;
	//Camera* camera;

public:
	Background() {}
	void init();
	void update(SDL_Event _event);
	void draw(SDL_Window* window);
	void Set_ShaderID(GLuint _id);
	void getStack(std::stack<glm::mat4>* stack);
};