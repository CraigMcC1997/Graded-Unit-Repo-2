#include "IntroductionLevel.h"

void IntroductionLevel::init()
{
	//SOUND EFFECT
	samples[0] = Sound::loadSample("../Resources/SoundFiles/rainforest.wav", BASS_SAMPLE_LOOP);	//adding sound files to the array to be played later in code
	samples[1] = Sound::loadSample("../Resources/SoundFiles/Collectable.wav", BASS_SAMPLE_OVER_POS);
	samples[2] = Sound::loadSample("../Resources/SoundFiles/checkpoint.wav", BASS_SAMPLE_OVER_POS);
	samples[3] = Sound::loadSample("../Resources/SoundFiles/endpoint.wav", BASS_SAMPLE_OVER_POS);

	Sound::playSample(samples[0]);

	//INITIALISING OBJECTS
	for (int i = 0; i < MAX_COLLECTABLES; i++)
	{
		collectable[i]->init();
	}

	for (int i = 0; i < MAX_PLATFORMS; i++)
	{
		platform[i]->init();
	}
	
	for (int i = 0; i < MAX_CHECKPOINTS; i++)
	{
		checkPoint[i]->init();
	}

	endPoint->init();
	enemy->init();
	projectile_Enemy->init();
	player->init();
	bush->init();
	tree->init();

	//SETTING POSITIONS FOR OBJECTS
	endPoint->setPosition(glm::vec3(-3.0f, 3.0f, 230.0f));

	checkPoint[0]->setPosition(glm::vec3(-3.0f, 3.0f, 55.0f));
	checkPoint[1]->setPosition(glm::vec3(-3.0f, 3.0f, 150.0f));
	checkPoint[2]->setPosition(glm::vec3(-3.0f, 3.0f, 190.0f));

	platform[0]->setPosition(glm::vec3(-3.0f, 2.0f, 40.0f));
	platform[1]->setPosition(glm::vec3(-3.0f, 4.0f, 45.0f));
	
	glm::vec3 stairsPosition(glm::vec3(-3.0f, 2.0f, 70.0f));
	for (int i = 2; i <= 6; i++)
	{ 
		platform[i]->setPosition(stairsPosition);
		stairsPosition.z += 5;
		stairsPosition.y += 2;
	}

	collectable[0]->setPosition(glm::vec3(-3.0f, 10.0f, 95.0f));
	collectable[1]->setPosition(glm::vec3(-3.0f, 3.0f, 105.0f));
	collectable[2]->setPosition(glm::vec3(-3.0f, 3.0f, 110.0f));

	enemy->setEnemyPosition(glm::vec3(-3.0f, 1.0f, 120.0f));
	enemy->setMinRange(glm::vec3(0.0f, 0.0f, 120.0f));
	enemy->setMaxRange(glm::vec3(0.0f, 0.0f, 140.0f));

	projectile_Enemy->setEnemyPosition(glm::vec3(-3.0f, 0.5f, 160.0f));
	projectile_Enemy->setMinRange(glm::vec3(-3.0f, 0.5f, 160.0f));
	projectile_Enemy->setMaxRange(glm::vec3(-3.0f, 0.5f, 180.0f));
}

void IntroductionLevel::update(AbstractLevel ** level)
{
	//RUNNING UPDATE LOOP FOR EACH OBJECT
	player->update();
	enemy->update();
	projectile_Enemy->update();

	//CHECKING COLLISION FOR COLLECTABLES
	for (int i = 0; i < MAX_COLLECTABLES; i++)
	{
		if (Collision::collisionDetection(player, collectable[i]))
		{
			player->addCollectable();
			collectable[i]->setPosition(glm::vec3(collectable[i]->getPosition().x,
				collectable[i]->getPosition().y, collectable[i]->getPosition().z + 1000.0f));

			Sound::playSample(samples[1]);
		}
	}

	//CHECKING COLLISION FOR PLATFORMS
	for (int i = 0; i < MAX_PLATFORMS; i++)
	{
		if (Collision::collisionDetection(player, platform[i]))
		{
			if (player->getPosition().y >= platform[i]->getPosition().y)
			{
				player->noPlatformCollision = false;
				player->setJump(false);
				Move::resetV();

				glm::vec3 position = player->getPosition();
				position.y = platform[i]->getPosition().y + 1.3f;

				if (!player->jumping)
					player->setPlayerPosition(position);
			}
		}
		else
			player->noPlatformCollision = true;
			
	}

	//CHECKING COLLISION FOR CHECKPOINTS
	for (int i = 0; i < MAX_CHECKPOINTS; i++)
	{
		if (Collision::collisionDetection(player, checkPoint[i]))
		{
			player->setCheckPoint(checkPoint[i]->getPosition());
			Sound::playSample(samples[2]);
		}
	}

	//CHECKING COLLISION FOR ENEMIES
	if (Collision::collisionDetection(player, enemy))
	{
		if (player->getAllowDamage())
		{
			player->noEnemyCollision = false;
			player->setAllowDamage(false);
			player->takeDamage();
		}
	}
	else
		player->noEnemyCollision = true;

	if (Collision::collisionDetection(player, projectile_Enemy->getProjectile()))
	{
		if (player->getAllowDamage())
		{
			player->noProjectileCollision = false;
			player->setAllowDamage(false);
			player->takeDamage();
		}
	}


	if (player->getPosition().z >= projectile_Enemy->getPosition().z - 5
		&& player->getPosition().z <= projectile_Enemy->getPosition().z + 5)
	{
		projectile_Enemy->shoot();
	}

	if (Collision::collisionDetection(player, endPoint))
	{
		delete endPoint;
		delete* collectable;
		delete* platform;
		delete enemy;
		lUpdate->update(level);
	}
}

void IntroductionLevel::draw(SDL_Window * window)
{
	//DRAWING THE OBJECTS
	display->draw(window);
	player->draw(window);
	endPoint->draw(window);
	projectile_Enemy->draw(window);
	enemy->draw(window);

	for (int i = 0; i < MAX_PLATFORMS; i++)
	{
		platform[i]->draw(window);
	}

	for (int i = 0; i < MAX_CHECKPOINTS; i++)
	{
		checkPoint[i]->draw(window);
	}

	for (int i = 0; i < MAX_COLLECTABLES; i++)
	{
		collectable[i]->draw(window);
	}

	bush->draw(window);
	tree->draw(window);

	SDL_GL_SwapWindow(window);
}