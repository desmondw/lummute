#ifndef _CALCULATIONS_H
#define _CALCULATIONS_H

#include "DataStore.h"

#include <math.h>

class Calculations
{
	private:

	public:
		sf::Clock bulletTimer;
		sf::Clock enemyTimer;
		sf::Clock ammoTimer;

		Calculations(void);
		~Calculations(void);
		void nextFrame(sf::RenderWindow& mainWindow, DataStore& data);
		void playerMovement(sf::RenderWindow& mainWindow, DataStore& data);
		void bulletMovement(sf::RenderWindow& mainWindow, DataStore& data);
		void ammoMovement(sf::RenderWindow& mainWindow, DataStore& data);
		void enemyMovement(sf::RenderWindow& mainWindow, DataStore& data);
		void ammoCollision(sf::RenderWindow& mainWindow, DataStore& data);
		void bulletCollision(sf::RenderWindow& mainWindow, DataStore& data);
		bool playerCollision(sf::RenderWindow& mainWindow, DataStore& data);
		bool bulletFiring(sf::RenderWindow& mainWindow, DataStore& data);
		void enemySpawning(sf::RenderWindow& mainWindow, DataStore& data);
		void ammoSpawning(sf::RenderWindow& mainWindow, DataStore& data);
};

#endif