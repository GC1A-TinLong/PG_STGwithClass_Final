#pragma once
#include "Player.h"
#include "Enemy.h"

enum Gamescene {
	Title_,
	Gamestage_,
	Clear_,
};

class Scene
{
private:
	Player* player;
	Enemy* enemy[kEnemyNum];
	Gamescene currentScene = Title_;

	short enemyCount;

	int aniTimer;
	int aniPosX;
	int width;

	int titleHandle;
	int titleKeysHandle;
	int pressRHandle;
	int clearHandle;

public:
	Scene();
	~Scene();
	void Initialization();

	void Gameplay(char* keys, char* preKeys);

	void Gamestage(char* keys, char* preKeys);

	void DrawTitle();
	void DrawGamestage();
	void DrawClear();

	void Draw();
};

