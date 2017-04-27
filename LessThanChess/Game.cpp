#include "Game.h"

void GameStart(Settings& game, sf::RenderWindow& window)
{
	ButtonsManager buttList;

	Board board;
	std::ifstream loadf;
	if (game.mode == _GAME_LOAD_)
	{
		loadf.open(_SAVE_BOARD_FILE_);
		loadf >> game.mode;
		loadf >> game.difficulty;
	}
	else
	{
		loadf.open(_NEW_BOARD_FILE_);
	}
	board.load(loadf);
	loadf.close();
	board.setPlayer(_PLAYER_WHITE_);

	Button cancel("CANCEL", sf::Vector2f(240, 680), sf::Vector2f(240, 50));
	cancel.setActive(false);
	buttList.push(&cancel);

	Button finish("FINISH", sf::Vector2f(520, 680), sf::Vector2f(240, 50));
	finish.setActive(false);
	buttList.push(&finish);

	Button save("SAVE", sf::Vector2f(240, 740), sf::Vector2f(240, 50));
	save.setActive((game.mode == _GAME_OFFLINE_) || (game.mode == _GAME_AI_));
	buttList.push(&save);

	Button surrender("SURRENDER", sf::Vector2f(520, 740), sf::Vector2f(240, 50));
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
					if (clicked == &save)
					{
						std::ofstream savef;
						savef.open(_SAVE_BOARD_FILE_);
						savef << game.mode << " " << game.difficulty << std::endl;
						board.save(savef);
						savef.close();
					}
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
		board.draw(window);
		window.display();
		//
	}
}