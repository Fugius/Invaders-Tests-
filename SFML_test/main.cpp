#include <SFML/Graphics.hpp>
#include "Level.h"

enum Size {WIDTH = 1280, HEIGHT = 720};

int main()
{


	sf::ContextSettings settings;
	settings.antialiasingLevel = 16;

	sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Earth Invaders", sf::Style::Default, settings);

	sf::Clock clock;
	sf::Time t1 = sf::milliseconds(1000 / 60);

	sf::Clock clock2;
	sf::Time t2 = sf::milliseconds(1000 / 60);

	bool pause = false;

	Level *level = new Level(window);

	while (window.isOpen())
	{
		//update
		if (clock.getElapsedTime() >= t1 && !pause)
		{
			clock.restart();
			
			level->update(window);
		}

		//render
		if (clock2.getElapsedTime() >= t2 && !pause)
		{
			clock2.restart();

			window.clear();

			level->render(window);

			window.display();
		}

	}

	return 0;
}