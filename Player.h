#pragma once
#include "Object.h"
#include "Bullet.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include "Enemy.h"

class Enemy;

class Player :public Object
{
private:
	Bullet* bullet[kBulletNum];
	int bulletCD;
	int getHitCD;

	bool getHitBuffer;
	bool buffer;
	bool getHit;
	bool isEnemyHit;

public:
	Player(Vector2f pos);
	~Player();
	void Initialization(Vector2f pos_);

	bool isAlive() { return hp > 0; };

	void IsGetHit(Enemy* enemy);
	void IsEnemyHit(Enemy* enemy);
	void Control(char* keys, char* preKeys);
	void Draw();
};