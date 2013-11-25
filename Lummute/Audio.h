#ifndef _AUDIO_H
#define _AUDIO_H

#include <SFML/Audio.hpp>

#include "DataStore.h"

class Audio
{
	private:

	public:
		sf::SoundBuffer buffer;
		sf::Sound sound;

		Audio(void);
		~Audio(void);
		void playMusic(DataStore& data);
		void playSoundQueue(DataStore& data);
};

#endif