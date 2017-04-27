#include "Button.h"
#include <iostream>

Button::~Button()
{

}

Button::Button()
{
	std::cout << "I'm here" << std::endl;
	active = true;
	trigger = false;
	triggered = false;
	buttonBody.setFillColor(_BUTTON_COLOR_);
	buttonBody.setSize(sf::Vector2f(200, 50));
	buttonBody.setPosition(sf::Vector2f(100, 100));
	buttonBody.setOutlineThickness(_BUTTON_OUTLINE_THICKNESS_);
	buttonBody.setOutlineColor(_BUTTON_OUTLINE_COLOR_);
	buttonFont.loadFromFile(_FONT_FILE_);
	buttonText.setFont(buttonFont);
	buttonText.setString("NONE");
	textRect = buttonText.getGlobalBounds();
	buttonText.setFillColor(_BUTTON_TEXT_COLOR_);
	buttonText.setPosition(buttonBody.getPosition() + buttonBody.getSize() / 2.f - sf::Vector2f(textRect.width / 2.f, textRect.height));
}

Button::Button(sf::String text)
{
	active = true;
	trigger = false;
	triggered = false;
	buttonBody.setFillColor(_BUTTON_COLOR_);
	buttonBody.setSize(sf::Vector2f(200, 50));
	buttonBody.setPosition(sf::Vector2f(100, 100));
	buttonBody.setOutlineThickness(_BUTTON_OUTLINE_THICKNESS_);
	buttonBody.setOutlineColor(_BUTTON_OUTLINE_COLOR_);
	buttonFont.loadFromFile(_FONT_FILE_);
	buttonText.setFont(buttonFont);
	buttonText.setString(text);
	textRect = buttonText.getGlobalBounds();
	buttonText.setFillColor(_BUTTON_TEXT_COLOR_);
	buttonText.setPosition(buttonBody.getPosition() + buttonBody.getSize() / 2.f - sf::Vector2f(textRect.width / 2.f, textRect.height));
}

void Button::setPosition(sf::Vector2f position)
{
	buttonText.setPosition(buttonText.getPosition() - buttonBody.getPosition() + position);
	buttonBody.setPosition(position);
}

sf::Vector2f Button::getSize()
{
	return buttonBody.getSize();
}

void Button::setSize(sf::Vector2f size)
{
	buttonText.setPosition(buttonText.getPosition() - buttonBody.getSize() / 2.f + size / 2.f);
	buttonBody.setSize(size);
}

Button::Button(sf::String text, sf::Vector2f position, sf::Vector2f size)
{
	active = true;
	trigger = false;
	triggered = false;
	buttonBody.setFillColor(_BUTTON_COLOR_);
	buttonBody.setSize(size);
	buttonBody.setPosition(position);
	buttonBody.setOutlineThickness(_BUTTON_OUTLINE_THICKNESS_);
	buttonBody.setOutlineColor(_BUTTON_OUTLINE_COLOR_);
	buttonFont.loadFromFile(_FONT_FILE_);
	buttonText.setFont(buttonFont);
	buttonText.setString(text);
	textRect = buttonText.getGlobalBounds();
	buttonText.setFillColor(_BUTTON_TEXT_COLOR_);
	buttonText.setPosition(buttonBody.getPosition() + buttonBody.getSize() / 2.f - sf::Vector2f(textRect.width / 2.f, textRect.height));
}

void Button::draw(sf::RenderWindow& window)
{
	window.draw(buttonBody);
	window.draw(buttonText);
}

void Button::setActive(bool act)
{
	active = act;
	trigger = trigger && act;
	if (active)
	{
		buttonBody.setFillColor(_BUTTON_COLOR_);
	}
	else
	{
		buttonBody.setFillColor(_BUTTON_NONACTIVE_COLOR_);
	}
}

void Button::setTrigger(bool trig)
{
	trigger = trig;
}

void Button::setTriggered(bool trig)
{
	if (!trigger)
		return;
	triggered = trig;
	if (trig)
	{
		buttonBody.setFillColor(_BUTTON_TRIGGERED_COLOR_);
	}
	else
	{
		buttonBody.setFillColor(_BUTTON_COLOR_);
	}
}

void Button::setCover(bool cov)
{
	if (!active)
		return;
	if (trigger && triggered)
		return;
	if (!cov)
	{
		buttonBody.setFillColor(_BUTTON_COLOR_);
	}
	else
	{
		buttonBody.setFillColor(_BUTTON_COLOR_ON_COVER_);
	}
}

bool Button::contains(sf::Vector2f pos)
{
	return (buttonBody.getGlobalBounds()).contains(pos);
}

ButtonsManager::ButtonsManager()
{
	buttonsList.clear();
}

ButtonsManager::~ButtonsManager()
{
	buttonsList.clear();
}

void ButtonsManager::push(Button* but)
{
	buttonsList.push_back(but);
}

void ButtonsManager::onCover(sf::Vector2f position)
{
	for (std::vector<Button*>::iterator it = buttonsList.begin(); it != buttonsList.end(); it++)
	{
		if ((*it)->contains(position))
		{
			(*it)->setCover(true);
		}
		else
		{
			(*it)->setCover(false);
		}
	}
}

Button* ButtonsManager::onClick(sf::Vector2f position)
{
	for (std::vector<Button*>::iterator it = buttonsList.begin(); it != buttonsList.end(); it++)
	{
		if ((*it)->contains(position))
		{
			return (*it);
		}
	}
	return NULL;
}

void ButtonsManager::draw(sf::RenderWindow& window)
{
	for (std::vector<Button*>::iterator it = buttonsList.begin(); it != buttonsList.end(); it++)
	{
		(*it)->draw(window);
	}
}

void Button::setText(sf::String text)
{
	buttonText.setString(text);
	textRect = buttonText.getGlobalBounds();
	buttonText.setPosition(buttonBody.getPosition() + buttonBody.getSize() / 2.f - sf::Vector2f(textRect.width / 2.f, textRect.height));
}