#include <SFML/Graphics.hpp>

#include "DataStore.h"
#include "Input.h"
#include "Audio.h"
#include "Video.h"
#include "Calculations.h"

sf::RenderWindow mainWindow; //game window
DataStore data;
Input input;
Audio audio;
Video video;
Calculations calculate;

void intializeVideoSettings()
{
	ShowWindow(GetConsoleWindow(), SW_HIDE); //hides console

	mainWindow.UseVerticalSync(data.settings.vsyncOn);
	if (data.settings.fullscreenOn)
		mainWindow.Create(sf::VideoMode(data.settings.WIN_WIDTH, data.settings.WIN_HEIGHT, 32), "Lummute", sf::Style::Fullscreen);
	else
		mainWindow.Create(sf::VideoMode(data.settings.WIN_WIDTH, data.settings.WIN_HEIGHT, 32), "Lummute", sf::Style::Close);
	mainWindow.ShowMouseCursor(false);
}

void main()
{
	srand (static_cast<int>(time(NULL))); //seed random gen
	data.newGame(mainWindow); //generate new world
	intializeVideoSettings(); //implement initial window settings

	//main loop
    while (mainWindow.IsOpened())
    {
		input.handleInput(mainWindow, data, audio, video);
		calculate.nextFrame(mainWindow, data);
		audio.playSoundQueue(data);
		//audio.playMusic(data);
		video.drawGraphics(mainWindow, data);
    }
}