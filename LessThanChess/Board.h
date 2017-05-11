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
#define _PLAYER_BOTH_ 3

const sf::Color _SQUARE_BLACK_COLOR_(150, 150, 150, 255);
const sf::Color _SQUARE_WHITE_COLOR_(255, 255, 255, 255);
const sf::Color _SQUARE_WHITE_AVAILABLE_COLOR_(90, 200, 90, 255);
const sf::Color _SQUARE_BLACK_AVAILABLE_COLOR_(50, 160, 50, 255);
const sf::Color _SQUARE_WHITE_COVERED_COLOR_(120, 200, 225, 255);
const sf::Color _SQUARE_BLACK_COVERED_COLOR_(40, 120, 165, 255);
const sf::Color _SQUARE_WHITE_READY_COLOR_(225, 225, 40, 255);
const sf::Color _SQUARE_BLACK_READY_COLOR_(185, 185, 0, 255);


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
	sf::Texture texture;
	sf::RectangleShape figureBody;
public:
	bool hasMoved;
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
	bool underAttack[2];
	bool movingIn[2];
	bool movingOut[2];
	bool available;
	bool covered;
} SquareStat;

class Square
{
private:
	sf::RectangleShape squareBody;
public:
	Figure* figure[2];
	SquareStat stat;
	int squareColor;
	Square();
	~Square();
	void setPosition(sf::Vector2f position);
	void setColor(sf::Color color);
	void setFigure(Figure* fig);
	Figure* getFigure(int player);
	void draw(sf::RenderWindow& window);
	void resetStat();
	bool contains(sf::Vector2f pos);
	bool isFree();
	bool isFree(int player);
};

typedef struct Move
{
	sf::Vector2i start;
	sf::Vector2i end;
} Move;

class Board
{
private:
	sf::RectangleShape boardBody;
	Square squares[8][8];
	Figure figures[32];
	int player;
	int movesPlayer[2];
	bool moveStarted;
	bool castling[2];
	Move moves[2][4];
public:
	int movesDone;
	int winner;
	Board();
	~Board();
	void load(std::ifstream& in);
	void save(std::ofstream& out);
	void setPlayer(int pl);
	int getPlayer();
	void draw(sf::RenderWindow& window);
	bool contains(sf::Vector2f pos);
	void onCover(sf::Vector2f pos);
	void setAvailable(sf::Vector2i start);
	void resetAvailable();
	void resetStat();
	void onClick(sf::Vector2f pos);
	void countMoves();
	void nextPlayer();
};