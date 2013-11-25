#ifndef _PHYSICS_H
#define _PHYSICS_H

#include <SFML/Graphics.hpp>

class Physics
{
	private:

	public:
		float PLAYER_INITIAL_SIZE, PLAYER_SIZE_CHANGE;
		float ENEMY_SIZE, BULLET_SIZE, AMMO_SIZE, CURSOR_SIZE;
		float PLAYER_SPEED, BULLET_SPEED, BULLET_SPACING, ENEMY_SPEED, AMMO_SPEED;
		float ENEMY_SPEED_GAIN;
		float ENEMY_SPAWN_RATE, AMMO_SPAWN_RATE;
		sf::Color PLAYER_COLOR, BULLET_COLOR, ENEMY_COLOR, AMMO_INNER_COLOR, AMMO_OUTER_COLOR, BG_COLOR;

		Physics(void);
		~Physics(void);
};

#endif