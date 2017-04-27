#include "Game.h"

void GameStart(Settings& game, sf::RenderWindow& window)
{
	ButtonsManager buttList;

	Button save("SAVE", sf::Vector2f(150, 700), sf::Vector2f(300, 50));
	save.setActive(false);
	buttList.push(&save);

	Button surrender("SURRENDER", sf::Vector2f(550, 700), sf::Vector2f(300, 50));
	surrender.setActive(false);
	buttList.push(&surrender);


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

				}
			}

			if (event.type == sf::Event::Closed)
			{
				game.mode = _GAME_OUT_;
				window.close();
			}
		}


		// render
		window.clear(_BACKGROUND_);
		buttList.draw(window);
		window.display();
		//
	}
}