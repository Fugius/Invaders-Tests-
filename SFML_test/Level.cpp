#include "Level.h"

Level::Level(sf::RenderWindow & window) : m_planet(sf::Vector2f(window.getSize().x/2 - 65, window.getSize().y/2 - 65), 130.0f, sf::Vector2f(window.getSize().x, window.getSize().y)), m_ship(sf::Vector2f(50, 50), sf::Vector2f(window.getSize().x, window.getSize().y), sf::Vector2f(130, 130)), m_bg(sf::Vector2f(0, 0), sf::Vector2f(window.getSize().x, window.getSize().y), "Ressources/textures/Background.png")
{
	m_clock.restart();
	m_waveLength = sf::seconds(2);

	m_waveCounter = 2;
	m_waves = m_waveCounter;

	m_smallNum = 4;
	m_mediumNum = 6;
	m_largeNum = 2;

	m_win = false;
	m_score = 0;

	m_screenWidth = window.getSize().x;
	m_screenHeight = window.getSize().y;

	pause = false;

	m_projectile_set = new Projectile_set();

	m_projectile_set->add_projectile(sf::Vector2f(0, 0), sf::Vector2f(1280, 720), Invaders);
	m_projectile_set->add_projectile(sf::Vector2f(1280, 0), sf::Vector2f(0, 720), Invaders);
	m_projectile_set->add_projectile(sf::Vector2f(1280, 720), sf::Vector2f(0, 0), Invaders);
	m_projectile_set->add_projectile(sf::Vector2f(0, 720), sf::Vector2f(1280, 0), Invaders);

}

Level::Level(sf::RenderWindow & window, int small, int medium, int large, int waves) : m_planet(sf::Vector2f(window.getSize().x / 2 - 65, window.getSize().y / 2 - 65), 130.0f, sf::Vector2f(window.getSize().x, window.getSize().y)), m_ship(sf::Vector2f(50, 50), sf::Vector2f(window.getSize().x, window.getSize().y), sf::Vector2f(130, 130)), m_bg(sf::Vector2f(0, 0), sf::Vector2f(window.getSize().x, window.getSize().y), "Ressources/textures/Background.png")
{
	m_clock.restart();
	m_waveLength = sf::seconds(10.0f);

	m_waveCounter = waves;
	m_waves = m_waveCounter;

	m_smallNum = small;
	m_mediumNum = medium;
	m_largeNum = large;

	m_win = false;
	m_score = 0;

	pause = false;

	m_projectile_set = new Projectile_set();
}

void Level::update(sf::RenderWindow & window)
{
	//events

	sf::Event event;
	while (window.pollEvent(event))
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			m_ship.move(m_left);

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			m_ship.move(m_right);

		if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Left && !sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			m_ship.stopMoving();

		if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Right && !sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			m_ship.stopMoving();

		if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			window.close();

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::P))
			pause = true;

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
			pause = false;

	}

	if (!pause)
	{
		//update Everything
		m_planet.update();
		m_ship.update();

		for (int i = 0; i < m_invaders_S.size(); i++)
		{
			m_invaders_S[i].update();
		}

		for (int i = 0; i < m_invaders_M.size(); i++)
		{
			m_invaders_M[i].update(m_projectile_set);
		}

		for (int i = 0; i < m_invaders_L.size(); i++)
		{
			m_invaders_L[i].update();
		}

		m_projectile_set->update();

		//collision check

		//planet

		sf::Vector2f temp[4];
		int r = 0;
		temp[0] = sf::Vector2f(m_planet.getPosition()[0].x + r, m_planet.getPosition()[0].y + r);
		temp[1] = sf::Vector2f(m_planet.getPosition()[1].x - r, m_planet.getPosition()[1].y + r);
		temp[2] = sf::Vector2f(m_planet.getPosition()[2].x - r, m_planet.getPosition()[2].y - r);
		temp[3] = sf::Vector2f(m_planet.getPosition()[3].x + r, m_planet.getPosition()[3].y - r);

		if (m_projectile_set->check_collisions(m_planet.getPosition(), Defender))
		{
			m_planet.getDamage();
		}

	/*	if (m_projectile_set->check_collisions(m_ship.getPosition(), Defender))
		{
			m_ship.getDamage();
		}*/

		//New wave ?
		if (m_clock.getElapsedTime() >= m_waveLength)
		{
			m_clock.restart();
			m_score += 100;

			//newWave();
		}
	}
}

void Level::render(sf::RenderWindow & window)
{
	m_bg.render(&window);
	m_projectile_set->render(window);
	m_planet.render(window);
	m_ship.render(window);

	for (int i = 0; i < m_invaders_S.size(); i++)
	{
		m_invaders_S[i].render(window);
	}

	for (int i = 0; i < m_invaders_M.size(); i++)
	{
		m_invaders_M[i].render(window);
	}

	for (int i = 0; i < m_invaders_L.size(); i++)
	{
		m_invaders_L[i].render(window);
	}
}

void Level::setEarthPos(sf::Vector2f pos)
{
	m_planet.setPosition(pos);
}

bool Level::isFinished()
{
	return (m_invaders_S.size() + m_invaders_M.size() + m_invaders_L.size() <= 0 && m_waveCounter == 0);
}

Level::~Level()
{
}

void Level::newWave()
{
	srand(time(NULL));
	if (m_waveCounter >= m_waves / 2)
	{
		for (int i = 0; i < m_smallNum / 2; i++)
		{
			if (rand() % 2 == 1)
				m_invaders_S.emplace_back(sf::Vector2f(35, 35), sf::Vector2f(m_screenWidth, m_screenHeight), m_right);
			else
				m_invaders_S.emplace_back(sf::Vector2f(35, 35), sf::Vector2f(m_screenWidth, m_screenHeight), m_left);
		}

		for (int i = 0; i < m_mediumNum / 3; i++)
		{
			if (rand() % 2 == 1)
				m_invaders_M.emplace_back(sf::Vector2f(50, 50), sf::Vector2f(m_screenWidth, m_screenHeight), m_right);
			else
				m_invaders_M.emplace_back(sf::Vector2f(50, 50), sf::Vector2f(m_screenWidth, m_screenHeight), m_left);
		}

		for (int i = 0; i < m_smallNum / 2; i++)
		{
			if (rand() % 2 == 1)
				m_invaders_L.emplace_back(sf::Vector2f(65, 65), sf::Vector2f(m_screenWidth, m_screenHeight), m_right);
			else
				m_invaders_L.emplace_back(sf::Vector2f(65, 65), sf::Vector2f(m_screenWidth, m_screenHeight), m_left);
		}
		m_waveCounter--;
	}

	else if (m_waveCounter > 0)
	{
		for (int i = 0; i < m_smallNum / 4; i++)
		{
			if (rand() % 2 == 1)
				m_invaders_S.emplace_back(sf::Vector2f(35, 35), sf::Vector2f(m_screenWidth, m_screenHeight), m_right);
			else
				m_invaders_S.emplace_back(sf::Vector2f(35, 35), sf::Vector2f(m_screenWidth, m_screenHeight), m_left);
		}

		for (int i = 0; i < m_mediumNum / 2; i++)
		{
			if (rand() % 2 == 1)
				m_invaders_M.emplace_back(sf::Vector2f(50, 50), sf::Vector2f(m_screenWidth, m_screenHeight), m_right);
			else
				m_invaders_M.emplace_back(sf::Vector2f(50, 50), sf::Vector2f(m_screenWidth, m_screenHeight), m_left);
		}

		for (int i = 0; i < m_smallNum / 1.5; i++)
		{
			if (rand() % 2 == 1)
				m_invaders_L.emplace_back(sf::Vector2f(65, 65), sf::Vector2f(m_screenWidth, m_screenHeight), m_right);
			else
				m_invaders_L.emplace_back(sf::Vector2f(65, 65), sf::Vector2f(m_screenWidth, m_screenHeight), m_left);
		}
		m_waveCounter--;
	}
}
