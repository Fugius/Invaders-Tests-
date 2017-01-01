#include <SFML/Graphics.hpp>
#include "Planet.h"
#include "Ship.h"
#include "Invader_S.h"
#include "Invader_M.h"
#include "Invader_L.h"
#include "Projectiles_Set.h"

enum Size {WIDTH = 1280, HEIGHT = 720};

int main()
{


	sf::ContextSettings settings;
	settings.antialiasingLevel = 16;

	sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Earth Invaders", sf::Style::Default, settings);

	sf::Clock clock;
	sf::Time t1 = sf::seconds(1/60);

	bool pause = false;

	float planetSize = 130;

	Planet p(sf::Vector2f(WIDTH / 2 - planetSize/2, HEIGHT / 2 - planetSize / 2), planetSize, sf::Vector2f(WIDTH, HEIGHT));
	Ship s(sf::Vector2f(50, 50), sf::Vector2f(WIDTH, HEIGHT), sf::Vector2f(planetSize, planetSize));
	Invader_S i1(sf::Vector2f(35, 35), sf::Vector2f(WIDTH, HEIGHT), m_right);
	Invader_M i2(sf::Vector2f(50, 50), sf::Vector2f(WIDTH, HEIGHT), m_left);
	Invader_L i3(sf::Vector2f(65, 65), sf::Vector2f(WIDTH, HEIGHT), m_right);
	Entity background(sf::Vector2f(0, 0), sf::Vector2f(WIDTH, HEIGHT), "Ressources/textures/background.png");
	Projectile_set prs;

	prs.add_projectile(sf::Vector2f(0, 0), sf::Vector2f(WIDTH, HEIGHT), Defender);


	while (window.isOpen())
	{
		//events
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
				window.close();

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			{
				s.move(m_left);
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			{
				s.move(m_right);
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::P))
			{
				pause = true;
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
			{
				pause = false;
			}


			if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Left && !sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
				s.stopMoving();

			if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Right && !sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
				s.stopMoving();
		}

		//update
		if (clock.getElapsedTime() >= t1 && !pause)
		{
			clock.restart();
			p.update();
			s.update();
			i1.update();
			i2.update();
			i3.update();
			prs.update();

			prs.check_collisions(p.getPosition());
			
			
		}

		//render
		background.render(&window);
		p.render(window);
		s.render(window);
		i1.render(window);
		i2.render(window);
		i3.render(window);
		prs.render(window);
		window.display();
	}

	return 0;
}