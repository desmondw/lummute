#ifndef _SETTINGS_H
#define _SETTINGS_H

#include <SFML/Graphics.hpp>

class Settings
{
	private:

	public:
		static const int WIN_WIDTH = 800, WIN_HEIGHT = 600;
		bool fullscreenOn, vsyncOn;

		Settings(void);
		~Settings(void);
};

#endif