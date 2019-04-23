#include "OpeningWindow.h"

void OpeningWindow::init()
{		
	//shader
	shaderProgram = rt3d::initShaders("../Resources/Shaders/phong.vert", "../Resources/Shaders/phong.frag");
	rt3d::setLight(shaderProgram, light0);
	rt3d::setMaterial(shaderProgram, material0);

	textures[0] = loadTexture::loadTextures("../Resources/Textures/Main-menu.bmp");
	textures[1] = loadTexture::loadTextures("../Resources/Textures/Play_Button.png");
	textures[2] = loadTexture::loadTextures("../Resources/Textures/Options_Button.png");
	textures[3] = loadTexture::loadTextures("../Resources/Textures/Quit_Button.png");
	textures[4] = loadTexture::loadTextures("../Resources/Textures/arrow.png");
	textures[5] = loadTexture::loadTextures("../Resources/Textures/Fullscreen_Button.png");
	textures[6] = loadTexture::loadTextures("../Resources/Textures/Windowed_Button.png");

	background = new Box(textures[0]);
	background->init();
	background->setPosition(glm::vec3(0.0f, 8.0f, 0.0f));
	background->setScale(glm::vec3(13.0f, 12.0f, 13.0f));

	buttonPos[1] = glm::vec3(-4.0f, 14.0f, 8.0f);
	buttonPos[2] = glm::vec3(-4.0f, 9.5f, 8.0f);
	buttonPos[3] = glm::vec3(-4.0f, 5.0f, 8.0f);


	for (int i = 1; i <= MAX_BUTTONS; i++)
	{
		box[i] = new Box(textures[i]);
		box[i]->init();
		box[i]->setPosition(buttonPos[i]);
	}

	box[1]->setScale(glm::vec3(3.0f, 2.0f, 11.0f));
	box[2]->setScale(glm::vec3(3.0f, 2.0f, 11.0f));
	box[3]->setScale(glm::vec3(3.0f, 2.0f, 11.0f));
	box[4]->setScale(glm::vec3(1.0f, 1.0f, 11.1f));

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void OpeningWindow::findController()
{
	int attempts = 0;

	do {
		attempts++;
		printf("%i joysticks were found.\n\n", SDL_NumJoysticks());
	} while ((SDL_NumJoysticks() < 0) || attempts <= 0);

	
	if (SDL_NumJoysticks() > 0)
		gamePad = SDL_GameControllerOpen(0);

	foundController = false;
}

glm::vec2 OpeningWindow::getPos()
{
	return glm::vec2(horizontal, vertical);
}

// Get the horizontal and vertical screen sizes in pixel
void OpeningWindow::GetDesktopResolution(int& horizontal, int& vertical)
{
	RECT desktop;
	// Get a handle to the desktop window
	const HWND hDesktop = GetDesktopWindow();
	// Get the size of screen to the variable desktop
	GetWindowRect(hDesktop, &desktop);
	// The top left corner will have coordinates (0,0)
	// and the bottom right corner will have coordinates
	// (horizontal, vertical)
	horizontal = desktop.right;
	vertical = desktop.bottom;
}

void OpeningWindow::play()
{
	//play game
	running = true;
	runOpening = false;
}

void OpeningWindow::options()
{
	optionsActive = true;

	for (int i = 0; i <= MAX_OPTIONS_BUTTONS; i++)
	{
		optionsButtons[i] = new Box(textures[i+5]);
		optionsButtons[i]->init();
		optionsButtons[i]->setPosition(buttonPos[i+1]);
		optionsButtons[i]->setScale(glm::vec3(3.0f, 2.0f, 11.0f));
	}		
}

void OpeningWindow::quit()
{
	//close program
	running = false; 
	runOpening = false;
}

bool OpeningWindow::getRunning()
{
	return running;
}

void OpeningWindow::setRunning(bool newRunning)
{
	running = newRunning;
}

void OpeningWindow::update()
{
	const Uint8 *keys = SDL_GetKeyboardState(NULL);
	
	if(foundController)
		findController();

	if (keys[SDL_SCANCODE_DOWN] || SDL_GameControllerGetButton(gamePad, SDL_CONTROLLER_BUTTON_DPAD_DOWN))
	{
		//move down
		if (!pressed)
		{
			if (!optionsActive)
			{
				//highlight option 1 down
				if (currentPos <= 3 && currentPos >= 1)
					currentPos++;
			}
			else
			{
				//highlight option 1 down
				if (currentPos <= 2 && currentPos >= 1)
					currentPos++;
			}

			pressed = true;
		}
	}

	if (keys[SDL_SCANCODE_UP] || SDL_GameControllerGetButton(gamePad, SDL_CONTROLLER_BUTTON_DPAD_UP))
	{
		if (!pressed)
		{
			if (!optionsActive)
			{
				//highlight option 1 down
				if (currentPos <= 3 && currentPos >= 1)
					currentPos--;
			}
			else
			{
				//highlight option 1 down
				if (currentPos <= 2 && currentPos >= 1)
					currentPos--;
			}
			pressed = true;
		}
	}

	if (keys[SDL_SCANCODE_RETURN] || SDL_GameControllerGetButton(gamePad, SDL_CONTROLLER_BUTTON_A))
	{
		//select
		if (!pressed)
		{
			if (!optionsActive)
			{
				//Chose the highlighted options
				switch (currentPos)
				{
				case 1:
					play();
					break;
				case 2:
					options();
					break;
				case 3:
					quit();
					break;
				}
			}
			else
			{
				//Chose the highlighted options
				switch (currentPos)
				{
				case 1:
				{
					//make full screen
					GetDesktopResolution(horizontal, vertical);
				}
					break;
				case 2:
					break;
				}

				optionsActive = false;
			}

			pressed = true;
		}
	}

	if (!optionsActive)
	{
		//keeps position within range
		if (currentPos < 1)
		{
			currentPos = 3;
		}

		if (currentPos > 3)
		{
			currentPos = 1;
		}
	}
	else
	{
		//keeps position within range
		if (currentPos < 1)
		{
			currentPos = 2;
		}

		if (currentPos > 2)
		{
			currentPos = 1;
		}
	}

	box[4]->setPosition(glm::vec3(buttonPos[currentPos].x + 2.0f,
		buttonPos[currentPos].y, buttonPos[currentPos].z - 4.5f));

	if (!keys[SDL_SCANCODE_DOWN] && !keys[SDL_SCANCODE_UP] && !keys[SDL_SCANCODE_RETURN]
		&& !SDL_GameControllerGetButton(gamePad, SDL_CONTROLLER_BUTTON_A)
		&& !SDL_GameControllerGetButton(gamePad, SDL_CONTROLLER_BUTTON_DPAD_UP)
		&& !SDL_GameControllerGetButton(gamePad, SDL_CONTROLLER_BUTTON_DPAD_DOWN))
	{
		pressed = false;
	}
}

void OpeningWindow::draw(SDL_Window* window)
{
	glEnable(GL_CULL_FACE);
	glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::mat4 projection(1.0f);
	glm::mat4 modelview(1.0);
	mvStack.push(modelview);
	projection = glm::perspective(glm::radians(60.0f), 800.0f / 600.0f, 1.0f, 50.0f);
	rt3d::setUniformMatrix4fv(shaderProgram, "projection", glm::value_ptr(projection));

	camera::setAt(Move::moveForward(camera::getEye(), Move::getRotation(), 1.0f));
	mvStack.top() = glm::lookAt(camera::getEye(), camera::getAt(), camera::getUp());

	background->draw(window);

	if (!optionsActive)
	{
		for (int i = 1; i < MAX_BUTTONS; i++)
		{
			box[i]->draw(window);
		}
	}
	else
	{
		for (int i = 0; i < MAX_OPTIONS_BUTTONS; i++)
		{
			optionsButtons[i]->draw(window);
		}

		box[4]->draw(window);
	}

	SDL_GL_SwapWindow(window); // swap buffers
}