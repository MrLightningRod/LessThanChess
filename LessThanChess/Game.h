#pragma once
#include <SFML/Graphics.hpp>
#include "Elements.h"
#include "Board.h"
#include <iostream>

#define _GAME_OFFLINE_ 1
#define _GAME_SERVER_ 2
#define _GAME_CONNECT_ 3
#define _GAME_AI_ 4
#define _GAME_OUT_ 5
#define _GAME_LOAD_ 6

#define _GAME_DIF_EASY_ 1
#define _GAME_DIF_MEDIUM_ 2
#define _GAME_DIF_HARD_ 3

typedef struct Settings
{
public:
	int mode;
	int difficulty;
} Settings;

void GameStart(Settings& game, sf::RenderWindow& window);