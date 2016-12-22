#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include "Entity.h"
#include "GlobalUtils.h"
#include <random>


using namespace std;

class Invader_S
{
public:
	Invader_S(sf::Vector2f size, sf::Vector2f screenSize, Direction dir);
	void update();
	void render(sf::RenderWindow &window);
	~Invader_S();

private:
	Entity *m_InvaderSprite;
	sf::Vector2f m_pos;
	Direction m_direction;
	float m_speed;
	int m_counter;
	sf::Vector2f m_screenSize;
	sf::Vector2f m_size;
	int m_hp;
};
