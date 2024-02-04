#pragma once
#include <Novice.h>
#include "Struct.h"

class Object
{
protected:
	Vector2f pos;
	int spd;
	int radius;
	int hp;
	unsigned int color;

	bool isShot;

public:
	const Vector2f GetPos() { return pos; };
	const int GetRadius() { return radius; };
};