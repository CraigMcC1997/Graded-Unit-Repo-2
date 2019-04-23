#pragma once
#include "AbstractLevel.h"
#include "IntroductionLevel_Display.h"
#include "IntroductionLevel_Update.h"
#include "Player.h"
#include "Platform.h"
#include "Basic_Enemy.h"
#include "Projectile_Enemy.h"
#include "Collectable.h"
#include "EndPoint.h"
#include "Tree.h"
#include "Bush.h"

class IntroductionLevel : public AbstractLevel
{
private:
	Player* player;
	Basic_Enemy* enemy;
	Projectile_Enemy* projectile_Enemy;
	EndPoint* endPoint;

	enum { MAX_PLATFORMS = 6 };
	enum { MAX_CHECKPOINTS = 2 };
	enum { MAX_COLLECTABLES = 3 };

	Platform* platform[MAX_PLATFORMS];
	EndPoint* checkPoint[MAX_CHECKPOINTS];
	Collectable* collectable[MAX_COLLECTABLES];
	Bush* bush = new Bush();
	Tree* tree = new Tree();

public:
	IntroductionLevel(Player* player) : player(player)
	{
		display = new IntroductionLevel_Display();
		lUpdate = new IntroductionLevel_Update(player);
		endPoint = new EndPoint(2);
		projectile_Enemy = new Projectile_Enemy();
		enemy = new Basic_Enemy();

		for (int i = 0; i < MAX_PLATFORMS; i++)
		{
			platform[i] = new Platform();
		}

		for (int i = 0; i < MAX_COLLECTABLES; i++)
		{
			collectable[i] = new Collectable();
		}

		for (int i = 0; i < MAX_CHECKPOINTS; i++)
		{
			checkPoint[i] = new EndPoint(1);
		}

		display->init();
		init();
	}

	void init();
	void draw(SDL_Window* window);
	void update(AbstractLevel** level);
};

