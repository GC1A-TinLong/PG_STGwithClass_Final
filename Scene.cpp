#include "Scene.h"

Scene::Scene()
{
	player = new Player({ 640.0f,600.0f });
	for (int i = 0; i < kEnemyNum; i++) {
		enemy[i] = new Enemy({ 100.0f + i * 80,50.0f + i * 40 });
	}

	enemyCount = 0;

	aniTimer = 0;
	aniPosX = 0;
	width = 1280;

	titleHandle = Novice::LoadTexture("./images/title.png");
	titleKeysHandle = Novice::LoadTexture("./images/titleKeys.png");
	pressRHandle = Novice::LoadTexture("./images/pressR.png");
	clearHandle = Novice::LoadTexture("./images/clear.png");
}
Scene::~Scene()
{
	delete player;
	delete* enemy;
}
void Scene::Initialization()
{
	aniTimer = 0;
	aniPosX = 0;
	width = 1280;
}

void Scene::Gameplay(char* keys, char* preKeys)
{
	switch (currentScene) {
	case Title_:
		if (keys[DIK_SPACE] && !preKeys[DIK_SPACE]) {
			currentScene = Gamestage_;
			Initialization();
		}
		break;

	case Gamestage_:
		Gamestage(keys, preKeys);

		for (int i = 0; i < kEnemyNum; i++) {
			enemyCount += enemy[i]->aliveCount();
		}
		if (enemyCount <= 0) {
			currentScene = Clear_;
			Initialization();
		}
		enemyCount = 0;
		break;

	case Clear_:
		if (keys[DIK_SPACE] && !preKeys[DIK_SPACE]) {
			currentScene = Title_;
			player->Initialization({ 640.0f,600.0f });
			for (int i = 0; i < kEnemyNum; i++) {
				enemy[i]->Initialization({ 100.0f + i * 80,50.0f + i * 40 });
			}
		}
		break;
	}
}

void Scene::Gamestage(char* keys, char* preKeys)
{
	player->Control(keys, preKeys);
	for (int i = 0; i < kEnemyNum; i++) {
		player->IsGetHit(enemy[i]);
		player->IsEnemyHit(enemy[i]);
		enemy[i]->Update();
	}
}

void Scene::Draw()
{
	switch (currentScene) {
	case Title_:
		DrawTitle();
		break;

	case Gamestage_:
		DrawGamestage();
		break;

	case Clear_:
		DrawClear();
		break;
	}
}

void Scene::DrawTitle()
{
	Novice::DrawSprite(0, 0, titleHandle, 1.0f, 1.0f, 0, WHITE);
	aniTimer++;
	if (aniTimer >= 30) {
		aniPosX += width;
		aniTimer = 0;
	}
	if (aniPosX >= 2560) {
		aniPosX = 0;
	}
	Novice::DrawSpriteRect(0, 0, aniPosX, 0, width, 720, titleKeysHandle, 0.5f, 1.0f, 0, WHITE);
}

void Scene::DrawGamestage()
{
	Novice::DrawBox(0, 0, 1280, 720, 0, 0x3e3e3eff, kFillModeSolid);

	player->Draw();
	for (int i = 0; i < kEnemyNum; i++) {
		enemy[i]->Draw();
	}
	if (player->isAlive() == 0) {
		aniTimer++;
		if (aniTimer >= 25) {
			aniPosX += width;
			aniTimer = 0;
		}
		if (aniPosX >= 2560) {
			aniPosX = 0;
		}
		Novice::DrawSpriteRect(0, 0, aniPosX, 0, width, 720, pressRHandle, 0.5f, 1.0f, 0, WHITE);
	}
	else {
		Initialization();
	}
}

void Scene::DrawClear()
{
	Novice::DrawSprite(0, 0, clearHandle, 1.0f, 1.0f, 0, WHITE);
	aniTimer++;
	if (aniTimer >= 30) {
		aniPosX += width;
		aniTimer = 0;
	}
	if (aniPosX >= 2560) {
		aniPosX = 0;
	}
	Novice::DrawSpriteRect(0, 0, aniPosX, 0, width, 720, titleKeysHandle, 0.5f, 1.0f, 0, WHITE);
}
