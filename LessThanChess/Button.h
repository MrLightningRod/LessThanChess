#pragma once
#include <SFML/Graphics.hpp>
#include "Constants.h"
#include <vector>

#define _BUTTON_OUTLINE_THICKNESS_ 2

const sf::Color _BUTTON_COLOR_(255, 255, 255, 255);
const sf::Color _BUTTON_NONACTIVE_COLOR_(150, 150, 150, 255);
const sf::Color _BUTTON_COLOR_ON_COVER_(120, 200, 225, 255);
const sf::Color _BUTTON_OUTLINE_COLOR_(0, 0, 0, 255);
const sf::Color _BUTTON_TEXT_COLOR_(0, 0, 0, 255);
const sf::Color _BUTTON_TRIGGERED_COLOR_(100, 250, 75, 255);


class Button
{
private:
	sf::RectangleShape buttonBody;
	sf::Text buttonText;
	sf::Font buttonFont;
	sf::FloatRect textRect;
	bool active;
	bool trigger;
	bool triggered;
public:
	Button();
	Button(sf::String text);
	void setPosition(sf::Vector2f position);
	sf::Vector2f getSize();
	void setSize(sf::Vector2f size);
	Button(sf::String text, sf::Vector2f position, sf::Vector2f size);
	~Button();
	void draw(sf::RenderWindow& window);
	void setActive(bool act);
	void setTrigger(bool trig);
	void setTriggered(bool trig);
	void setCover(bool cov);
	bool contains(sf::Vector2f pos);
	void setText(sf::String text);
};

class ButtonsManager
{
private:
	std::vector<Button*> buttonsList;
public:
	ButtonsManager();
	~ButtonsManager();
	void push(Button* but);
	void onCover(sf::Vector2f position);
	Button* onClick(sf::Vector2f position);
	void draw(sf::RenderWindow& window);
};