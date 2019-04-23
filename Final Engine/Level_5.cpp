#include "Level_5.h"

void Level_5::init()
{
	samples[0] = Sound::loadSample("../Resources/SoundFiles/rainforest.wav", BASS_SAMPLE_LOOP);	//adding sound files to the array to be played later in code
	samples[1] = Sound::loadSample("../Resources/SoundFiles/Collectable.wav", BASS_SAMPLE_OVER_POS);
	samples[2] = Sound::loadSample("../Resources/SoundFiles/checkpoint.wav", BASS_SAMPLE_OVER_POS);
	samples[3] = Sound::loadSample("../Resources/SoundFiles/endpoint.wav", BASS_SAMPLE_OVER_POS);

	for (int i = 0; i < 5; i++)
	{
		collectable[i]->init();
	}
	for (int i = 0; i < MAX_PLATFORMS; i++)
	{
		platform[i]->init();
	}
	for (int i = 0; i < 2; i++)
	{
		enemy[i]->init();
	}
	endPoint->init();
	endPoint->setPosition(glm::vec3(-6.0f, 3.0f, 90.0f));
	platform[0]->setPosition(glm::vec3(-6.0f, 2.0f, 20.0f));
	platform[1]->setPosition(glm::vec3(-6.0f, 4.0f, 30.0f));
	platform[2]->setPosition(glm::vec3(-6.0f, 2.0f, 40.0f));
	platform[3]->setPosition(glm::vec3(-6.0f, 3.0f, 50.0f));
	platform[4]->setPosition(glm::vec3(-6.0f, 5.0f, 60.0f));
	collectable[0]->setPosition(glm::vec3(-6.0f, 3.0f, 30.0f));
	collectable[1]->setPosition(glm::vec3(-6.0f, 3.0f, 40.0f));
	collectable[2]->setPosition(glm::vec3(-6.0f, 3.0f, 50.0f));
	collectable[3]->setPosition(glm::vec3(-6.0f, 3.0f, 60.0f));
	collectable[4]->setPosition(glm::vec3(-6.0f, 3.0f, 70.0f));
	enemy[0]->setEnemyPosition(glm::vec3(-6.0f, 0.0f, 20.0f));
	enemy[1]->setEnemyPosition(glm::vec3(-6.0f, 0.5f, 50.0f));
	enemy[0]->setMinRange(glm::vec3(0.0f, 0.0f, 10.0f));
	enemy[0]->setMaxRange(glm::vec3(0.0f, 0.0f, 30.0f));
	enemy[1]->setMinRange(glm::vec3(0.0f, 0.0f, 40.0f));
	enemy[1]->setMaxRange(glm::vec3(0.0f, 0.0f, 60.0f));
	player->init();
	bush->init();
	tree->init();
}

void Level_5::update(AbstractLevel** level)
{
	for (int i = 0; i < 5; i++)
	{
		if (Collision::collisionDetection(player, collectable[i]))
		{
			player->addCollectable();
			collectable[i]->setPosition(glm::vec3(collectable[i]->getPosition().x,
				collectable[i]->getPosition().y, collectable[i]->getPosition().z + 1000.0f));
			Sound::playSample(samples[1]);
		}
	}

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
			else
				player->noPlatformCollision = true;
		}

	}

	for (int i = 0; i < 2; i++)
	{
		if (Collision::collisionDetection(player, enemy[i]))
		{
			player->takeDamage();
		}
	}

	for (int i = 0; i < 2; i++)
	{
		enemy[i]->update();
	}
	player->update();

	if (Collision::collisionDetection(player, endPoint))
	{
		Sound::playSample(samples[2]);
		SDL_Quit();
	}
}

void Level_5::draw(SDL_Window* window)
{
	display->draw(window);
	player->draw(window);
	endPoint->draw(window);

	for (int i = 0; i < 2; i++)
	{
		enemy[i]->draw(window);
	}
	for (int i = 0; i < 5; i++)
	{
		collectable[i]->draw(window);
	}
	for (int i = 0; i < MAX_PLATFORMS; i++)
	{
		platform[i]->draw(window);
	}
	bush->draw(window);
	tree->draw(window);
	SDL_GL_SwapWindow(window);
}