#include "Invader_S.h"

Invader_S::Invader_S(sf::Vector2f size, sf::Vector2f screenSize, Direction dir) : m_pos((screenSize.x / 2), -size.y - 100), m_direction(dir), m_speed(1.1), m_counter(0), m_screenSize(screenSize), m_size(size), m_hp(1)
{
	int rdAngle = 0;

	random_device rd;
	mt19937 eng(rd());
	uniform_int_distribution<> distr(1, 360);

	rdAngle = distr(eng);

	m_InvaderSprite = new Entity(m_pos, size, "Ressources/textures/ET1.png");
	m_pos = m_InvaderSprite->rotate(rdAngle, sf::Vector2f(m_screenSize.x / 2, m_screenSize.y / 2));

	m_team = Invaders;
}

void Invader_S::update()
{
	m_counter++;

	float dx = ((( (m_screenSize.x - m_size.x) / 2) - (m_pos.x)) / 2300);
	float dy = ((( (m_screenSize.y - m_size.y) / 2) - (m_pos.y)) / 2300);

	m_InvaderSprite->move(sf::Vector2f(dx, dy));

	if (m_direction == m_right)
		m_pos = m_InvaderSprite->rotate(m_speed, sf::Vector2f(m_screenSize.x / 2, m_screenSize.y / 2));
	if (m_direction == m_left)
		m_pos = m_InvaderSprite->rotate(-m_speed, sf::Vector2f(m_screenSize.x / 2, m_screenSize.y / 2));

}

void Invader_S::render(sf::RenderWindow &window)
{
	m_InvaderSprite->render(&window);
}

sf::Vector2f * Invader_S::getPosition()
{
	return m_InvaderSprite->getPosition();
}

Invader_S::~Invader_S()
{
}
