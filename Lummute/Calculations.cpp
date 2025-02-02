#include "Calculations.h"


Calculations::Calculations(void)
{
}


Calculations::~Calculations(void)
{
}


void Calculations::nextFrame(sf::RenderWindow& mainWindow, DataStore& data)
{
	//update movements
	playerMovement(mainWindow, data);
	bulletMovement(mainWindow, data);
	ammoMovement(mainWindow, data);
	enemyMovement(mainWindow, data);

	//check for collisions
	ammoCollision(mainWindow, data);
	bulletCollision(mainWindow, data);
	if (playerCollision(mainWindow, data)) //if dead
	{
		data.newGame(mainWindow);
		return;
	}
	
	//spawn new entities
	enemySpawning(mainWindow, data);
	ammoSpawning(mainWindow, data);
	//if (bulletFiring(mainWindow, data)) //if dead
	//{
	//	data.newGame(mainWindow);
	//	return;
	//}
}

void Calculations::playerMovement(sf::RenderWindow& mainWindow, DataStore& data)
{
	float frameTime = mainWindow.GetFrameTime();
	bool leftPressed = false, rightPressed = false, upPressed = false, downPressed = false;

	//left, right, up, down
	if (mainWindow.GetInput().IsKeyDown(sf::Key::A) || mainWindow.GetInput().IsKeyDown(sf::Key::Left) || mainWindow.GetInput().IsKeyDown(sf::Key::Numpad4))
		leftPressed = true;
	if (mainWindow.GetInput().IsKeyDown(sf::Key::D) || mainWindow.GetInput().IsKeyDown(sf::Key::Right) || mainWindow.GetInput().IsKeyDown(sf::Key::Numpad6))
		rightPressed = true;
	if (mainWindow.GetInput().IsKeyDown(sf::Key::W) || mainWindow.GetInput().IsKeyDown(sf::Key::Up) || mainWindow.GetInput().IsKeyDown(sf::Key::Numpad8))
		upPressed = true;
	if (mainWindow.GetInput().IsKeyDown(sf::Key::S) || mainWindow.GetInput().IsKeyDown(sf::Key::Down) || mainWindow.GetInput().IsKeyDown(sf::Key::Numpad2))
		downPressed = true;

	//up-left, up-right, down-left, down-right
	if (mainWindow.GetInput().IsKeyDown(sf::Key::Numpad7))
	{
		upPressed = true;
		leftPressed = true;
	}
	if (mainWindow.GetInput().IsKeyDown(sf::Key::Numpad9))
	{
		upPressed = true;
		rightPressed = true;
	}
	if (mainWindow.GetInput().IsKeyDown(sf::Key::Numpad1))
	{
		downPressed = true;
		leftPressed = true;
	}
	if (mainWindow.GetInput().IsKeyDown(sf::Key::Numpad3))
	{
		downPressed = true;
		rightPressed = true;
	}

	float normalSpeed = data.physics.PLAYER_SPEED * frameTime;
	float diagonalSpeed = sqrt(pow(data.physics.PLAYER_SPEED * frameTime, 2) / 2);

	//calculates speed and executes
	if (leftPressed)
	{
		if (upPressed)
		{
			data.playerPos[0] -= diagonalSpeed;
			data.playerPos[1] -= diagonalSpeed;
		}
		else if (downPressed)
		{
			data.playerPos[0] -= diagonalSpeed;
			data.playerPos[1] += diagonalSpeed;
		}
		else
			data.playerPos[0] -= normalSpeed;
	}
	else if (rightPressed)
	{
		if (upPressed)
		{
			data.playerPos[0] += diagonalSpeed;
			data.playerPos[1] -= diagonalSpeed;
		}
		else if (downPressed)
		{
			data.playerPos[0] += diagonalSpeed;
			data.playerPos[1] += diagonalSpeed;
		}
		else
			data.playerPos[0] += normalSpeed;
	}
	else if (upPressed)
		data.playerPos[1] -= normalSpeed;
	else if (downPressed)
		data.playerPos[1] += normalSpeed;
}

void Calculations::bulletMovement(sf::RenderWindow& mainWindow, DataStore& data)
{
	float frameTime = mainWindow.GetFrameTime();

	for(int i=0; i<data.bulletList.size(); i++)
	{
		//if not within window borders after this frame's bullet movement, delete bullet
		if (!(data.bulletList[i][0] + data.bulletList[i][2] * frameTime >= 0 && data.bulletList[i][0] + data.bulletList[i][2] * frameTime < data.settings.WIN_WIDTH && data.bulletList[i][1] + data.bulletList[i][3] * frameTime >= 0 && data.bulletList[i][1] + data.bulletList[i][3] * frameTime < data.settings.WIN_HEIGHT))
			data.bulletList.erase(data.bulletList.begin() + i);
		else //else update bullet position
		{
			data.bulletList[i][0] += data.bulletList[i][2] * frameTime;
			data.bulletList[i][1] += data.bulletList[i][3] * frameTime;
		}
	}
}

void Calculations::ammoMovement(sf::RenderWindow& mainWindow, DataStore& data)
{
	float frameTime = mainWindow.GetFrameTime();

	for(int i=0; i<data.ammoList.size(); i++)
	{
		//if not within window borders after this frame's bullet movement, delete ammo
		if (!(data.ammoList[i][0] + data.ammoList[i][2] * frameTime >= 0 && data.ammoList[i][0] + data.ammoList[i][2] * frameTime < data.settings.WIN_WIDTH && data.ammoList[i][1] + data.ammoList[i][3] * frameTime >= 0 && data.ammoList[i][1] + data.ammoList[i][3] * frameTime < data.settings.WIN_HEIGHT))
			data.ammoList.erase(data.ammoList.begin() + i);
		else //else update ammo position
		{
			data.ammoList[i][0] += data.ammoList[i][2] * frameTime;
			data.ammoList[i][1] += data.ammoList[i][3] * frameTime;
		}
	}
}

void Calculations::enemyMovement(sf::RenderWindow& mainWindow, DataStore& data)
{
	float frameTime = mainWindow.GetFrameTime();
	
	for(int i=0; i<data.enemyList.size(); i++)
	{
		float angle = atan2((data.playerPos[1]-data.enemyList[i][1]),(data.playerPos[0]-data.enemyList[i][0]));
		float xSpeed = cos(angle) * data.enemyList[i][2];
		float ySpeed = sin(angle) * data.enemyList[i][2];
		bool collision = false;
		float iFromPlayer, jFromPlayer;

		//detect collision with another enemy
		//for(int j=0; j<data.enemyList.size(); j++)
		//{
		//	if (i != j)
		//	{
		//		float enemyHardBorder = data.physics.ENEMY_SIZE/2;
		//		if ((data.enemyList[i][0] + enemyHardBorder > data.enemyList[j][0] - enemyHardBorder) && (data.enemyList[i][0] - enemyHardBorder < data.enemyList[j][0] + enemyHardBorder))
		//		{
		//			if ((data.enemyList[i][1] + enemyHardBorder > data.enemyList[j][1] - enemyHardBorder) && (data.enemyList[i][1] - enemyHardBorder < data.enemyList[j][1] + enemyHardBorder))
		//			{
		//				iFromPlayer = abs((data.playerPos[0] - data.enemyList[i][0]) + (data.playerPos[1] - data.enemyList[i][1]));
		//				jFromPlayer = abs((data.playerPos[0] - data.enemyList[j][0]) + (data.playerPos[1] - data.enemyList[j][1]));
		//				collision = true;
		//			}
		//		}
		//	}
		//}


		data.enemyList[i][0] += xSpeed * frameTime;
		data.enemyList[i][1] += ySpeed * frameTime;
		data.enemyList[i][2] *= data.physics.ENEMY_SPEED_GAIN;
	}
}

void Calculations::ammoCollision(sf::RenderWindow& mainWindow, DataStore& data)
{
	for(int i=0; i<data.ammoList.size(); i++)
	{
		if ((data.ammoList[i][0] + data.physics.AMMO_SIZE/2 > data.playerPos[0] - data.playerSize/2) && (data.ammoList[i][0] - data.physics.AMMO_SIZE/2 < data.playerPos[0] + data.playerSize/2))
		{
			if ((data.ammoList[i][1] + data.physics.AMMO_SIZE/2 > data.playerPos[1] - data.playerSize/2) && (data.ammoList[i][1] - data.physics.AMMO_SIZE/2 < data.playerPos[1] + data.playerSize/2))
			{
				data.ammoList.erase(data.ammoList.begin() + i);
				data.playerSize += data.physics.PLAYER_SIZE_CHANGE;
			}
		}
	}
}

void Calculations::bulletCollision(sf::RenderWindow& mainWindow, DataStore& data)
{
	bool enemyAlive;
	for(int i=0; i<data.enemyList.size(); i++)
	{
		enemyAlive = true;

		for(int j=0; j<data.bulletList.size(); j++)
		{
			if (enemyAlive)
			{
				if ((data.bulletList[j][0] + data.physics.BULLET_SIZE/2 > data.enemyList[i][0] - data.physics.ENEMY_SIZE/2) && (data.bulletList[j][0] - data.physics.BULLET_SIZE/2 < data.enemyList[i][0] + data.physics.ENEMY_SIZE/2))
				{
					if ((data.bulletList[j][1] + data.physics.BULLET_SIZE/2 > data.enemyList[i][1] - data.physics.ENEMY_SIZE/2) && (data.bulletList[j][1] - data.physics.BULLET_SIZE/2 < data.enemyList[i][1] + data.physics.ENEMY_SIZE/2))
					{
						//collision
						data.bulletList.erase(data.bulletList.begin() + j);
						data.enemyList.erase(data.enemyList.begin() + i);
						enemyAlive = false;
					}
				}
			}
		}
	}
}

bool Calculations::playerCollision(sf::RenderWindow& mainWindow, DataStore& data)
{
	for(int i=0; i<data.enemyList.size(); i++)
	{
		if ((data.enemyList[i][0] + data.physics.ENEMY_SIZE/2 > data.playerPos[0] - data.playerSize/2) && (data.enemyList[i][0] - data.physics.ENEMY_SIZE/2 < data.playerPos[0] + data.playerSize/2))
		{
			if ((data.enemyList[i][1] + data.physics.ENEMY_SIZE/2 > data.playerPos[1] - data.playerSize/2) && (data.enemyList[i][1] - data.physics.ENEMY_SIZE/2 < data.playerPos[1] + data.playerSize/2))
				return true; //collision
		}
	}
	return false;
}

//DEPRECATED
bool Calculations::bulletFiring(sf::RenderWindow& mainWindow, DataStore& data)
{
	if (mainWindow.GetInput().IsMouseButtonDown(sf::Mouse::Left) && bulletTimer.GetElapsedTime() > data.physics.BULLET_SPACING)
	{
		float angle = atan2((data.mousePos[1] - data.playerPos[1]), (data.mousePos[0] - data.playerPos[0]));
		float xSpeed = cos(angle)*data.physics.BULLET_SPEED;
		float ySpeed = sin(angle)*data.physics.BULLET_SPEED;
		
		data.playerSize -= data.physics.PLAYER_SIZE_CHANGE;
		if (data.playerSize < 2)
			return true;

		data.addBullet(data.playerPos[0], data.playerPos[1], xSpeed, ySpeed);
		bulletTimer.Reset();
	}
		return false;
}

void Calculations::enemySpawning(sf::RenderWindow& mainWindow, DataStore& data)
{
	if (enemyTimer.GetElapsedTime() > data.physics.ENEMY_SPAWN_RATE)
	{
		float spawnX, spawnY;

		if (rand() % 2 > 0) //spawn at random location along top or bottom
		{
			spawnX = rand() % data.settings.WIN_WIDTH;

			if (rand() % 2 > 0)
				spawnY = 0;
			else
				spawnY = data.settings.WIN_HEIGHT;
		}
		else //spawn at random location along left or right
		{
			spawnY = rand() % data.settings.WIN_HEIGHT;

			if (rand() % 2 > 0)
				spawnX = 0;
			else
				spawnX = data.settings.WIN_WIDTH;
		}

		data.addEnemy(spawnX, spawnY);
		enemyTimer.Reset();
	}
}

void Calculations::ammoSpawning(sf::RenderWindow& mainWindow, DataStore& data)
{
	if (ammoTimer.GetElapsedTime() > data.physics.AMMO_SPAWN_RATE)
	{
		float spawnX, spawnY;

		if (rand() % 2 > 0) //spawn at random location along top or bottom
		{
			spawnX = rand() % data.settings.WIN_WIDTH;

			if (rand() % 2 > 0)
				spawnY = 0;
			else
				spawnY = data.settings.WIN_HEIGHT;
		}
		else //spawn at random location along left or right
		{
			spawnY = rand() % data.settings.WIN_HEIGHT;

			if (rand() % 2 > 0)
				spawnX = 0;
			else
				spawnX = data.settings.WIN_WIDTH;
		}

		float destinationX = rand() % data.settings.WIN_WIDTH;
		float destinationY = rand() % data.settings.WIN_HEIGHT;
		float angle = atan2((destinationY - spawnY), (destinationX - spawnX));
		float xSpeed = cos(angle)*data.physics.AMMO_SPEED;
		float ySpeed = sin(angle)*data.physics.AMMO_SPEED;

		data.addAmmo(spawnX, spawnY, xSpeed, ySpeed);
		ammoTimer.Reset();
	}
}