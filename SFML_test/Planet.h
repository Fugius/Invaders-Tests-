#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include "Entity.h"
#include "GlobalUtils.h"
#include <algorithm>

class Planet
{
public:
	Planet(sf::Vector2f pos, float size, sf::Vector2f screenSize);
	void update();
	void render(sf::RenderWindow &window);
	sf::Vector2f* getPosition();
	void setPosition(sf::Vector2f pos);
	void getDamage();
	bool isAlive();
	~Planet();

private:
	bool m_alive;
	sf::Vector2f m_pos;
	Entity *m_planetSprite[10];
	int m_angle;
	int m_hp;
	float m_size;
	int m_counter;
	sf::Vector2f m_screenSize;
	Team m_team;

	Entity *tempE;

};