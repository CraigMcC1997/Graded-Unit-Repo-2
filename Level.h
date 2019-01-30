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

	static const GLuint MAX_PLATFORMS = 4;	//	number of platforms
	static const GLuint MAX_OBJECTS = 2;
	const char* name[10];
	drawObject* object[MAX_OBJECTS];
	platform* _platform[MAX_PLATFORMS];	//	array of platforms
	glm::vec3 position[MAX_PLATFORMS];	//	array of positions
	glm::vec3 platformPos = glm::vec3(0.0f, -0.1f, 0.0f);

public:
	Level() {}
	void update(SDL_Event _event);
	void display(SDL_Window* window);
	void init();
};