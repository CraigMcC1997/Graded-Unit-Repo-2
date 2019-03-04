#include "Player.h"

using namespace std;

void Player::init()
{
	camera = new Camera(glm::vec3(0.0f, 0.0f, -3.0f));
	playerPos = glm::vec3(3.0f, 2.0f, -12.0f);	//initialising players starting position

	//Initialize default output device
	if (!BASS_Init(-1, 44100, 0, 0, NULL))
		cout << "Can't initialize device";

	samples = new HSAMPLE[5];	//array of sound  files
	samples[0] = Sound::loadSample("../Resources/SoundFiles/jump.wav");	//adding sound files to the array to be played later in code

	shader = new Shader("../Resources/Shaders/phong.vert", "../Resources/Shaders/phong.frag");
	myModel = new Model("../Resources/MODEL.obj");	//loading player model
	shader->Use();

	texture[0] = loadTexture::loadTextures("../Resources/fabric.bmp");

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void Player::update(SDL_Event _event)
{
	playerPos = move::grav(playerPos);

	const Uint8 *keys = SDL_GetKeyboardState(NULL);
	if (keys[SDL_SCANCODE_W]) {
		playerPos = move::moveRight(playerPos, move::getRotation(), 0.10f);
		rotationValue = 0.0f;
	}

	if (keys[SDL_SCANCODE_S]) {
		playerPos = move::moveRight(playerPos, move::getRotation(), -0.10f);
		rotationValue = 180.0f;
	}

	if (keys[SDL_SCANCODE_X])
	{
		if (allowJumpSound)
		{
			Sound::playSample(samples[0]);
			cout << "sound played" << endl;
			allowJumpSound = false;
		}
	}
	else
		allowJumpSound = true;

	if (keys[SDL_SCANCODE_SPACE]) {
		doJump = true;
	}
	else
		if (playerPos.y <= 0.0f)
		{
			move::resetV();
			doJump = false;
		}

	if (doJump)
	{
		playerPos.y += move::jump();
		cout << "JUMPING" << endl;
	}

	if (playerPos.y <= 0.0f)
		playerPos.y = 0.0f;
}

void Player::draw(SDL_Window* window)
{
	glm::mat4 projection(1.0); // creating the projection matrix
	projection = glm::perspective(float(glm::radians(60.0f)), 800.0f / 600.0f, 1.0f, 150.0f); //setting up perspective
	rt3d::setUniformMatrix4fv(shaderProgram, "projection", glm::value_ptr(projection));

	//assimp stuf
	glm::mat4 view = camera->GetViewMatrix();
	glUniformMatrix4fv(glGetUniformLocation(shader->Program, "projection"),
		1, GL_FALSE, glm::value_ptr(projection));
	glUniformMatrix4fv(glGetUniformLocation(shader->Program, "view"),
		1, GL_FALSE, glm::value_ptr(view));

	glm::mat4x4 model;
	model = glm::translate(model, glm::vec3(playerPos));
	model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
	glUniformMatrix4fv(glGetUniformLocation(shader->Program, "model"),
		1, GL_FALSE, glm::value_ptr(model));
	myModel->Draw(*shader);

	// remember to use at least one pop operation per push...
	glDepthMask(GL_TRUE);
	SDL_GL_SwapWindow(window); // swap buffers
}

glm::vec3 Player::getPlayerPos()
{
	return playerPos;
}

void Player::setPlayerPos(glm::vec3 pos)
{
	playerPos = pos;
}