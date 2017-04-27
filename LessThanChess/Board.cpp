#include "Board.h"

Figure::Figure()
{
	owner = 0;
	has_moved = false;
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
	whiteFigure = NULL;
	blackFigure = NULL;
	squareBody.setSize(sf::Vector2f(80, 80));
	squareBody.setPosition(sf::Vector2f(100, 100));
	this->resetStat();
}

Square::~Square()
{
	whiteFigure = NULL;
	blackFigure = NULL;
}

void Square::setPosition(sf::Vector2f position)
{
	squareBody.setPosition(position);
	if (whiteFigure != NULL)
	{
		whiteFigure->setPosition(position);
	}
	if (blackFigure != NULL)
	{
		blackFigure->setPosition(position);
	}
}

void Square::setColor(sf::Color color)
{
	squareBody.setFillColor(color);
}

void Square::setFigure(Figure* figure)
{
	figure->setPosition(squareBody.getPosition());
	if (figure->getOwner() == _PLAYER_WHITE_)
	{
		whiteFigure = figure;
	}
	else
	{
		blackFigure = figure;
	}
}

Figure* Square::getBlackFigure()
{
	return blackFigure;
}

Figure* Square::getWhiteFigure()
{
	return whiteFigure;
}

void Square::draw(sf::RenderWindow& window)
{
	window.draw(squareBody);
	if (whiteFigure != NULL)
	{
		whiteFigure->draw(window);
	}
	if (blackFigure != NULL)
	{
		blackFigure->draw(window);
	}
}

void Square::resetStat()
{
	stat.movingBlackIn = false;
	stat.movingBlackOut = false;
	stat.movingWhiteIn = false;
	stat.movingWhiteOut = false;
	stat.underBlackAttack = false;
	stat.underWhiteAttack = false;
}

Board::Board()
{
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
	int num_figure = 0;
	for (int j = 0; j < 8; j++)
		for (int i = 0; i < 8; i++)
		{
			in >> owner >> type;
			if ((owner != _PLAYER_NONE_) && (type != _FIGURE_NONE_))
			{
				figures[num_figure].setTypeOwn(type, owner);
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
			if ((squares[i][j].getBlackFigure() == NULL) && (squares[i][j].getWhiteFigure() == NULL))
			{
				out << 2 << " " << 2 << " ";
			}
			else
			{
				if (squares[i][j].getBlackFigure() != NULL)
				{
					out << squares[i][j].getBlackFigure()->getOwner() << " " << squares[i][j].getBlackFigure()->getType() << " ";
				}
				else
				{
					out << squares[i][j].getWhiteFigure()->getOwner() << " " << squares[i][j].getWhiteFigure()->getType() << " ";
				}
			}
		}
		out << std::endl;
	}
}
