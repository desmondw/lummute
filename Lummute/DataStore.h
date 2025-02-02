#ifndef _DATASTORE_H
#define _DATASTORE_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

#include "Settings.h"
#include "Physics.h"

class DataStore
{
	private:

	public:
		Settings settings;
		Physics physics;

		std::vector<float> playerPos, mousePos;
		int playerSize;
		std::vector<std::vector<float>> bulletList, enemyList, ammoList;
		std::vector<std::string> sfxQueue;

		DataStore(void);
		~DataStore(void);
		void newGame(sf::RenderWindow& mainWindow);
		void addBullet(float x, float y, float xSpeed, float ySpeed);
		void addEnemy(float x, float y);
		void addAmmo(float x, float y, float xSpeed, float ySpeed);
		void queueSound(std::string fileName);
};

#endif