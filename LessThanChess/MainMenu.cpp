#include "MainMenu.h"
#include "Elements.h"
#include "Constants.h"
#include <iostream>

Settings MainMenu(sf::RenderWindow& window)
{
	Settings result;
	result.mode = _GAME_OFFLINE_;
	result.difficulty = _GAME_DIF_EASY_;
	ButtonsManager buttList;


	// page layout (it's not ok, but I'll fix it in the future, lol)
	Button start("START", sf::Vector2f(_WINDOW_WIDTH_ / 2.f - 320, 100), sf::Vector2f(640, 50));
	buttList.push(&start);

	Button easy("EASY", sf::Vector2f(_WINDOW_WIDTH_ / 2.f - 320, 160), sf::Vector2f(200, 40));
	easy.setTrigger(true);
	easy.setTriggered(true);
	buttList.push(&easy);

	Button medium("MEDIUM", sf::Vector2f(_WINDOW_WIDTH_ / 2.f - 100, 160), sf::Vector2f(200, 40));
	medium.setTrigger(true);
	buttList.push(&medium);

	Button hard("HARD", sf::Vector2f(_WINDOW_WIDTH_ / 2.f + 120, 160), sf::Vector2f(200, 40));
	hard.setTrigger(true);
	buttList.push(&hard);

	Button offline("HOTSEAT", sf::Vector2f(_WINDOW_WIDTH_ / 2.f - 320, 210), sf::Vector2f(200, 40));
	offline.setTrigger(true);
	offline.setTriggered(true);
	buttList.push(&offline);

	Button online("ONLINE", sf::Vector2f(_WINDOW_WIDTH_ / 2.f - 100, 210), sf::Vector2f(200, 40));
	online.setActive(false);
	buttList.push(&online);

	Button ai("AI", sf::Vector2f(_WINDOW_WIDTH_ / 2.f + 120, 210), sf::Vector2f(200, 40));
	ai.setActive(false);
	buttList.push(&ai);

	Button connect("CONNECT", sf::Vector2f(_WINDOW_WIDTH_ / 2.f - 320, 280), sf::Vector2f(640, 50));
	connect.setActive(false);
	buttList.push(&connect);

	Button load("LOAD", sf::Vector2f(_WINDOW_WIDTH_ / 2.f - 320, 360), sf::Vector2f(640, 50));
	load.setActive(true);
	buttList.push(&load);

	Button quit("QUIT", sf::Vector2f(_WINDOW_WIDTH_ / 2.f - 320, 440), sf::Vector2f(640, 50));
	buttList.push(&quit);
	//


	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::MouseMoved)
			{
				sf::Vector2f mouse_position(event.mouseMove.x, event.mouseMove.y);
				buttList.onCover(mouse_position);
			}

			if (event.type == sf::Event::MouseButtonPressed)
			{
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					sf::Vector2f mouse_position(event.mouseButton.x, event.mouseButton.y);
					Button* clicked = buttList.onClick(mouse_position);
					if (clicked == &start)
					{
						return result;
					}
					if (clicked == &quit)
					{
						result.mode = _GAME_OUT_;
						window.close();
						return result;
					}
					if (clicked == &easy)
					{
						easy.setTriggered(true);
						medium.setTriggered(false);
						hard.setTriggered(false);
						result.difficulty = _GAME_DIF_EASY_;
					}
					if (clicked == &medium)
					{
						easy.setTriggered(false);
						medium.setTriggered(true);
						hard.setTriggered(false);
						result.difficulty = _GAME_DIF_MEDIUM_;
					}
					if (clicked == &hard)
					{
						easy.setTriggered(false);
						medium.setTriggered(false);
						hard.setTriggered(true);
						result.difficulty = _GAME_DIF_HARD_;
					}
					if (clicked == &load)
					{
						result.mode = _GAME_LOAD_;
						return result;
					}
				}
			}
			
			if (event.type == sf::Event::Closed)
			{
				result.mode = _GAME_OUT_;
				window.close();
			}
		}


		// render
		window.clear(_BACKGROUND_);
		buttList.draw(window);
		window.display();
		//
	}

	return result;
}