#pragma once
#include "Object.h"

const int kBulletNum = 50;

class Bullet :public Object
{
private:

public:
	Bullet(Vector2f pos);
	void Initialization(Vector2f pos_);

	bool GetIsShot() { return isShot; };
	Vector2f GetPos() { return pos; };
	int GetRadius() { return radius; };

	void SetPosToPlayer(Vector2f& playerPos);
	void Shooting();

	void Draw();
};

