#pragma once
#include "Struct.h"
#include "Object.h"

const int kEnemyNum = 5;

class Enemy :public Object
{
private:
	int getHitCD;
	int respawnTimer;

	bool isHit;
	bool getHitBuffer;

public:
	Enemy(Vector2f pos);
	void Initialization(Vector2f pos_);

	bool isAlive() { return hp > 0; };
	short aliveCount() { return isAlive() == 1; };

	void SetIsHit(bool isHit_) { this->isHit = isHit_; };
	void GotHit();
	void Respawn();
	void Update();

	void Draw();
};