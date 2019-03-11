#pragma once
#include "Entity.h"

using namespace std;

class DrawableEntity : public Entity
{
protected:
	GLuint shaderProgram;						//	Phong Shader
	GLuint size;
	GLuint texture[5];


public:
	virtual void update(SDL_Event _event) = 0;
	virtual void draw(SDL_Window* window) = 0;
};