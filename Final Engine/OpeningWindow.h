//	#########################################
//	opening window which displays before
//	the main game displays.
//	Allows player to chose window size
//	#########################################

#pragma once

#include "Box.h"
#include "AbstractDisplay.h"
#include <iostream>
#include <wtypes.h>
#include "GL/GL.h"

using namespace std;

class OpeningWindow : public AbstractDisplay
{
private:
	Box* background;
	enum { MAX_OPTIONS_BUTTONS = 2 };
	Box* optionsButtons[MAX_OPTIONS_BUTTONS];
	glm::vec3 optionsButtonPos[MAX_OPTIONS_BUTTONS];

	enum { MAX_BUTTONS = 5 };
	Box* box[MAX_BUTTONS];
	glm::vec3 buttonPos[MAX_BUTTONS];
	int currentPos = 1;

	GLuint textures[10];
	bool pressed = false;
	bool running = false; // set running to true if play, false if quit
	bool optionsActive = false;
	int horizontal = 800;
	int vertical = 600;

	SDL_GameController* gamePad = NULL;
	bool foundController = true;

public:
	OpeningWindow() {}

	void init();
	void update();
	void draw(SDL_Window* window);

	void GetDesktopResolution(int& horizontal, int& vertical);
	void play();
	void options();
	void quit();
	void findController();

	glm::vec2 getPos();
	bool getRunning();
	void setRunning(bool);

	bool runOpening = true;
};

