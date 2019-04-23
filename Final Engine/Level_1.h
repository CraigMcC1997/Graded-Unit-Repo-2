#pragma once
#include "AbstractLevel.h"
#include "Level_1_Display.h"
#include "Level_1_Update.h"
#include "Player.h"
#include "Platform.h"
#include "Basic_Enemy.h"
#include "Projectile_Enemy.h"
#include "Collectable.h"
#include "EndPoint.h"

class Level_1 : public AbstractLevel
{
protected:
	HSAMPLE *samples = NULL;

	Player* player;
	Projectile_Enemy* proj_Enemy;
	EndPoint* endPoint;

	enum { MAX_PLATFORMS = 6 };
	enum { MAX_COLLECTABLES = 6 };
	enum { MAX_ENEMIES = 3 };
	enum { MAX_CHECKPOINTS = 4 };

	Platform* platform[MAX_PLATFORMS];
	Collectable* collectable[MAX_COLLECTABLES];
	Basic_Enemy* enemy[MAX_ENEMIES];
	EndPoint* checkPoint[MAX_CHECKPOINTS];

public:
	Level_1(Player* player) : player(player)
	{
		display = new Level_1_Display();
		lUpdate = new Level_1_Update(player);
		endPoint = new EndPoint(2);
		//proj_Enemy = new Projectile_Enemy();

		display->init();
		player->setPlayerPosition(glm::vec3(-3.0f, 0.1f, 0.0f));
		for (int i = 0; i < MAX_PLATFORMS; i++)
		{
			platform[i] = new Platform();
		}
		for (int i = 0; i < MAX_COLLECTABLES; i++)
		{
			collectable[i] = new Collectable();
		}
		for (int i = 0; i < MAX_ENEMIES; i++)
		{
			enemy[i] = new Basic_Enemy();
		}
		for (int i = 0; i < MAX_CHECKPOINTS; i++)
		{
			checkPoint[i] = new EndPoint(1);
		}
		init();
	}

	void init();
	void draw(SDL_Window* window);
	void update(AbstractLevel** level);
};