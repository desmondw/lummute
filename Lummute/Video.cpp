#include "Video.h"

Video::Video(void)
{
	font.LoadFromFile("bin/gfx/arial.ttf", 30);
}

Video::~Video(void)
{
}

void Video::drawGraphics(sf::RenderWindow& mainWindow, DataStore& data)
{
	mainWindow.Clear(data.physics.BG_COLOR); //clear screen
	
	//draw world
	drawAmmo(mainWindow, data);
	drawBullets(mainWindow, data);
	drawEnemies(mainWindow, data);
	drawPlayer(mainWindow, data);

	//draw gui
	drawCursor(mainWindow, data);
	drawDebug(mainWindow, data);

    mainWindow.Display(); //draw screen
}

void Video::drawPlayer(sf::RenderWindow& mainWindow, DataStore& data)
{
	float playerSize = data.playerSize / 2;
	sf::Shape player = sf::Shape::Rectangle((data.playerPos[0] - playerSize), (data.playerPos[1] - playerSize), (data.playerPos[0] + playerSize), (data.playerPos[1] + playerSize), data.physics.PLAYER_COLOR);
	mainWindow.Draw(player);
}

void Video::drawBullets(sf::RenderWindow& mainWindow, DataStore& data)
{
	float bulletSize = data.physics.BULLET_SIZE / 2;
	sf::Shape bullet;

	for(int i=0; i<data.bulletList.size(); i++)
	{
		bullet = sf::Shape::Rectangle((data.bulletList[i][0] - bulletSize), (data.bulletList[i][1] - bulletSize), (data.bulletList[i][0] + bulletSize), (data.bulletList[i][1] + bulletSize), data.physics.BULLET_COLOR);
		mainWindow.Draw(bullet);
	}
}

void Video::drawAmmo(sf::RenderWindow& mainWindow, DataStore& data)
{
	float ammoSize = data.physics.AMMO_SIZE / 2;
	sf::Shape ammo;

	for(int i=0; i<data.ammoList.size(); i++)
	{
		ammo = sf::Shape::Rectangle((data.ammoList[i][0] - ammoSize), (data.ammoList[i][1] - ammoSize), (data.ammoList[i][0] + ammoSize), (data.ammoList[i][1] + ammoSize), data.physics.AMMO_OUTER_COLOR);
		mainWindow.Draw(ammo);
		ammo = sf::Shape::Rectangle((data.ammoList[i][0] - ammoSize*.75), (data.ammoList[i][1] - ammoSize*.75), (data.ammoList[i][0] + ammoSize*.75), (data.ammoList[i][1] + ammoSize*.75), data.physics.AMMO_INNER_COLOR);
		mainWindow.Draw(ammo);
	}
}

void Video::drawEnemies(sf::RenderWindow& mainWindow, DataStore& data)
{
	float enemySize = data.physics.ENEMY_SIZE / 2;
	sf::Shape enemy;

	for(int i=0; i<data.enemyList.size(); i++)
	{
		enemy = sf::Shape::Rectangle((data.enemyList[i][0] - enemySize), (data.enemyList[i][1] - enemySize), (data.enemyList[i][0] + enemySize), (data.enemyList[i][1] + enemySize), data.physics.ENEMY_COLOR);
		mainWindow.Draw(enemy);
	}
}



void Video::drawCursor(sf::RenderWindow& mainWindow, DataStore& data)
{
	//draw a box cursor with spaces on the sides
	float cursorSize = data.physics.CURSOR_SIZE / 2;
	float cursorWidth = cursorSize / 4;
	float cursorLength = cursorSize / 2;

	sf::Shape cursor;

	//top-left
	cursor = sf::Shape::Rectangle((data.mousePos[0] - cursorSize), (data.mousePos[1] - cursorSize), (data.mousePos[0] - cursorSize + cursorLength), (data.mousePos[1] - cursorSize + cursorWidth), data.physics.PLAYER_COLOR);
	mainWindow.Draw(cursor);
	cursor = sf::Shape::Rectangle((data.mousePos[0] - cursorSize), (data.mousePos[1] - cursorSize), (data.mousePos[0] - cursorSize + cursorWidth), (data.mousePos[1] - cursorSize + cursorLength), data.physics.PLAYER_COLOR);
	mainWindow.Draw(cursor);
	
	//top-right
	cursor = sf::Shape::Rectangle((data.mousePos[0] + cursorSize - cursorLength), (data.mousePos[1] - cursorSize), (data.mousePos[0] + cursorSize), (data.mousePos[1] - cursorSize + cursorWidth), data.physics.PLAYER_COLOR);
	mainWindow.Draw(cursor);
	cursor = sf::Shape::Rectangle((data.mousePos[0] + cursorSize - cursorWidth), (data.mousePos[1] - cursorSize), (data.mousePos[0] + cursorSize), (data.mousePos[1] - cursorSize + cursorLength), data.physics.PLAYER_COLOR);
	mainWindow.Draw(cursor);
	
	//bottom-left
	cursor = sf::Shape::Rectangle((data.mousePos[0] - cursorSize), (data.mousePos[1] + cursorSize), (data.mousePos[0] - cursorSize + cursorWidth), (data.mousePos[1] + cursorSize - cursorLength), data.physics.PLAYER_COLOR);
	mainWindow.Draw(cursor);
	cursor = sf::Shape::Rectangle((data.mousePos[0] - cursorSize), (data.mousePos[1] + cursorSize), (data.mousePos[0] - cursorSize + cursorLength), (data.mousePos[1] + cursorSize - cursorWidth), data.physics.PLAYER_COLOR);
	mainWindow.Draw(cursor);
	
	//bottom-right
	cursor = sf::Shape::Rectangle((data.mousePos[0] + cursorSize), (data.mousePos[1] + cursorSize), (data.mousePos[0] + cursorSize - cursorLength), (data.mousePos[1] + cursorSize - cursorWidth), data.physics.PLAYER_COLOR);
	mainWindow.Draw(cursor);
	cursor = sf::Shape::Rectangle((data.mousePos[0] + cursorSize), (data.mousePos[1] + cursorSize), (data.mousePos[0] + cursorSize - cursorWidth), (data.mousePos[1] + cursorSize - cursorLength), data.physics.PLAYER_COLOR);
	mainWindow.Draw(cursor);
}

void Video::drawDebug(sf::RenderWindow& mainWindow, DataStore& data)
{
	std::ostringstream sstream;
	sf::String text("", font, 15);
	text.SetPosition(5, 5);

	sstream << "FPS: ";
	sstream << static_cast<int>(1 / mainWindow.GetFrameTime());

	text.SetText(sstream.str());
	sstream.end;
	
	text.SetColor(sf::Color::Black);
	mainWindow.Draw(text);
}