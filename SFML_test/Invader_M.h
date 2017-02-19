#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include "Entity.h"
#include "GlobalUtils.h"
#include "Projectiles_Set.h"
#include <algorithm>
#include <time.h>
#include <random>

using namespace std;

class Invader_M
{
public:
	Invader_M(sf::Vector2f size, sf::Vector2f screenSize, Direction dir);
	void update(Projectile_set *ps);
	void render(sf::RenderWindow &window);
	sf::Vector2f* getPosition();
	~Invader_M();

protected:
	void fire_projectile(Projectile_set *ps);

private:
	sf::Clock m_clock;
	Entity *m_InvaderSprite;
	sf::Vector2f m_pos;
	Direction m_direction;
	float m_speed;
	int m_counter;
	sf::Vector2f m_screenSize;
	sf::Vector2f m_size;
	int m_hp;
	Team m_team;
	sf::Time m_time;
};
