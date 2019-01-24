#pragma once
#include "AbstractDisplay.h"
#include "loadTexture.h"
#include "Window.h"
#include "PlayerDisplay.h"
#include "playerUpdate.h"
#include "Platform.h"
#include "CollectableDisplay.h"
#include "DrawObject.h"

class LevelDisplay : public AbstractDisplay
{
private:
	PlayerDisplay* player;
	playerUpdate* playerUp;
	CollectableDisplay* collectableDisplay;
	const char* name[10];
	drawObject* object[10];
	platform* _platform[4];	//	array of platforms
	glm::vec3 position[4];	//	array of positions

	const GLuint MAX_PLATFORMS = 3;	//	number of platforms
	const GLuint MAX_OBJECTS = 1;

public:
	LevelDisplay(PlayerDisplay* player, CollectableDisplay* collectableDisplay) : player(player), collectableDisplay(collectableDisplay) {}
	glm::vec3 platformPos = glm::vec3(0.0f, -0.1f, 0.0f);
	void print(SDL_Window* window);
	void init();
};