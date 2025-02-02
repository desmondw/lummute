#include "Input.h"

Input::Input(void)
{
}

Input::~Input(void)
{
}

void Input::handleInput(sf::RenderWindow& mainWindow, DataStore& data, Audio& audio, Video& video)
{
	sf::Event input;
    while (mainWindow.GetEvent(input))
    {
        if (input.Type == sf::Event::Closed) //window closed
            mainWindow.Close();
		else if (input.Type == sf::Event::KeyPressed) //key pressed
			keyPress(mainWindow, data, audio, video, input);
		else if (input.Type == sf::Event::MouseButtonPressed) //key pressed
			mouseClick(mainWindow, data, audio, video, input);
		else if (input.Type == sf::Event::MouseMoved)
		{
			data.mousePos[0] = input.MouseMove.X;
			data.mousePos[1] = input.MouseMove.Y;
		}
    }
}

void Input::keyPress(sf::RenderWindow& mainWindow, DataStore& data, Audio& audio, Video& video, sf::Event& input)
{
	switch (input.Key.Code)
	{
		case sf::Key::F9:
			if (data.settings.vsyncOn)
			{
				data.settings.vsyncOn = false;
				mainWindow.UseVerticalSync(data.settings.vsyncOn);
			}
			else
			{
				data.settings.vsyncOn = true;
				mainWindow.UseVerticalSync(data.settings.vsyncOn);
			}
			break;
		case sf::Key::F11:
			if (data.settings.fullscreenOn)
			{
				data.settings.fullscreenOn = false;
				mainWindow.Create(sf::VideoMode(data.settings.WIN_WIDTH, data.settings.WIN_HEIGHT, 32), "Lummute", sf::Style::Close);
			}
			else
			{
				data.settings.fullscreenOn = true;
				mainWindow.Create(sf::VideoMode(data.settings.WIN_WIDTH, data.settings.WIN_HEIGHT, 32), "Lummute", sf::Style::Fullscreen);
			}
			break;
		case sf::Key::Escape:
			mainWindow.Close();
			break;
	}
}

void Input::mouseClick(sf::RenderWindow& mainWindow, DataStore& data, Audio& audio, Video& video, sf::Event& input)
{
	switch (input.MouseButton.Button)
	{
		case sf::Mouse::Left:
			float angle = atan2((data.mousePos[1] - data.playerPos[1]), (data.mousePos[0] - data.playerPos[0]));
			float xSpeed = cos(angle)*data.physics.BULLET_SPEED;
			float ySpeed = sin(angle)*data.physics.BULLET_SPEED;
		
			data.playerSize -= data.physics.PLAYER_SIZE_CHANGE;
			data.addBullet(data.playerPos[0], data.playerPos[1], xSpeed, ySpeed);
			data.queueSound("shoot.wav");
			
			if (data.playerSize < 2)
				data.newGame(mainWindow);
			break;
	}
}