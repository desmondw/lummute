#include "Physics.h"

Physics::Physics(void)
{
	PLAYER_INITIAL_SIZE = 16, PLAYER_SIZE_CHANGE = 2;
	ENEMY_SIZE = 16, BULLET_SIZE = 8, AMMO_SIZE = 8, CURSOR_SIZE = 32;
	PLAYER_SPEED = 200, BULLET_SPEED = 1000, BULLET_SPACING = .1, ENEMY_SPEED = 100, AMMO_SPEED = 50;
	ENEMY_SPEED_GAIN = 1.00005;
	ENEMY_SPAWN_RATE = 1, AMMO_SPAWN_RATE = .125;

	PLAYER_COLOR = sf::Color(128, 128, 128);
	BULLET_COLOR = sf::Color(128, 128, 128);
	ENEMY_COLOR = sf::Color(0, 0, 0);
	AMMO_INNER_COLOR = sf::Color(255, 255, 255);
	AMMO_OUTER_COLOR = sf::Color(0, 0, 0);
	BG_COLOR = sf::Color(255, 255, 255);
}

Physics::~Physics(void)
{
}