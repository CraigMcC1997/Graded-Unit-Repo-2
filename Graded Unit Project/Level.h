#pragma once
#include "AbstractLevel.h"
#include "Window.h"
#include "Player.h"
#include "Collectable.h"
#include "DrawObject.h"
#include "Platform.h"
#include "Background.h"
#include "Model.h"
#include "Camera.h"

class Level : public AbstractDisplay
{
private:
	Player* player = new Player();
	Collectable* collectable = new Collectable();
	Background* background = new Background();
	Shader* shader;
	Model* myModel;
	Camera* camera;

	static const GLuint MAX_PLATFORMS = 5;	//	number of platforms
	static const GLuint MAX_OBJECTS = 2;
	const char* name[10];
	GLuint texture[5];							//	array of textures
	drawObject* object[MAX_OBJECTS];
	platform* _platform[MAX_PLATFORMS];	//	array of platforms
	glm::vec3 position[MAX_PLATFORMS];	//	array of positions
	glm::vec3 scale[MAX_PLATFORMS];

public:
	Level() {}
	void update(SDL_Event _event);
	void display(SDL_Window* window);
	void init();
};