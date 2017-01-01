#include "Projectiles_Set.h"

Projectile_set::Projectile_set()
{

}

void Projectile_set::add_projectile(sf::Vector2f origin, sf::Vector2f target, Team team)
{
	m_elements.push_back(new Projectile(origin, target, team));
}

bool Projectile_set::check_collisions(sf::Vector2f arrayPos[])
{
	bool colX(false);
	bool colY(false);

	int i(0), j(0);
	float max_x_projectile(0), max_y_projectile(0), min_x_projectile(0), min_y_projectile(0);
	float max_x_obj(0), max_y_obj(0), min_x_obj(arrayPos[0].x), min_y_obj(arrayPos[0].y);

	//for each projectile
	for (i = 0; i < m_elements.size(); i++)
	{
		min_y_projectile = m_elements[i]->getPosition()[0].y;
		min_x_projectile = m_elements[i]->getPosition()[0].x;

		for (j = 0; j < 4; j++)
		{
			if (arrayPos[j].x > max_x_obj)
				max_x_obj = arrayPos[j].x;

			if (arrayPos[j].y > max_y_obj)
				max_y_obj = arrayPos[j].y;

			if (m_elements[i]->getPosition()[j].x > max_x_projectile)
				max_x_projectile = m_elements[i]->getPosition()[j].x;

			if (m_elements[i]->getPosition()[j].y > max_y_projectile)
				max_y_projectile = m_elements[i]->getPosition()[j].y;




			if (arrayPos[j].x < min_x_obj)
				min_x_obj = arrayPos[j].x;

			if (arrayPos[j].y < min_y_obj)
				min_y_obj = arrayPos[j].y;

			if (m_elements[i]->getPosition()[j].x < min_x_projectile)
				min_x_projectile = m_elements[i]->getPosition()[j].x;

			if (m_elements[i]->getPosition()[j].y < min_y_projectile)
				min_y_projectile = m_elements[i]->getPosition()[j].y;
		}

		j = 0;

		if (max_x_obj > max_x_projectile)
		{
			if (max_x_projectile > min_x_obj)
				colX = true;
		}

		else
		{
			if (max_x_obj > min_x_projectile)
				colX = true;
		}

		if (max_y_obj > max_y_projectile)
		{
			if (max_y_projectile > min_y_obj)
				colY = true;
		}

		else
		{
			if (max_y_obj > min_y_projectile)
				colY = true;
		}
	
		if (colX && colY)
		{
			m_elements.erase(m_elements.begin() + i);
		}
		
	}

	return (colX && colY);

}

void Projectile_set::update()
{
	int i = 0;

	for (i = 0; i < m_elements.size(); i++)
	{
		m_elements[i]->update();
	}
}

void Projectile_set::render(sf::RenderWindow & window)
{
	int i = 0;

	for (i = 0; i < m_elements.size(); i++)
	{
		m_elements[i]->render(window);
	}
}

Projectile_set::~Projectile_set()
{

}
