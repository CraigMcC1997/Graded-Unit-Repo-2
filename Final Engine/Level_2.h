#pragma once
#include "AbstractLevel.h"
#include "Level_2_Display.h"
#include "Level_2_Update.h"
#include "Player.h"
#include "Platform.h"
#include "Basic_Enemy.h"
#include "Collectable.h"
#include "EndPoint.h"
#include "Tree.h"
#include "Bush.h"

class Level_2 : public AbstractLevel
{
protected:
	enum { MAX_PLATFORMS = 6 };
	enum { MAX_ENEMIES = 3 };
	enum { MAX_COLLECTABLES = 6 };

	Player* player;
	Platform* platform[MAX_PLATFORMS];
	Collectable* collectable[MAX_COLLECTABLES];
	Basic_Enemy* enemy[MAX_ENEMIES];
	EndPoint* endPoint;
	Bush* bush = new Bush();
	Tree* tree = new Tree();
public:
	Level_2(Player* player) : player(player)
	{
		display = new Level_2_Display();
		lUpdate = new Level_2_Update(player);
		endPoint = new EndPoint(2);

		display->init();
		player->setPlayerPosition(glm::vec3(-3.0f, 0.1f, 0.0f));
		for (int i = 0; i < MAX_PLATFORMS; i++)
		{
			platform[i] = new Platform();
		}
		for (int i = 0; i < 5; i++)
		{
			collectable[i] = new Collectable();
		}
		for (int i = 0; i < 2; i++)
		{
			enemy[i] = new Basic_Enemy();
		}
		init();
	}

	void init();
	void draw(SDL_Window* window);
	void update(AbstractLevel** level);
};