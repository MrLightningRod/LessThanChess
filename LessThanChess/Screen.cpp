#include "Screen.h"
#include "Constants.h"
#include <iostream>

void ChangeScreen(sf::RenderWindow& window, int player)
{
	sf::Color back_color;
	sf::Color text_color;
	sf::Font font;
	font.loadFromFile(_FONT_FILE_);
	sf::Text text;
	text.setFont(font);
	if (player == _PLAYER_BLACK_)
	{
		back_color = sf::Color(0, 0, 0, 255);
		text_color = sf::Color(255, 255, 255, 255);
	}
	else
	{
		back_color = sf::Color(255, 255, 255, 255);
		text_color = sf::Color(0, 0, 0, 255);
	}
	if (player == _PLAYER_BLACK_)
	{
		text.setString("BLACK");
	}
	else
	{
		text.setString("WHITE");
	}
	text.setFillColor(text_color);
	text.setCharacterSize(90);
	sf::FloatRect textRect;
	textRect = text.getGlobalBounds();
	text.setPosition(sf::Vector2f(_WINDOW_WIDTH_ / 2, _WINDOW_HEIGHT_ / 2) - sf::Vector2f(textRect.width / 2.f, 100.f));

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::MouseButtonPressed)
			{
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					return;
				}
			}
		}

		// render
		window.clear(back_color);
		window.draw(text);
		window.display();
		//
	}
}

void WinnerScreen(sf::RenderWindow& window, int winner)
{
	std::cout << winner << std::endl;
	sf::Color back_color;
	sf::Color text_color;
	sf::Font font;
	font.loadFromFile(_FONT_FILE_);
	sf::Text text;
	sf::Text drawWhite;
	sf::Text drawBlack;
	sf::RectangleShape rectWhite;
	sf::RectangleShape rectBlack;
	rectWhite.setSize(sf::Vector2f(_WINDOW_WIDTH_, _WINDOW_HEIGHT_ / 2.f));
	rectBlack.setSize(sf::Vector2f(_WINDOW_WIDTH_, _WINDOW_HEIGHT_ / 2.f));
	rectWhite.setPosition(sf::Vector2f(0, 0));
	rectBlack.setPosition(sf::Vector2f(0, _WINDOW_HEIGHT_ / 2.f));
	rectWhite.setFillColor(sf::Color(255, 255, 255, 255));
	rectBlack.setFillColor(sf::Color(0, 0, 0, 255));
	drawWhite.setFont(font);
	drawBlack.setFont(font);
	drawWhite.setString("DRAW");
	drawBlack.setString("DRAW");
	drawWhite.setFillColor(sf::Color(0, 0, 0, 255));
	drawBlack.setFillColor(sf::Color(255, 255, 255, 255));
	sf::FloatRect drawRect;
	drawRect = drawWhite.getGlobalBounds();
	drawWhite.setCharacterSize(60);
	drawBlack.setCharacterSize(60);

	drawWhite.setPosition(sf::Vector2f(_WINDOW_WIDTH_ / 2.f - drawRect.width, _WINDOW_HEIGHT_ / 4.f));
	drawBlack.setPosition(sf::Vector2f(_WINDOW_WIDTH_ / 2.f - drawRect.width, 3.f * _WINDOW_HEIGHT_ / 4.f));

	text.setFont(font);
	if (winner == _PLAYER_BLACK_)
	{
		back_color = sf::Color(0, 0, 0, 255);
		text_color = sf::Color(255, 255, 255, 255);
	}
	else
	{
		back_color = sf::Color(255, 255, 255, 255);
		text_color = sf::Color(0, 0, 0, 255);
	}
	if (winner == _PLAYER_BLACK_)
	{
		text.setString("BLACK WINS");
	}
	else
	{
		text.setString("WHITE WINS");
	}
	text.setFillColor(text_color);
	text.setCharacterSize(90);
	sf::FloatRect textRect;
	textRect = text.getGlobalBounds();
	text.setPosition(sf::Vector2f(_WINDOW_WIDTH_ / 2, _WINDOW_HEIGHT_ / 2) - sf::Vector2f(textRect.width / 2.f, 100.f));

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::MouseButtonPressed)
			{
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					return;
				}
			}
		}

		// render
		window.clear(back_color);
		if ((winner == _PLAYER_BLACK_) || (winner == _PLAYER_WHITE_))
		{
			window.draw(text);
		}
		else
		{
			window.draw(rectWhite);
			window.draw(rectBlack);
			window.draw(drawWhite);
			window.draw(drawBlack);
		}
		window.display();
		//
	}
}