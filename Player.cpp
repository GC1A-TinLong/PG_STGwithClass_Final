#include "Player.h"

Player::Player(Vector2f pos)
{
	for (int i = 0; i < kBulletNum; i++) {
		bullet[i] = new Bullet({ -100.0f,0 });
	}

	this->pos = pos;
	spd = 12;
	radius = 40;
	hp = 1;
	color = WHITE;

	buffer = 0;
	bulletCD = 0;
	getHitCD = 0;

	getHitBuffer = 0;
	getHit = 0;
	isShot = 0;
	isEnemyHit = 0;
}
Player::~Player()
{
	delete* bullet;
}

void Player::Initialization(Vector2f pos_)
{
	for (int i = 0; i < kBulletNum; i++) {
		bullet[i]->Initialization({ -100.0f,0 });
	}

	this->pos = pos_;
	spd = 12;
	radius = 40;
	hp = 1;
	color = WHITE;

	buffer = 0;
	bulletCD = 0;
	getHitCD = 0;

	getHitBuffer = 0;
	getHit = 0;
	isShot = 0;
	isEnemyHit = 0;
}

void Player::IsGetHit(Enemy* enemy)
{
	float distance = sqrtf(powf(pos.x - enemy->GetPos().x, 2.0f) + powf(pos.y - enemy->GetPos().y, 2.0f));
	int minDistance = radius + enemy->GetRadius();
	getHit = (distance <= minDistance) ? 1 : 0;

	if (getHit == 1 && getHitBuffer == 0) {
		hp--;
		getHitBuffer = 1;
	}
	if (getHitBuffer == 1) {
		getHitCD++;
		if (getHitCD >= 120) {
			getHitCD = 0;
			getHitBuffer = 0;
		}
	}
}

void Player::IsEnemyHit(Enemy* enemy)
{
	float distance[kBulletNum]{};
	int minDistance = bullet[0]->GetRadius() + enemy->GetRadius();
	for (int i = 0; i < kBulletNum; i++) {
		distance[i] = sqrtf(powf(bullet[i]->GetPos().x - enemy->GetPos().x, 2.0f) + powf(bullet[i]->GetPos().y - enemy->GetPos().y, 2.0f));
	}
	for (int i = 0; i < kBulletNum; i++) {
		if (distance[i] <= minDistance) {
			enemy->SetIsHit(true);
		}
	}
	enemy->GotHit();
}

void Player::Control(char* keys, char* preKeys)
{
	if (isAlive() == 1) {
		if (keys[DIK_W]) {
			pos.y -= spd;
		}
		if (keys[DIK_S]) {
			pos.y += spd;
		}
		if (keys[DIK_A]) {
			pos.x -= spd;
		}
		if (keys[DIK_D]) {
			pos.x += spd;
		}

		if (keys[DIK_SPACE] && buffer == 0) {
			for (int i = 0; i < kBulletNum; i++) {
				if (bullet[i]->GetIsShot() == 0) {
					bullet[i]->SetPosToPlayer(pos);

					buffer = 1;
					break;
				}
			}
		}
		else if (buffer == 1) {
			bulletCD++;
			if (bulletCD >= 4) {
				buffer = 0;
				bulletCD = 0;
			}
		}
		for (int i = 0; i < kBulletNum; i++) {
			bullet[i]->Shooting();
		}
	}

	if (isAlive() == 0) {
		if (keys[DIK_R] && !preKeys[DIK_R]) {
			Initialization({ 640.0f,600.0f });
		}
	}
}

void Player::Draw()
{
	for (int i = 0; i < kBulletNum; i++) {
		bullet[i]->Draw();
	}
	if (isAlive() == 1) {
		Novice::DrawEllipse(int(pos.x), int(pos.y), radius, radius, 0, color, kFillModeSolid);
	}
}
