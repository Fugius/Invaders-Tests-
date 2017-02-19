#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <cmath>
#include "Entity.h"
#include "GlobalUtils.h"



class Projectile
{
public:
	Projectile(sf::Vector2f origin, sf::Vector2f target, Team team);
	void update();
	void render(sf::RenderWindow &window);
	sf::Vector2f* getPosition();
	Team getTeam();
	~Projectile();

private:
	Entity m_sprite;
	sf::Vector2f m_pos;
	sf::Vector2f m_size;
	float m_dx;
	float m_dy;
	int m_counter;
	Team m_team;
};