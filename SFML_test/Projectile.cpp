#include "Projectile.h"

Projectile::Projectile(sf::Vector2f origin, sf::Vector2f target, Team team) : m_size(30, 5), m_sprite(origin, sf::Vector2f(30, 5), "Ressources/textures/Laser.png"),  m_counter(0), m_pos(origin), m_team(team)
{
	m_dx = (target.x - origin.x);
	m_dy = (target.y - origin.y);

	float angle = 0;
	float dta = sqrt(m_dx*m_dx + m_dy*m_dy);
	float dtb = abs(m_dx);
	float cosA = 0;
	float pi = 3.14159265359;

	cosA = dtb / dta;

	angle = acos(cosA);
	angle *= (360 / (2 * pi));

	if (m_dx * m_dy < 0)
		angle = -angle;

	m_pos = m_sprite.rotate(angle, sf::Vector2f(origin.x - m_size.y / 2, origin.y - m_size.y / 2));
	
}

void Projectile::update()
{
	m_counter++;

	if (m_counter % 20 == 0)
	{
		m_pos.x += (m_dx / 400);
		m_pos.y += (m_dy / 400);

		m_sprite.move(sf::Vector2f(m_dx / 400, m_dy / 400));
	}
}

void Projectile::render(sf::RenderWindow & window)
{
	m_sprite.render(&window);
}

sf::Vector2f * Projectile::getPosition()
{
	return m_sprite.getPosition();
}

Projectile::~Projectile()
{
}


