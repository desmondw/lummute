#include "DataStore.h"

DataStore::DataStore(void)
{
	settings = Settings();
	physics = Physics();
	mousePos.resize(2);
	mousePos[0] = -500;
	mousePos[1] = -500;
}

DataStore::~DataStore(void)
{
}

void DataStore::newGame(sf::RenderWindow& mainWindow)
{
	playerPos.resize(2);
	playerPos[0] = settings.WIN_WIDTH / 2;
	playerPos[1] = settings.WIN_HEIGHT / 2;
	playerSize = physics.PLAYER_INITIAL_SIZE;

	bulletList.resize(0);
	enemyList.resize(0);
	ammoList.resize(0);
	sfxQueue.resize(0);
}

void DataStore::addBullet(float x, float y, float xSpeed, float ySpeed)
{
	std::vector<float> bullet;
	bullet.resize(4);
	bullet[0] = x;
	bullet[1] = y;
	bullet[2] = xSpeed;
	bullet[3] = ySpeed;

	bulletList.push_back(bullet);
}

void DataStore::addEnemy(float x, float y)
{
	std::vector<float> enemy;
	enemy.resize(3);
	enemy[0] = x;
	enemy[1] = y;
	enemy[2] = physics.ENEMY_SPEED;

	enemyList.push_back(enemy);
}

void DataStore::addAmmo(float x, float y, float xSpeed, float ySpeed)
{
	std::vector<float> ammo;
	ammo.resize(4);
	ammo[0] = x;
	ammo[1] = y;
	ammo[2] = xSpeed;
	ammo[3] = ySpeed;

	ammoList.push_back(ammo);
}

void DataStore::queueSound(std::string fileName)
{
	std::string filePath = "bin/sfx/";
	filePath.append(fileName);

	sfxQueue.push_back(filePath);
}