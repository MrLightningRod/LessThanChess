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

Square::Square()
{
	whiteFigure = NULL;
	blackFigure = NULL;
	squareBody.setSize(sf::Vector2f(80, 80));
	squareBody.setPosition(sf::Vector2f(100, 100));
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