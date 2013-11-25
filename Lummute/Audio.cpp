#include "Audio.h"

Audio::Audio(void)
{
}

Audio::~Audio(void)
{
}

void Audio::playMusic(DataStore& data)
{

}

void Audio::playSoundQueue(DataStore& data)
{
	for (int i=0; i<data.sfxQueue.size(); i++)
	{
		buffer.LoadFromFile(data.sfxQueue[i]);
		sound.SetBuffer(buffer);
		sound.Play();
	}

	data.sfxQueue.resize(0);
}