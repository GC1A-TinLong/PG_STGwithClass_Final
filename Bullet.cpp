#include "Bullet.h"

Bullet::Bullet(Vector2f pos)
{
	this->pos = pos;
	spd = 15;
	radius = 10;
	color = BLACK;

	isShot = 0;
}

void Bullet::Initialization(Vector2f pos_)
{
	this->pos = pos_;

	isShot = 0;
}

void Bullet::SetPosToPlayer(Vector2f& playerPos)
{
	pos = playerPos;

	isShot = 1;
}
void Bullet::Shooting()
{
	if (isShot == 1) {
		pos.y -= spd;
	}
	if (pos.y < -radius) {
		isShot = 0;
		pos.x = -100.0f;
	}
}

void Bullet::Draw()
{
	if (isShot == 1) {
		Novice::DrawEllipse(int(pos.x), int(pos.y), radius, radius, 0, color, kFillModeSolid);
	}
}
