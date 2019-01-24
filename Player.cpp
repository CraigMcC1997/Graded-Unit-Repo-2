#include "Player.h"

using namespace std;

//code below
HSAMPLE *samples = NULL;	//Used by BASS library

void Player::init()
{
	playerPos = glm::vec3(3.0f, 2.0f, -12.0f);

	//Initialize default output device
	if (!BASS_Init(-1, 44100, 0, 0, NULL))
		cout << "Can't initialize device";

	//array of sound  files
	samples = new HSAMPLE[5];

	//adding sound files to the array to be played later in code
	samples[0] = Sound::loadSample("../SoundFiles/jump.wav");
}

void Player::update(SDL_Event _event)
{
	player->playerPos = move::grav(player->playerPos);

	const Uint8 *keys = SDL_GetKeyboardState(NULL);
	if (keys[SDL_SCANCODE_W]) {
		display->playerPos = move::moveRight(display->playerPos, move::getRotation(), 0.10f);
		display->rotationValue = 0.0f;
	}

	if (keys[SDL_SCANCODE_S]) {
		display->playerPos = move::moveRight(display->playerPos, move::getRotation(), -0.10f);
		display->rotationValue = 180.0f;
	}

	if (keys[SDL_SCANCODE_X])
	{
		if (allowJumpSound)
		{
			Sound::playSample(samples[0]);
			allowJumpSound = false;
		}
	}
	else
		allowJumpSound = true;

	if (keys[SDL_SCANCODE_SPACE]) {
		cout << "JUMPING" << endl;
		doJump = true;
	}
	else
		if (display->playerPos.y <= 0.0f)
		{
			move::resetV();
			doJump = false;
		}

	if (doJump)
		display->playerPos.y += move::jump();

	if (keys[SDL_SCANCODE_R]) {
		cout << "R" << endl;
	}
	if (keys[SDL_SCANCODE_F]) {
		cout << "F" << endl;
	}

	if (display->playerPos.y <= 0.0f)
		display->playerPos.y = 0.0f;
}

void Player::display()
{

}

glm::vec3 Player::getPlayerPos()
{
	return playerPos;
}

void Player::setPlayerPos(glm::vec3 pos)
{
	playerPos = pos;
}