#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include "Constants.h"
#include "Elements.h"

#define _TEXTURE_FILE_ "chessfig.png"
#define _NEW_BOARD_FILE_ "new.sav"
#define _SAVE_BOARD_FILE_ "save.sav"

#define _PLAYER_NONE_ 2
#define _PLAYER_WHITE_ 0
#define _PLAYER_BLACK_ 1

const sf::Color _SQUARE_BLACK_COLOR_(150, 150, 150, 255);
const sf::Color _SQUARE_WHITE_COLOR_(255, 255, 255, 255);

#define _FIGURE_NONE_ -1
#define _FIGURE_KING_ 4
#define _FIGURE_QUENN_ 3
#define _FIGURE_BISHOP_ 2
#define _FIGURE_KNIGHT_ 1
#define _FIGURE_ROOK_ 0
#define _FIGURE_PAWN_ 5

#define _SQUARE_WHITE_ 0
#define _SQUARE_BLACK_ 1
#define _SQUARE_NONE_ 2

class Figure
{
private:
	int owner;
	int type;
	bool has_moved;
	sf::Texture texture;
	sf::RectangleShape figureBody;
public:
	Figure();
	void setTypeOwn(int typ, int own);
	void setPosition(sf::Vector2f position);
	~Figure();
	void draw(sf::RenderWindow& window);
	int getOwner();
	int getType();
};

typedef struct SquareStat
{
	bool underWhiteAttack;
	bool underBlackAttack;
	bool movingWhiteIn;
	bool movingWhiteOut;
	bool movingBlackIn;
	bool movingBlackOut;
} SquareStat;

class Square
{
private:
	sf::RectangleShape squareBody;
	Figure* whiteFigure;
	Figure* blackFigure;
public:
	SquareStat stat;
	int squareColor;
	Square();
	~Square();
	void setPosition(sf::Vector2f position);
	void setColor(sf::Color color);
	void setFigure(Figure* figure);
	Figure* getWhiteFigure();
	Figure* getBlackFigure();
	void draw(sf::RenderWindow& window);
	void resetStat();
};

class Board
{
private:
	sf::RectangleShape boardBody;
	Square squares[8][8];
	Figure figures[32];
	int player;
public:
	Board();
	~Board();
	void load(std::ifstream& in);
	void save(std::ofstream& out);
	void setPlayer(int pl);
	void draw(sf::RenderWindow& window);
};