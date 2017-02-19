#include "Invader_M.h"

Invader_M::Invader_M(sf::Vector2f size, sf::Vector2f screenSize, Direction dir) : m_time(sf::seconds(1)), m_pos((screenSize.x / 2), -size.y - 100), m_direction(dir), m_speed(0.8), m_counter(0), m_screenSize(screenSize), m_size(size), m_hp(2)
{
	int rdAngle = 0;

	random_device rd;
	mt19937 eng(rd());
	uniform_int_distribution<> distr(1, 360);

	rdAngle = distr(eng);

	m_InvaderSprite = new Entity(m_pos, size, "Ressources/textures/ET3.png");
	m_pos = m_InvaderSprite->rotate(rdAngle, sf::Vector2f(m_screenSize.x / 2, m_screenSize.y / 2));

	m_team = Invaders;
}

void Invader_M::update(Projectile_set *ps)
{
	m_counter++;

	float dx = ((((m_screenSize.x - m_size.x) / 2) - (m_pos.x)) / 2000);
	float dy = ((((m_screenSize.y - m_size.y) / 2) - (m_pos.y)) / 2000);

	m_InvaderSprite->move(sf::Vector2f(dx, dy));

	if (m_direction == m_right)
		m_pos = m_InvaderSprite->rotate(m_speed, sf::Vector2f(m_screenSize.x / 2, m_screenSize.y / 2));
	else
		m_pos = m_InvaderSprite->rotate(-m_speed, sf::Vector2f(m_screenSize.x / 2, m_screenSize.y / 2));

	if (m_clock.getElapsedTime() >= m_time)
	{
		fire_projectile(ps);
		m_clock.restart();
	}
		

}

void Invader_M::render(sf::RenderWindow &window)
{
	m_InvaderSprite->render(&window);
}

sf::Vector2f * Invader_M::getPosition()
{
	return m_InvaderSprite->getPosition();
}

Invader_M::~Invader_M()
{
}

void Invader_M::fire_projectile(Projectile_set * ps)
{
	sf::Vector2f tpos[2];
	float ox = 0, oy = 0;

	for (int i = 0; i < 4; i++)
	{
		ox = std::max(ox, getPosition()[i].x);
		oy = std::max(oy, getPosition()[i].y);
	}

	tpos[1] = sf::Vector2f(ox, oy);

	for (int i = 0; i < 4; i++)
	{
		ox = std::min(ox, getPosition()[i].x);
		oy = std::min(oy, getPosition()[i].y);
	}

	tpos[0] = sf::Vector2f(ox, oy);



	ps->add_projectile(sf::Vector2f((tpos[1].x - tpos[0].x)/2 + tpos[0].x, (tpos[1].y - tpos[0].y)/2 + tpos[0].y), sf::Vector2f(m_screenSize.x / 2, m_screenSize.y / 2), Invaders);
}
