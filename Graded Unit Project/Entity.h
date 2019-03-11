#pragma once

#include <SDL.h>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>
#include <stack>

class Entity
{
protected:

public:
	virtual void init(void) = 0;
	virtual void update(SDL_Event _event) = 0;
	virtual void draw(SDL_Window* window) = 0;
};