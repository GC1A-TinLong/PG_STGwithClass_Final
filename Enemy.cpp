#include "Enemy.h"

Enemy::Enemy(Vector2f pos)
{
	this->pos = pos;
	spd = 3;
	radius = 20;
	hp = 5;
	color = 0x990000FF;
	getHitCD = 0;
	respawnTimer = 0;

	isHit = 0;
	getHitBuffer = 0;
	isShot = 0;
}

void Enemy::Initialization(Vector2f pos_)
{
	this->pos = pos_;
	spd = 3;
	radius = 20;
	hp = 5;
	color = 0x990000FF;
	getHitCD = 0;
	respawnTimer = 0;

	isHit = 0;
	getHitBuffer = 0;
	isShot = 0;
}

void Enemy::GotHit()
{
	if (isHit == 1 && getHitBuffer == 0 && hp > 0) {
		hp--;
		getHitBuffer = 1;
	}
	if (getHitBuffer == 1) {
		getHitCD++;
	}
	if (getHitCD >= 10) {
		getHitCD = 0;
		getHitBuffer = 0;
		isHit = 0;
	}
	if (isAlive() == 0) {
		getHitCD = 0;
		getHitBuffer = 0;
		isHit = 0;
		Respawn();
	}
}
void Enemy::Respawn()
{
	respawnTimer++;

	if (respawnTimer >= 240) {
		hp = 5;
		respawnTimer = 0;
	}
}

void Enemy::Update()
{
	if (isAlive() == 1) {
		pos.x += spd;
	}
	if (pos.x >= 1280 - radius) {
		pos.x = float(1280 - radius);
	}
	else if (pos.x <= radius) {
		pos.x = (float)radius;
	}
	if (pos.x >= 1280 - radius || pos.x <= radius) {
		spd *= -1;
	}
}

void Enemy::Draw()
{
	if (isAlive() == 1) {
		Novice::DrawEllipse(int(pos.x), int(pos.y), radius, radius, 0, color, kFillModeSolid);
		Novice::ScreenPrintf(int(pos.x - radius), int(pos.y - radius), "HP=%d", hp);
	}
	if (isAlive() == 0) {
		Novice::ScreenPrintf(int(pos.x - radius * 2), int(pos.y - radius), "RespawnTimer=%d", respawnTimer);
	}
}
