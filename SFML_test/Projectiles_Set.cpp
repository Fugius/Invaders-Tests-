#include "Projectiles_Set.h"

Projectile_set::Projectile_set()
{
	m_e = new Entity(sf::Vector2f(0, 0), sf::Vector2f(0, 0), "Ressources/textures/test.png");
}

void Projectile_set::add_projectile(sf::Vector2f origin, sf::Vector2f target, Team team)
{
	m_elements.push_back(new Projectile(origin, target, team));
}

bool Projectile_set::check_collisions(sf::Vector2f arrayPos[], Team team)
{

	float maxx = std::numeric_limits<float>::min(), maxy = std::numeric_limits<float>::min();
	float minx = std::numeric_limits<float>::max(), miny = std::numeric_limits<float>::max();

	bool coolision = false;
	
	for (int i = 0; i < m_elements.size(); i++)
	{
		if (team != m_elements[i]->getTeam())
		{

			maxx = std::numeric_limits<float>::min(), maxy = std::numeric_limits<float>::min();
			minx = std::numeric_limits<float>::max(), miny = std::numeric_limits<float>::max();

			for (int j = 0; j < 4; j++)
			{
				maxx = std::max(m_elements[i]->getPosition()[j].x, maxx);
				maxy = std::max(m_elements[i]->getPosition()[j].y, maxy);
			}

			for (int k = 0; k < 4; k++)
			{
				minx = std::min(m_elements[i]->getPosition()[k].x, minx);
				miny = std::min(m_elements[i]->getPosition()[k].y, miny);
			}

			bool p1 = false;
			bool p2 = false;
			bool p3 = false;
			bool p4 = false;

			if ((arrayPos[0].x >= minx && arrayPos[0].y >= miny) && (arrayPos[0].x <= maxx && arrayPos[0].y <= maxy))
				p1 = true;

			if ((arrayPos[1].x <= maxx && arrayPos[1].y <= maxy) && (arrayPos[1].x > minx && arrayPos[1].y > miny))
				p2 = true;

			if ((arrayPos[2].x <= maxx && arrayPos[2].y <= maxy) && (arrayPos[2].x > minx && arrayPos[2].y > miny))
				p3 = true;

			if ((arrayPos[3].x >= minx && arrayPos[3].y >= miny) && (arrayPos[3].x <= maxx && arrayPos[3].y <= maxy))
				p4 = true;

			sf::Vector2f pos[4] = {
				sf::Vector2f(minx, miny),
				sf::Vector2f(maxx, miny),
				sf::Vector2f(maxx, maxy),
				sf::Vector2f(minx, maxy)
			};

			if ((pos[0].x >= arrayPos[0].x && pos[0].y >= arrayPos[0].y) && (pos[0].x <= arrayPos[1].x && pos[0].y <= arrayPos[2].y))
				p1 = true;

			if ((pos[1].x <= arrayPos[1].x && pos[1].y <= arrayPos[1].y) && (pos[1].x >= arrayPos[0].x && pos[1].y >= arrayPos[3].y))
				p2 = true;

			if ((pos[2].x <= arrayPos[2].x && pos[2].y <= arrayPos[1].y) && (pos[2].x >= arrayPos[3].x && pos[1].y >= arrayPos[3].y))
				p3 = true;

			if ((pos[3].x >= arrayPos[3].x && pos[3].y >= arrayPos[0].y) && (pos[3].x <= arrayPos[1].x && pos[3].y <= arrayPos[3].y))
				p4 = true;

			cout << endl << endl << i << " : max X = " << maxx << ", max Y = " << maxy << ", min X = " << minx << ", min Y = " << miny << endl << i << " : max x - min x = " << maxx- minx << ", max y - min y = " << maxy - miny << endl;
			m_e->move(pos);
			

			if (p1 || p2 || p3 || p4)
			{
				m_elements.erase(m_elements.begin() + i);
				coolision = true;
				cout << "lol" << endl;
			}
				
		}
	}

	return coolision;

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

	m_e->render(&window);
}

Projectile_set::~Projectile_set()
{

}
