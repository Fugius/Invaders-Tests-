#include "Planet.h"

Planet::Planet(sf::Vector2f pos, float size, sf::Vector2f screenSize) : m_alive(true), m_pos(pos), m_hp(3), m_angle(0.003), m_size(size), m_counter(0), m_screenSize(screenSize)
{
	m_planetSprite[0] = new Entity(m_pos, sf::Vector2f(m_size, m_size), "Ressources/textures/earth.png");

	int i = 0;
	for (i = 1; i < 10; i++)
	{
		m_planetSprite[i] = new Entity(m_pos, sf::Vector2f(m_size, m_size), "Ressources/textures/earth2.png");
	}

	m_team = Defender;
	
}

void Planet::update()
{
	m_counter++;
	int i = 0;
	if (m_counter % 100 == 0)
	{
		m_planetSprite[0]->rotate(m_angle + 0.5, sf::Vector2f(m_screenSize.x / 2, m_screenSize.y / 2));
		for (i = 1; i < 10; i++)
		{
			m_planetSprite[i]->rotate(m_angle + i * 0.5, sf::Vector2f(m_screenSize.x / 2, m_screenSize.y / 2));
		}
	}
		
}

void Planet::render(sf::RenderWindow & window)
{
	int i = 0;

	for (i = 9; i >= 0; i--)
	{
		m_planetSprite[i]->render(&window);
	}
}

sf::Vector2f * Planet::getPosition()
{
	return m_planetSprite[0]->getPosition();
}

Planet::~Planet()
{
}
