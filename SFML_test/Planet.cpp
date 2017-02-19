#include "Planet.h"

Planet::Planet(sf::Vector2f pos, float size, sf::Vector2f screenSize) : m_alive(true), m_pos(pos), m_hp(3), m_angle(0.03), m_size(size), m_counter(0), m_screenSize(screenSize)
{
	m_planetSprite[0] = new Entity(m_pos, sf::Vector2f(m_size, m_size), "Ressources/textures/earth.png");

	int i = 0;
	for (i = 1; i < 10; i++)
	{
		m_planetSprite[i] = new Entity(m_pos, sf::Vector2f(m_size, m_size), "Ressources/textures/earth2.png");
	}

	m_team = Defender;
	tempE = new Entity(pos, sf::Vector2f(size, size) , "Ressources/textures/Laser.png");
	
}

void Planet::update()
{
	m_counter++;
	int i = 0;

	m_planetSprite[0]->rotate(m_angle + 0.5, sf::Vector2f(m_screenSize.x / 2, m_screenSize.y / 2));
	for (i = 1; i < 10; i++)
	{
		m_planetSprite[i]->rotate(m_angle + i * 0.5, sf::Vector2f(m_screenSize.x / 2, m_screenSize.y / 2));
	}
	
		
}

void Planet::render(sf::RenderWindow & window)
{
	int i = 0;

	for (i = 9; i >= 0; i--)
	{
		m_planetSprite[i]->render(&window);
	}

	tempE->render(&window);
}

sf::Vector2f * Planet::getPosition()
{
	float maxx = 0, maxy = 0;

	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			maxx = max(m_planetSprite[i]->getPosition()[j].x, maxx);
			maxy = max(m_planetSprite[i]->getPosition()[j].y, maxy);
		}
	}

	float minx = maxx, miny = maxy;

	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			minx = min(m_planetSprite[i]->getPosition()[j].x, minx);
			miny = min(m_planetSprite[i]->getPosition()[j].y, miny);
		}
	}
	sf::Vector2f res[4] = {
		sf::Vector2f(minx, miny),
		sf::Vector2f(maxx, miny),
		sf::Vector2f(maxx, maxy),
		sf::Vector2f(minx, maxy)
	};

	tempE->move(res);
	return res;
}

void Planet::setPosition(sf::Vector2f pos)
{
	for (int i = 0; i < 10; i++)
	{
		m_planetSprite[i]->move(pos);
	}
}

void Planet::getDamage()
{
	m_hp--;
}

bool Planet::isAlive()
{
	return m_hp > 0;
}

Planet::~Planet()
{
}
