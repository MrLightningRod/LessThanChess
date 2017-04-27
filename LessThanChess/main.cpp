#include <SFML/Graphics.hpp>
#include "Elements.h"
#include "Game.h"
#include "MainMenu.h"

int main()
{
	sf::RenderWindow window(sf::VideoMode(_WINDOW_WIDTH_, _WINDOW_HEIGHT_), "LessThanChess", sf::Style::Titlebar | sf::Style::Close);
	window.setVerticalSyncEnabled(true);
	Settings game;
	game.mode = 0;
	game.difficulty = 0;
	while ((game.mode != _GAME_OUT_) && ((game = MainMenu(window)).mode != _GAME_OUT_))
	{
		GameStart(game, window);
	}
	return 0;
}