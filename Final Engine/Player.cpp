#include "Player.h"

void Player::init()
{
	chekPointPos = position;

	printf("%i joysticks were found.\n\n", SDL_NumJoysticks());

	gamePad = SDL_GameControllerOpen(0);

	//starting the array of labels
	labels[0] = 0;

	if (TTF_Init() < 0) {
		printf("font error");
	}
	font = TTF_OpenFont("../Resources/Fonts/GoodTimes.ttf", 50);

	samples = new HSAMPLE[5];	//array of sound  files
	samples[0] = Sound::loadSample("../Resources/SoundFiles/jump.wav", BASS_SAMPLE_OVER_POS);	//adding sound files to the array to be played later in code
	samples[1] = Sound::loadSample("../Resources/SoundFiles/Damage.wav", BASS_SAMPLE_OVER_POS);
	samples[2] = Sound::loadSample("../Resources/SoundFiles/death.wav", BASS_SAMPLE_OVER_POS);

	//shader
	shaderProgram = rt3d::initShaders("../Resources/Shaders/phong.vert", "../Resources/Shaders/phong.frag");
	rt3d::setLight(shaderProgram, light0);
	rt3d::setMaterial(shaderProgram, material1);

	//model loading
	textures[1] = loadTexture::loadTextures("../Resources/Textures/hobgoblin2.bmp");
	meshObjects[1] = tmpModel.ReadMD2Model("../Resources/3D_Objects/tris.MD2");
	md2VertCount = tmpModel.getVertDataCount();

	//model loading
	rt3d::loadObj("../Resources/3D_Objects/cube.obj", verts, norms, tex_coords, indices);
	meshIndexCount[1] = indices.size();
	meshObjects[1] = rt3d::createMesh(verts.size() / 3, verts.data(), nullptr, norms.data(), tex_coords.data(),
		meshIndexCount[1], indices.data());
	verts.clear(), norms.clear(), tex_coords.clear(), indices.clear();

	collisionBox = glm::vec3(1, 1, 1);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void Player::setPlayerPosition(glm::vec3 newPosition)
{
	position = newPosition;
}

glm::vec3 Player::getPosition()
{
	return position;
}

void Player::setPlayerRotate(GLfloat newRotate)
{
	rotate = newRotate;
}

glm::vec3 Player::getScale()
{
	return scale;
}

void Player::takeDamage()
{
	//reset lives count
	playerLives--;
	Sound::playSample(samples[1]);
}

void Player::setJump(bool setJump)
{
	jumping = setJump;
}

void Player::setCheckPoint(glm::vec3 checkpoint)
{
	chekPointPos = checkpoint;
}

bool Player::getAllowDamage()
{
	return allowDamage;
}

void Player::setAllowDamage(bool setdamage)
{
	allowDamage = setdamage;
}

int Player::getCollectablesFound()
{
	return collectablesFound;
}

void Player::addCollectable()
{
	collectablesFound++;
}

glm::vec3 Player::getCollisionBox()
{
	return collisionBox;
}

void Player::update()
{
	const Uint8 *keys = SDL_GetKeyboardState(NULL);
	setPlayerPosition(Move::grav(getPosition()));

	if (position.z < camPos.z - 3)
	{
		if (camPos.z != position.z)
			camPos.z -= 0.2;
		else
			camPos.z = position.z;

		camera::setEye(camPos);
	}

	currentAnimation = 0;

	if (position.z > camPos.z + 3)
	{
		if (camera::getEye().z != position.z)
			camPos.z += 0.2;
		else
			camPos.z = position.z;

		camera::setEye(camPos);
	}
	
	if (position.z > camPos.z + 4 || position.z < camPos.z - 4)
	{
		camPos.z = position.z;
	}

	camPos.y = position.y + 9.0f;
	camera::setEye(camPos);


	if (keys[SDL_SCANCODE_D] || SDL_GameControllerGetButton(gamePad, SDL_CONTROLLER_BUTTON_DPAD_RIGHT)) {
		setPlayerPosition(Move::moveZ(position, Move::getRotation(), 0.2));
		setPlayerRotate(90.0f);
		currentAnimation = 1;
	}

	if (keys[SDL_SCANCODE_A] || SDL_GameControllerGetButton(gamePad, SDL_CONTROLLER_BUTTON_DPAD_LEFT)) {
		setPlayerPosition(Move::moveZ(position, Move::getRotation(), -0.2));
		setPlayerRotate(-90.0f);
		currentAnimation = 1;
	}

	if (keys[SDL_SCANCODE_SPACE] || SDL_GameControllerGetButton(gamePad, SDL_CONTROLLER_BUTTON_A)) {
		if (!jumping)
		{
			jumping = true;
			Move::setGrav(-0.05);

			if (allowJumpSound)
			{
				Sound::playSample(samples[0]);
				allowJumpSound = false;
			}
		}
	}
	else
	{
		allowJumpSound = true;
	}

	if (jumping)
	{
		setPlayerPosition(glm::vec3(position.x, Move::jump(position).y, position.z));
	}

	if (position.y <= 2.5f)
	{
		glm::vec3 tempPosition = getPosition();
		tempPosition.y = 2.5f;
		setPlayerPosition(tempPosition);

		Move::resetV();
		jumping = false;
	}

	if (playerLives <= 0)
	{
		Sound::playSample(samples[2]);
		playerLives = 5;
		
		//kill player
		setPlayerPosition(chekPointPos);
		
		glm::vec3 camPos = camera::getEye();
		camPos.z = position.z;
		camera::setEye(camPos);
	}

	if (!jumping)
		Move::setGrav(-0.3f);

	if (noEnemyCollision)
		allowDamage = true;
}

void Player::draw(SDL_Window* window)
{
	//GLfloat scale(1.0f); // just to allow easy scaling of complete scene
	glm::mat4 modelview(1.0); // set base position for scene
	glm::mat4 projection(1.0);
	projection = glm::perspective(float(60.0f*DEG_TO_RADIAN), 800.0f / 600.0f, 1.0f, 150.0f);
	rt3d::setUniformMatrix4fv(shaderProgram, "projection", glm::value_ptr(projection));
	stack<glm::mat4> mvStack;
	mvStack.push(modelview);

	camera::setAt(Move::moveForward(camera::getEye(), Move::getRotation(), 1.0f));
	mvStack.top() = glm::lookAt(camera::getEye(), camera::getAt(), camera::getUp());

	tmpModel.Animate(currentAnimation, 0.1);
	rt3d::updateMesh(meshObjects[1], RT3D_VERTEX, tmpModel.getAnimVerts(), tmpModel.getVertDataSize());

	glUseProgram(shaderProgram);

	glCullFace(GL_FRONT);
	glBindTexture(GL_TEXTURE_2D, textures[1]);
	rt3d::setMaterial(shaderProgram, material0);
	mvStack.push(mvStack.top());
	mvStack.top() = glm::translate(mvStack.top(), glm::vec3(position));
	mvStack.top() = glm::rotate(mvStack.top(), (float(90.0f * DEG_TO_RADIAN)), glm::vec3(-1.0f, 0.0f, 0.0f));
	mvStack.top() = glm::rotate(mvStack.top(), (-float(rotate * DEG_TO_RADIAN)), glm::vec3(0.0f, 0.0f, 1.0f));
	mvStack.top() = glm::scale(mvStack.top(), glm::vec3(scale));
	rt3d::setUniformMatrix4fv(shaderProgram, "modelview", glm::value_ptr(mvStack.top()));
	rt3d::drawMesh(meshObjects[1], md2VertCount, GL_TRIANGLES);
	mvStack.pop();
	glCullFace(GL_BACK);
	
	mvStack.pop();	 // initial matrix
}