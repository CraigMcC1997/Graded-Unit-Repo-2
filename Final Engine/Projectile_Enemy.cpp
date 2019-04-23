#include "Projectile_Enemy.h"

void Projectile_Enemy::init()
{
	//shader
	shaderProgram = rt3d::initShaders("../Resources/Shaders/phong.vert", "../Resources/Shaders/phong.frag");
	rt3d::setLight(shaderProgram, light0);
	rt3d::setMaterial(shaderProgram, material1);

	projectile->init();

	samples = new HSAMPLE[5];	//array of sound  files
	samples[0] = Sound::loadSample("../Resources/SoundFiles/boom.wav", BASS_SAMPLE_OVER_POS);	//adding sound files to the array to be played later in code

	//model loading
	rt3d::loadObj("../Resources/3D_Objects/MODEL.obj", verts, norms, tex_coords, indices);
	meshIndexCount[0] = indices.size();
	textures[0] = loadTexture::loadTextures("../Resources/Textures/fabric.png");
	meshObjects[0] = rt3d::createMesh(verts.size() / 3, verts.data(), nullptr, norms.data(), tex_coords.data(),
		meshIndexCount[0], indices.data());
	verts.clear(), norms.clear(), tex_coords.clear(), indices.clear();

	collisionBox = glm::vec3(1, 1, 1);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void Projectile_Enemy::setEnemyPosition(glm::vec3 newPosition)
{
	position = newPosition;
}

void Projectile_Enemy::setMinRange(glm::vec3 minPosition)
{
	minRange = minPosition;
}

void Projectile_Enemy::setMaxRange(glm::vec3 maxPosition)
{
	maxRange = maxPosition;
}

glm::vec3 Projectile_Enemy::getPosition()
{
	return position;
}

void Projectile_Enemy::setEnemyRotate(GLfloat newRotate)
{
	rotate = newRotate;
}

glm::vec3 Projectile_Enemy::getScale()
{
	return scale;
}

void Projectile_Enemy::shoot()
{
	//shoot projectile
	

	if (!bulletActive)
	{
		Sound::playSample(samples[0]);
		bulletActive = true;
		projectile->setPosition(glm::vec3(position.x, position.y + 3.0f, position.z));
	}
}

void Projectile_Enemy::stopShooting()
{
	bulletActive = false;
	choseRotate = false;
	projectile->setPosition(glm::vec3(0.0f, 10000.0f, 0.0f));
}

Projectile* Projectile_Enemy::getProjectile()
{
	return projectile;
}

void Projectile_Enemy::update()
{
	setEnemyPosition(Move::moveZ(getPosition(), Move::getRotation(), velocity));
	projectile->update();

	if (position.z < minRange.z)
	{
		velocity *= -1.0f;
		rotate = 0.0f;
	}

	if (position.z > maxRange.z)
	{
		velocity *= -1.0f;
		rotate = 3.0f;
	}

	if (bulletActive) 
	{
		//find rotation
		bool moveLeft = true;

		if (!choseRotate)
		{
			if (rotate == 3.0f)
			{
				moveLeft = true;
				choseRotate = true;
			}
			else
				moveLeft = false;
		}


		if(moveLeft)
			projectile->setPosition(glm::vec3(projectile->getPosition().x,
				projectile->getPosition().y, projectile->getPosition().z - 0.1f));

		else
			projectile->setPosition(glm::vec3(projectile->getPosition().x,
				projectile->getPosition().y, projectile->getPosition().z + 0.1f));
	}

	if (projectile->getPosition().z <= position.z - 20
		|| projectile->getPosition().z >= position.z + 20)
		stopShooting();
}

void Projectile_Enemy::draw(SDL_Window* window)
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

	glUseProgram(shaderProgram);
	rt3d::setUniformMatrix4fv(shaderProgram, "projection", glm::value_ptr(projection));

	//enemy
	glBindTexture(GL_TEXTURE_2D, textures[0]);
	mvStack.push(mvStack.top());
	mvStack.top() = glm::translate(mvStack.top(), position);
	mvStack.top() = glm::scale(mvStack.top(), scale);
	mvStack.top() = glm::rotate(mvStack.top(), rotate, glm::vec3(0.0f, 1.0f, 0.0f));
	rt3d::setUniformMatrix4fv(shaderProgram, "modelview", glm::value_ptr(mvStack.top()));
	rt3d::setMaterial(shaderProgram, material1);
	rt3d::drawIndexedMesh(meshObjects[0], meshIndexCount[0], GL_TRIANGLES);
	mvStack.pop();

	//projectile
	if (bulletActive)
	{
		projectile->draw(window);
	}
	
	glDepthMask(GL_TRUE);
}

glm::vec3 Projectile_Enemy::getCollisionBox()
{
	return collisionBox;
}
