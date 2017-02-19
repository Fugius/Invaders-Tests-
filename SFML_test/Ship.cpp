#include "Ship.h"

Ship::Ship(sf::Vector2f size, sf::Vector2f screenSize, sf::Vector2f planetSize) : m_pos((screenSize.x / 2) , (screenSize.y / 2) - (planetSize.y / 2) - 100), m_direction(m_right), m_speed(0), m_acc(0.2), m_actSprite(0), m_moving(false), m_counter(0), m_screenSize(screenSize)
{
	int i = 0;

	for (i = 0; i < 6; i++)
	{
		string adress = "Ressources/textures/Ship_" + std::to_string(i+1) + ".png";
		m_ShipSprite[i] = new Entity(m_pos, size, adress);
		m_ShipSprite[i]->rotate(90);
	}

	m_team = Defender;
	m_hp = 3;
}

void Ship::update()
{
	m_counter++;
	if (m_counter % 2 == 0)
		m_actSprite += 1;

	if (m_actSprite > 5)
		m_actSprite = 0;

	if (m_moving == false)
	{
		if (m_direction == m_right)
		{
			m_speed -= m_acc * 0.37;
			if (m_speed <= 0)
				m_speed = 0;
		}
			

		if (m_direction == m_left)
		{
			m_speed += m_acc * 0.37;
			if (m_speed >= 0)
				m_speed = 0;
		}

	}

	

	else
	{
		if (m_direction == m_right)
		{
			if (m_speed >= 2)
				m_speed = 2;
			else
				m_speed += m_acc;
		}

		if (m_direction == m_left)
		{
			if (m_speed <= -2)
				m_speed = -2;
			else
				m_speed -= m_acc;
		}
		
	}

	int i = 0;

	for (i = 0; i < 6; i++)
	{
		m_ShipSprite[i]->rotate(m_speed, sf::Vector2f(m_screenSize.x / 2, m_screenSize.y / 2));
	}
}

void Ship::move(Direction dir)
{
	m_moving = true;

	if (dir != m_direction)
	{
		int i = 0;

		for (i = 0; i < 6; i++)
		{
			m_ShipSprite[i]->flip();
		}
		
	}
	m_direction = dir;
}

void Ship::stopMoving()
{
	m_moving = false;
}

void Ship::render(sf::RenderWindow &window)
{

	m_ShipSprite[m_actSprite]->render(&window);
}

sf::Vector2f * Ship::getPosition()
{
	return m_ShipSprite[0]->getPosition();
}

void Ship::fire()
{
}

void Ship::shield()
{
}

void Ship::getDamage()
{
	m_hp--;
}

bool Ship::isAllive()
{
	return m_hp > 0;
}

Ship::~Ship()
{
}
