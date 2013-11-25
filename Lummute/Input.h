#ifndef _INPUT_H
#define _INPUT_H

#include <SFML/Graphics.hpp>
#include "DataStore.h"
#include "Audio.h"
#include "Video.h"

class Input
{
	private:
		
	public:
		Input(void);
		~Input(void);
		void handleInput(sf::RenderWindow& mainWindow, DataStore& data, Audio& audio, Video& video);
		void keyPress(sf::RenderWindow& mainWindow, DataStore& data, Audio& audio, Video& video, sf::Event& input);
		void mouseClick(sf::RenderWindow& mainWindow, DataStore& data, Audio& audio, Video& video, sf::Event& input);
};

#endif