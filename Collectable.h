#pragma once
#include "AbstractDisplay.h"
#include "loadTexture.h"

class Collectable : public AbstractDisplay
{
private:
	glm::vec3 collectablePos;
public:
	void init();
	void update(SDL_Event _event);
	void display(SDL_Window* window);
};
