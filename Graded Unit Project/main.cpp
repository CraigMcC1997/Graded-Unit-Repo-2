#include <SDL.h> 
#include "Level.h"
#include "Window.h"
#include <iostream>

using namespace std;

bool handleSDLEvent(SDL_Event const &sdlEvent)
{
	if (sdlEvent.type == SDL_QUIT)
		return false;
	if (sdlEvent.type == SDL_KEYDOWN)
	{
		// Can extend this to handle a wider range of keys
		switch (sdlEvent.key.keysym.sym)
		{
		case SDLK_ESCAPE:
			return false;
		default:
			break;
		}
	}
	return true;
}

void exitFatalError(char *message)
{
	cout << message << " " << endl;
	cout << SDL_GetError();
	SDL_Quit();
	exit(1);
}

// Program entry point - SDL manages the actual WinMain entry point for us
int main(int argc, char *argv[])
{
	SDL_GLContext glContext; // OpenGL context handle
	Window* hWindow = new Window (800, 600, "Graded Unit Project"); // window handle
	
	Level* level = new Level();

	hWindow->setupRC(glContext);
	SDL_Renderer *renderTarget = nullptr;
	renderTarget = SDL_CreateRenderer(hWindow->getWindow(), -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	glewExperimental = GL_TRUE;
	GLenum err = glewInit();
	if (GLEW_OK != err) { // glewInit failed, something is seriously wrong
		std::cout << "glewInit failed, aborting." << endl;
		exit(1);
	}
	cout << glGetString(GL_VERSION) << endl;
	
	level->init();

	SDL_Event sdlEvent;	// variable to detect SDL events
	bool running = true;
	while (running) {	// the event loop
		while (SDL_PollEvent(&sdlEvent))
		{
			if (sdlEvent.type == SDL_QUIT)
				running = false;
		}
		level->update(sdlEvent);
		level->display(hWindow->getWindow()); // call the draw function
	}

	SDL_DestroyWindow(hWindow->getWindow());
	SDL_Quit();
	return 0;
}