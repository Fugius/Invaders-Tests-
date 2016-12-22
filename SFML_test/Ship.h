#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include "Entity.h"
#include "GlobalUtils.h"

using namespace std;

class Ship
{
public:
	Ship(sf::Vector2f size, sf::Vector2f screenSize, sf::Vector2f planetSize);
	void update();
	void move(Direction dir);
	void stopMoving();
	void render(sf::RenderWindow &window);
	void fire();
	void shield();
	~Ship();

private:
	Entity *m_ShipSprite[6];
	sf::Vector2f m_pos;
	Direction m_direction;
	float m_speed;
	float m_acc;
	int m_actSprite;
	bool m_moving;
	int m_counter;
	sf::Vector2f m_screenSize;
};
