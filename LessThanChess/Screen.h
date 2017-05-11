#pragma once
#include <SFML/Graphics.hpp>
#include "Constants.h"
#include "Game.h"
#include "Board.h"

void ChangeScreen(sf::RenderWindow& window, int player);
void WinnerScreen(sf::RenderWindow& window, int winner);