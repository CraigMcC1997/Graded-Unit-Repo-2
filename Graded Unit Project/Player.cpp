#include "Player.h"

using namespace std;

void Player::init()
{
	playerPos = glm::vec3(3.0f, 2.0f, -12.0f);	//initialising players starting position

	//Initialize default output device
	if (!BASS_Init(-1, 44100, 0, 0, NULL))
		cout << "Can't initialize device";

	samples = new HSAMPLE[5];	//array of sound  files
	samples[0] = Sound::loadSample("../Resources/SoundFiles/jump.wav");	//adding sound files to the array to be played later in code

	shaderProgram = rt3d::initShaders("../Resources/Shaders/phong.vert", "../Resources/Shaders/phong.frag");
	rt3d::setLight(shaderProgram, light);
	rt3d::setMaterial(shaderProgram, material);

	lightPos = glm::vec4(-10.0f, 10.0f, 10.0f, 1.0f);	//initialising world light position

	rt3d::loadObj("../Resources/MODEL.obj", verts, norms, tex_coords, indices);	//loading player model
	size = indices.size();
	meshIndexCount = size;
	meshObjects[1] = rt3d::createMesh(verts.size() / 3, verts.data(), nullptr, norms.data(), tex_coords.data(), size, indices.data());

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
	GLfloat scale(1.0f); //used for scaling models & objects
	glm::mat4 modelview(1.0); // set base position for scene //creating the modelview matrix
	mvStack.push(modelview); // first push
	at = move::moveForward(eye, move::getRotation(), 1.0f);
	mvStack.top() = glm::lookAt(eye, at, up); //pushing camera to top of stack

	glUseProgram(shaderProgram);

	glm::vec4 tmp = mvStack.top()*lightPos;
	light.position[0] = tmp.x;
	light.position[1] = tmp.y;
	light.position[2] = tmp.z;

	rt3d::setLightPos(shaderProgram, glm::value_ptr(tmp));
	rt3d::setUniformMatrix4fv(shaderProgram, "projection", glm::value_ptr(projection));

	// drawing player model
	glBindTexture(GL_TEXTURE_2D, texture[0]);
	mvStack.push(mvStack.top());
	mvStack.top() = glm::translate(mvStack.top(), glm::vec3(playerPos.x, playerPos.y, playerPos.z));
	mvStack.top() = glm::scale(mvStack.top(), glm::vec3(scale*0.5f, scale*0.5f, scale*0.5f));
	mvStack.top() = glm::rotate(mvStack.top(), glm::radians(0.0f), glm::vec3(-1.0f, 0.0f, 0.0f));
	mvStack.top() = glm::rotate(mvStack.top(), -glm::radians(rotationValue), glm::vec3(0.0f, 1.0f, 0.0f));
	rt3d::setUniformMatrix4fv(shaderProgram, "modelview", glm::value_ptr(mvStack.top()));
	rt3d::setMaterial(shaderProgram, material);
	rt3d::drawIndexedMesh(meshObjects[1], meshIndexCount, GL_TRIANGLES);
	mvStack.pop();

	// remember to use at least one pop operation per push...
	mvStack.pop(); // initial matrix
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