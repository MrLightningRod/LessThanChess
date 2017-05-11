#include "Board.h"

Figure::Figure()
{
	owner = 0;
	hasMoved = false;
	type = _FIGURE_NONE_;
	texture.loadFromFile(_TEXTURE_FILE_, sf::IntRect(0, 0, 80, 80));
	figureBody.setSize(sf::Vector2f(80, 80));
	figureBody.setPosition(sf::Vector2f(100, 100));
	figureBody.setTexture(&texture);
}

Figure::~Figure()
{

}

void Figure::setTypeOwn(int typ, int own)
{
	owner = own;
	type = typ;
	sf::IntRect textureRect(0, 0, 80, 80);
	if (owner == _PLAYER_WHITE_)
	{
		textureRect.top += 80;
	}
	if (type != _FIGURE_NONE_)
	{
		textureRect.left += type * 80;
	}
	texture.loadFromFile(_TEXTURE_FILE_, textureRect);
	figureBody.setTexture(&texture, false);
}

void Figure::setPosition(sf::Vector2f position)
{
	figureBody.setPosition(position);
}

void Figure::draw(sf::RenderWindow& window)
{
	if (type != _FIGURE_NONE_)
	{
		window.draw(figureBody);
	}
}

int Figure::getOwner()
{
	return owner;
}

int Figure::getType()
{
	return type;
}

Square::Square()
{
	figure[0] = figure[1] = NULL;
	squareBody.setSize(sf::Vector2f(80, 80));
	squareBody.setPosition(sf::Vector2f(100, 100));
	resetStat();
	stat.underAttack[0] = stat.underAttack[1] = false;
}

Square::~Square()
{
	figure[0] = figure[1] = NULL;
}

void Square::setPosition(sf::Vector2f position)
{
	squareBody.setPosition(position);
	for (int i = 0; i < 2; i++)
	{
		if (figure[i] != NULL)
		{
			figure[i]->setPosition(position);
		}
	}
}

void Square::setColor(sf::Color color)
{
	squareBody.setFillColor(color);
}

void Square::setFigure(Figure* fig)
{
	fig->setPosition(squareBody.getPosition());
	figure[fig->getOwner()] = fig;
}

Figure* Square::getFigure(int player)
{
	return figure[player];
}

void Square::draw(sf::RenderWindow& window)
{
	if (squareColor == _SQUARE_WHITE_)
	{
		squareBody.setFillColor(_SQUARE_WHITE_COLOR_);
	}
	else
	{
		squareBody.setFillColor(_SQUARE_BLACK_COLOR_);
	}
	if (stat.movingIn[0] || stat.movingOut[0] || stat.movingIn[1] || stat.movingOut[1])
	{
		if (squareColor == _SQUARE_WHITE_)
		{
			squareBody.setFillColor(_SQUARE_WHITE_READY_COLOR_);
		}
		else
		{
			squareBody.setFillColor(_SQUARE_BLACK_READY_COLOR_);
		}
	}
	if (stat.available)
	{
		if (squareColor == _SQUARE_WHITE_)
		{
			squareBody.setFillColor(_SQUARE_WHITE_AVAILABLE_COLOR_);
		}
		else
		{
			squareBody.setFillColor(_SQUARE_BLACK_AVAILABLE_COLOR_);
		}
	}
	if (stat.covered)
	{
		if (squareColor == _SQUARE_WHITE_)
		{
			squareBody.setFillColor(_SQUARE_WHITE_COVERED_COLOR_);
		}
		else
		{
			squareBody.setFillColor(_SQUARE_BLACK_COVERED_COLOR_);
		}
	}
	window.draw(squareBody);
	for (int i = 0; i < 2; i++)
	{
		if (figure[i] != NULL)
		{
			figure[i]->draw(window);
		}
	}
}

void Square::resetStat()
{
	for (int i = 0; i < 2; i++)
	{
		stat.movingIn[i] = stat.movingOut[i] = false;
	}
	stat.covered = false;
	stat.available = false;
}

bool Square::contains(sf::Vector2f pos)
{
	return (squareBody.getGlobalBounds()).contains(pos);
}

bool Square::isFree(int player)
{
	return ((!stat.movingIn[player]) && ((figure[player] == NULL) || (stat.movingOut[player])));
}

bool Square::isFree()
{
	return (isFree(0) && isFree(1));
}

Board::Board()
{
	moveStarted = false;
	movesPlayer[0] = 0;
	movesPlayer[1] = 0;
	movesDone = 0;
	winner = _PLAYER_NONE_;
	castling[0] = false;
	castling[1] = false;
	boardBody.setFillColor(_BUTTON_COLOR_);
	boardBody.setSize(sf::Vector2f(640, 640));
	boardBody.setPosition(sf::Vector2f(180, 20));
	boardBody.setOutlineThickness(_BUTTON_OUTLINE_THICKNESS_);
	boardBody.setOutlineColor(_BUTTON_OUTLINE_COLOR_);
	player = _PLAYER_NONE_;
	for (int j = 0; j < 8; j++)
		for (int i = 0; i < 8; i++)
		{
			sf::Vector2f position(sf::Vector2f(80 * i, 80 * (7 - j)) + boardBody.getPosition());
			squares[i][j].setPosition(position);
			if ((i + j) % 2 == 0)
			{
				squares[i][j].setColor(_SQUARE_BLACK_COLOR_);
				squares[i][j].squareColor = _SQUARE_BLACK_;
			}
			else
			{
				squares[i][j].setColor(_SQUARE_WHITE_COLOR_);
				squares[i][j].squareColor = _SQUARE_WHITE_;
			}
		}
}

Board::~Board()
{

}

void Board::draw(sf::RenderWindow& window)
{
	window.draw(boardBody);
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
			squares[i][j].draw(window);
}

void Board::setPlayer(int pl)
{
	player = pl;
	for (int j = 0; j < 8; j++)
		for (int i = 0; i < 8; i++)
		{
			int x = i;
			int y = j;
			if (player == _PLAYER_WHITE_)
			{
				y = 7 - y;
			}
			else
			{
				x = 7 - x;
			}
			sf::Vector2f position(sf::Vector2f(80 * x, 80 * y) + boardBody.getPosition());
			squares[i][j].setPosition(position);
		}
}

void Board::load(std::ifstream& in)
{
	int owner;
	int type;
	bool has_moved;
	int num_figure = 0;
	for (int j = 0; j < 8; j++)
		for (int i = 0; i < 8; i++)
		{
			in >> owner >> type >> has_moved;
			if ((owner != _PLAYER_NONE_) && (type != _FIGURE_NONE_))
			{
				figures[num_figure].setTypeOwn(type, owner);
				figures[num_figure].hasMoved = has_moved;
				squares[i][j].setFigure(&figures[num_figure]);
				num_figure++;
			}
		}
}

void Board::save(std::ofstream & out)
{
	for (int j = 0; j < 8; j++)
	{
		for (int i = 0; i < 8; i++)
		{
			if ((squares[i][j].getFigure(0) == NULL) && (squares[i][j].getFigure(1) == NULL))
			{
				out << 2 << " " << 2 << " " << 0 << " ";
			}
			else
			{
				if (squares[i][j].getFigure(0) != NULL)
				{
					out << squares[i][j].getFigure(0)->getOwner() << " " << squares[i][j].getFigure(0)->getType() << " " << squares[i][j].getFigure(0)->hasMoved << " ";
				}
				else
				{
					out << squares[i][j].getFigure(1)->getOwner() << " " << squares[i][j].getFigure(1)->getType() << " " << squares[i][j].getFigure(1)->hasMoved << " ";
				}
			}
		}
		out << std::endl;
	}
}

bool Board::contains(sf::Vector2f pos)
{
	return (boardBody.getGlobalBounds()).contains(pos);
}

void Board::onCover(sf::Vector2f pos)
{
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
		{
			if (squares[i][j].contains(pos))
			{
				if (moveStarted)
				{
					squares[i][j].stat.covered = squares[i][j].stat.available;
				}
				else
				{
					squares[i][j].stat.covered = ((squares[i][j].getFigure(player) != NULL) && (!squares[i][j].stat.movingOut[player]));
				}
			}
			else
			{
				squares[i][j].stat.covered = false;
			}
		}
}

void Board::resetAvailable()
{
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
		{
			squares[i][j].stat.available = false;
		}
}

void Board::resetStat()
{
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
		{
			squares[i][j].resetStat();
		}
}

void Board::setAvailable(sf::Vector2i start)
{
	Figure* figure;
	bool dont_stop;
	int add_y;
	figure = squares[start.x][start.y].getFigure(player);
	//PAWN
	if (figure->getType() == _FIGURE_PAWN_)
	{
		add_y = -1;
		if (player == _PLAYER_WHITE_)
		{

			add_y = 1;
		}
		if ((0 <= start.x - 1) && (0 <= (start.y + add_y)) && ((start.y + add_y) <= 7))
		{
			if (squares[start.x - 1][start.y + add_y].isFree(player))
			{
				if (!squares[start.x - 1][start.y + add_y].isFree((player + 1) % 2))
				{
					squares[start.x - 1][start.y + add_y].stat.available = true;
				}
			}
		}
		if ((start.x + 1 <= 7) && (0 <= (start.y + add_y)) && ((start.y + add_y) <= 7))
		{
			if (squares[start.x + 1][start.y + add_y].isFree(player))
			{
				if (!squares[start.x + 1][start.y + add_y].isFree((player + 1) % 2))
				{
					squares[start.x + 1][start.y + add_y].stat.available = true;
				}
			}
		}
		if (dont_stop = ((0 <= start.y + add_y) && (start.y + add_y <= 7)))
		{
			if (dont_stop = (squares[start.x][start.y + add_y].isFree()))
			{
				squares[start.x][start.y + add_y].stat.available = true;
			}
		}
		if ((dont_stop) && (!figure->hasMoved))
		{
			if (squares[start.x][start.y + 2 * add_y].isFree())
			{
				squares[start.x][start.y + 2 * add_y].stat.available = true;
			}
		}
	}
	//

	//KING
	if (figure->getType() == _FIGURE_KING_)
	{
		for (int i = -1; i <= 1; i++)
			for (int j = -1; j <= 1; j++)
			{
				if ((i == 0) && (j == 0))
					continue;
				if ((0 <= start.x + i) && (start.x + i <= 7) && (0 <= start.y + j) && (start.y + j <= 7))
				{
					if (squares[start.x + i][start.y + j].isFree(player))
					{
						squares[start.x + i][start.y + j].stat.available = true;
					}
				}
			}
		if (!figure->hasMoved)
		{
			if (squares[0][start.y].getFigure(player) != NULL)
			{
				if (!squares[0][start.y].getFigure(player)->hasMoved)
				{
					dont_stop = true;
					for (int i = 1; i < 4; i++)
					{
						dont_stop &= squares[i][start.y].isFree();
					}
					squares[2][start.y].stat.available = dont_stop;
				}
			}
		}
		if (!figure->hasMoved)
		{
			if (squares[7][start.y].getFigure(player) != NULL)
			{
				if (!squares[7][start.y].getFigure(player)->hasMoved)
				{
					dont_stop = true;
					for (int i = 5; i < 7; i++)
					{
						dont_stop &= squares[i][start.y].isFree();
					}
					squares[6][start.y].stat.available = dont_stop;
				}
			}
		}
	}
	//

	//BISHOP
	if ((figure->getType() == _FIGURE_BISHOP_) || (figure->getType() == _FIGURE_QUENN_))
	{
		for (int i = 0; i < 2; i++)
		{
			for (int j = 0; j < 2; j++)
			{
				int step_x = -1 + i * 2;
				int step_y = -1 + j * 2;
				int add = 0;
				int x = start.x;
				int y = start.y;
				bool dont_stop = true;
				while (dont_stop)
				{
					x += step_x;
					y += step_y;
					if (dont_stop = ((0 <= x) && (x <= 7) && (0 <= y) && (y <= 7)))
					{
						if (dont_stop = squares[x][y].isFree(player))
						{
							squares[x][y].stat.available = true;
							dont_stop = squares[x][y].isFree();
						}
					}
				}
			}
		}
	}
	//

	//KNIGHT
	if (figure->getType() == _FIGURE_KNIGHT_)
	{
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 2; j++)
			{
				int x = start.x;
				int y = start.y;
				int step_x = -2 + i + (i > 1);
				int step_y = (-1 + 2 * j) * (1 + ((step_x + 1) % 2 == 0));
				x += step_x;
				y += step_y;
				if ((0 <= x) && (x <= 7) && (0 <= y) && (y <= 7))
				{
					if (squares[x][y].isFree(player))
					{
						squares[x][y].stat.available = true;
					}
				}
			}
		}
	}
	//

	//ROOK
	if ((figure->getType() == _FIGURE_ROOK_) || (figure->getType() == _FIGURE_QUENN_))
	{
		for (int i = 0; i < 4; i++)
		{
			int step_x =  -1 + i * 2;
			if (i > 1)
				step_x = 0;
			int step_y = -5 + i * 2;
			if (i < 2)
				step_y = 0;
			int add = 0;
			int x = start.x;
			int y = start.y;
			bool dont_stop = true;
			while (dont_stop)
			{
				x += step_x;
				y += step_y;
				if (dont_stop = ((0 <= x) && (x <= 7) && (0 <= y) && (y <= 7)))
				{
					if (dont_stop = squares[x][y].isFree(player))
					{
						squares[x][y].stat.available = true;
						dont_stop = squares[x][y].isFree();
					}
				}
			}
		}
	}
	//
}

void Board::onClick(sf::Vector2f pos)
{
	int x;
	int y;
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
		{
			if (squares[i][j].contains(pos))
			{
				x = i;
				y = j;
			}
		}
	if (!moveStarted)
	{
		if ((squares[x][y].getFigure(player) != NULL) && (!squares[x][y].stat.movingOut[player]))
		{
			setAvailable(sf::Vector2i(x, y));
			moveStarted = true;
			moves[player][movesDone].start.x = x;
			moves[player][movesDone].start.y = y;
			squares[x][y].stat.movingOut[player] = true;
		}
	}
	else
	{
		if ((x == moves[player][movesDone].start.x) && (y == moves[player][movesDone].start.y))
		{
			moveStarted = false;
			squares[x][y].stat.movingOut[player] = false;
			resetAvailable();
		}
		else
		{
			if (squares[x][y].stat.available)
			{
				moves[player][movesDone].end.x = x;
				moves[player][movesDone].end.y = y;
				int start_x = moves[player][movesDone].start.x;
				int start_y = moves[player][movesDone].start.y;

				//castling
				if (squares[start_x][start_y].getFigure(player)->getType() == _FIGURE_KING_)
					if (!squares[start_x][start_y].getFigure(player)->hasMoved)
					{
						if ((x == 2) || (x == 6))
						{
							castling[player] = true;
							moves[player][3].start.y = y;
							moves[player][3].end.y = y;
							if (x == 2)
							{
								moves[player][3].start.x = 0;
								moves[player][3].end.x = 3;
							}
							else
							{
								moves[player][3].start.x = 7;
								moves[player][3].end.x = 5;
							}
							squares[moves[player][3].start.x][moves[player][3].start.y].stat.movingOut[player] = true;
							squares[moves[player][3].end.x][moves[player][3].end.y].stat.movingIn[player] = true;
							squares[moves[player][3].end.x][moves[player][3].end.y].stat.underAttack[player] = true;
						}
					}
				//

				moves[player][movesDone].end.x = x;
				moves[player][movesDone].end.y = y;
				squares[x][y].stat.movingIn[player] = true;
				squares[x][y].stat.underAttack[player] = true;

				/*
				//PAWN'S NON ATTACK MOVE
				if (squares[start_x][start_y].getFigure(player)->getType() == _FIGURE_PAWN_)
				{
					if (moves[player][movesDone].start.x == x)
					{
						squares[x][y].stat.underAttack[player] = false;
					}
				}
				//
				*/

				movesDone++;
				moveStarted = false;
				resetAvailable();
			}
		}
	}
}

void Board::countMoves()
{
	for (int i = 0; i < 2; i++)
	{
		int pl = i;
		for (int j = 0; j < movesPlayer[pl]; j++)
		{
			int end_x = moves[pl][j].end.x;
			int end_y = moves[pl][j].end.y;
			int start_x = moves[pl][j].start.x;
			int start_y = moves[pl][j].start.y;
			squares[end_x][end_y].setFigure(squares[start_x][start_y].getFigure(pl));
			if ((squares[end_x][end_y].figure[pl]->getType() == _FIGURE_PAWN_) && (end_y == (7 - pl * 7)))
			{
				squares[end_x][end_y].figure[pl]->setTypeOwn(_FIGURE_QUENN_, pl);
			}
			squares[end_x][end_y].figure[pl]->hasMoved = true;
			squares[start_x][start_y].figure[pl] = NULL;
			int other_pl = (pl + 1) % 2;

			if (squares[end_x][end_y].stat.underAttack[other_pl])
			{
				if (squares[end_x][end_y].figure[pl]->getType() == _FIGURE_KING_)
				{
					if ((winner == pl) || (winner == _PLAYER_BOTH_))
					{
						winner = _PLAYER_BOTH_;
					}
					if (winner == _PLAYER_NONE_)
					{
						winner = other_pl;
					}
				}
				squares[end_x][end_y].figure[pl] = NULL;
			}
		}
		if (castling[pl])
		{
			int end_x = moves[pl][3].end.x;
			int end_y = moves[pl][3].end.y;
			int start_x = moves[pl][3].start.x;
			int start_y = moves[pl][3].start.y;
			squares[end_x][end_y].setFigure(squares[start_x][start_y].getFigure(player));
			squares[end_x][end_y].figure[pl]->hasMoved = true;
			squares[start_x][start_y].figure[pl] = NULL;
			int other_pl = (pl + 1) % 2;
			if (squares[end_x][end_y].stat.underAttack[other_pl])
			{
				if (squares[end_x][end_y].figure[pl]->getType() == _FIGURE_KING_)
				{
					if ((winner == pl) || (winner == _PLAYER_BOTH_))
					{
						winner = _PLAYER_BOTH_;
					}
					if (winner == _PLAYER_NONE_)
					{
						winner = other_pl;
					}
				}
				squares[end_x][end_y].figure[pl] = NULL;
			}
		}
		for (int k = 0; k < 8; k++)
			for (int l = 0; l < 8; l++)
			{
				if (squares[k][l].stat.underAttack[(pl + 1) % 2])
				{
					if (squares[k][l].figure[pl] != NULL)
						if (squares[k][l].figure[pl]->getType() == _FIGURE_KING_)
						{
							if ((winner == pl) || (winner == _PLAYER_BOTH_))
							{
								winner = _PLAYER_BOTH_;
							}
							if (winner == _PLAYER_NONE_)
							{
								winner = (pl + 1) % 2;
							}
						}
					squares[k][l].figure[pl] = NULL;
				}
			}
	}
	movesPlayer[0] = movesPlayer[1] = 0;
	movesDone = 0;
	resetAvailable();
	resetStat();
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
			squares[i][j].stat.underAttack[0] = squares[i][j].stat.underAttack[1] = false;
}

void Board::nextPlayer()
{
	movesPlayer[player] = movesDone;
	movesDone = 0;
	resetStat();
	setPlayer((player + 1) % 2);
	if (player == _PLAYER_WHITE_)
		countMoves();
}

int Board::getPlayer()
{
	return player;
}