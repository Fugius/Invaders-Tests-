#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <cmath>
#include "Projectile.h"
#include <limits>

class Projectile_set
{
public:
	Projectile_set();
	void add_projectile(sf::Vector2f origin, sf::Vector2f target, Team team);
	bool check_collisions(sf::Vector2f arrayPos[], Team team);
	void update();
	void render(sf::RenderWindow &window);
	~Projectile_set();

private:
	std::vector<Projectile*> m_elements;
	Team m_tempTeam;
	Entity *m_e;
};