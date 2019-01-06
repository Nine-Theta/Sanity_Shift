
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Game.h"

using namespace std;
int main(int argc, char * argv[])
{
	//sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
	//shape.setFillColor(sf::Color::Green);
	ios_base::sync_with_stdio(false);
	sge::Game &game = sge::Game::GetInstance();
	game.Run();
	/*while (game.isOpen())
	{
		sf::Event event;
		while (game.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				game.close();
		}

		game.clear();
		game.draw(shape);
		game.display();
	}*/
	return 0;
}