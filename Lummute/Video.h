#ifndef _VIDEO_H
#define _VIDEO_H

#include <SFML/Graphics.hpp>
#include <sstream>
#include <string>
#include "DataStore.h"

class Video
{
	private:
		sf::Font font;
	public:
		Video(void);
		~Video(void);

		//world
		void drawGraphics(sf::RenderWindow& mainWindow, DataStore& data);
		void drawPlayer(sf::RenderWindow& mainWindow, DataStore& data);
		void drawBullets(sf::RenderWindow& mainWindow, DataStore& data);
		void drawAmmo(sf::RenderWindow& mainWindow, DataStore& data);
		void drawEnemies(sf::RenderWindow& mainWindow, DataStore& data);
		
		//gui
		void drawCursor(sf::RenderWindow& mainWindow, DataStore& data);
		void drawDebug(sf::RenderWindow& mainWindow, DataStore& data);
};

#endif