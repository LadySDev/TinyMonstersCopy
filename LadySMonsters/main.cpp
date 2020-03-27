#include <SFML/Graphics.hpp>
#include "Game.h"
#include <iostream>

int main()
{
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;

	sf::RenderWindow window(sf::VideoMode(1152, 648), "TinyMonstersCopy", sf::Style::Default, settings);

	Game* game = new Game(window);

	sf::Clock clock;
	float elapsedTime = 0;
	while (window.isOpen())
	{
		elapsedTime = elapsedTime + clock.restart().asSeconds();

		while (elapsedTime > 1.f / 60.f)
		{
			//Poll Event
			sf::Event event;
			while (window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
				{
					window.close();
				}
				else
				{
					game->processEvent(event);
				}
			}

			//Update
			game->update(elapsedTime);

			window.clear();

			//Render
			game->render();

			window.display();
		}
	}

	return 0;
}