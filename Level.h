#pragma once
#include "AbstractLevel.h"
#include "Window.h"
#include "Player.h"
#include "Collectable.h"
#include "DrawObject.h"
#include "Platform.h"

class Level : public AbstractDisplay
{
private:
	Player* player = new Player();
	Collectable* collectable = new Collectable();

	const char* name[10];
	drawObject* object[10];
	platform* _platform[4];	//	array of platforms
	glm::vec3 position[4];	//	array of positions
	const GLuint MAX_PLATFORMS = 3;	//	number of platforms
	const GLuint MAX_OBJECTS = 1;
	glm::vec3 platformPos = glm::vec3(0.0f, -0.1f, 0.0f);

public:
	Level() {}
	void update(SDL_Event _event);
	void display(SDL_Window* window);
	void init();
};