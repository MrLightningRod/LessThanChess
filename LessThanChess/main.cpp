#include <SFML/Graphics.hpp>
#include "Elements.h"
#include "Game.h"
#include "MainMenu.h"

int main()
{
	sf::RenderWindow window(sf::VideoMode(_WINDOW_WIDTH_, _WINDOW_HEIGHT_), "LessThanChess", sf::Style::Titlebar | sf::Style::Close);
	window.setVerticalSyncEnabled(true);

	Game game = MainMenu(window);
	return 0;
}