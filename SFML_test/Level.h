#pragma once
#include <SFML/Graphics.hpp>
#include "Planet.h"
#include "Ship.h"
#include "Invader_S.h"
#include "Invader_M.h"
#include "Invader_L.h"
#include "Projectiles_Set.h"
#include <time.h>
#include <stdlib.h>

class Level
{
public:
	Level(sf::RenderWindow &window);
	Level(sf::RenderWindow &window, int small, int medium, int Large, int waves);

	void update(sf::RenderWindow &window);
	void render(sf::RenderWindow &window);

	void setEarthPos(sf::Vector2f pos);
	bool isFinished();
	~Level();

protected:
	void newWave();

private:
	vector<Invader_S> m_invaders_S;
	vector<Invader_M> m_invaders_M;
	vector<Invader_L> m_invaders_L;

	Projectile_set *m_projectile_set;
	Ship m_ship;
	Planet m_planet;

	bool m_win;
	int m_score;

	sf::Clock m_clock;
	sf::Time m_waveLength;

	int m_waveCounter;
	int m_waves;

	int m_screenHeight;
	int m_screenWidth;

	int m_smallNum;
	int m_mediumNum;
	int m_largeNum;

	bool pause;

	Entity m_bg;
};