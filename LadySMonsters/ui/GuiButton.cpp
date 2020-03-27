#include "GuiButton.h"
#include <iostream>

GuiButton::GuiButton(std::string name)
{
	m_name = name;
	m_image.setPosition(sf::Vector2f(0, 0));
	m_text.setPosition(sf::Vector2f(0, 0));
}

std::string GuiButton::getName()
{
	return m_name;
}

void GuiButton::setPosition(sf::Vector2f position)
{
	float x = m_image.getPosition().x - position.x;
	float y = m_image.getPosition().y - position.y;

	float distanceX = abs(x);
	float distanceY = abs(y);

	int orientationX;
	float textPosX;
	if (x == 0)
	{
		orientationX = 0;
		textPosX = m_text.getPosition().x;
	}
	else
	{
		orientationX = x > 0 ? -1 : 1;
		if (orientationX == -1)
		{
			textPosX = m_text.getPosition().x - distanceX;
		}
		else
		{
			textPosX = m_text.getPosition().x + distanceX;
		}
	}

	int orientationY;
	float textPosY;
	if (y == 0)
	{
		orientationY = 0;
		textPosY = m_text.getPosition().y;
	}
	else
	{
		orientationY = y > 0 ? -1 : 1;
		if (orientationX == -1)
		{
			textPosY = m_text.getPosition().y - distanceY;
		}
		else
		{
			textPosY = m_text.getPosition().y + distanceY;
		}
	}

	m_image.setPosition(position);
	m_text.setPosition(sf::Vector2f(textPosX, textPosY));
}

sf::Vector2f GuiButton::getPosition()
{
	return m_image.getPosition();
}

void GuiButton::setOrigin(sf::Vector2f origin)
{
	m_image.setOrigin(origin);
}

void GuiButton::setImage(sf::RectangleShape image)
{
	m_image = image;
}

void GuiButton::setColor(sf::Color color)
{
	m_image.setFillColor(color);
}

sf::Vector2f GuiButton::getSize()
{
	return sf::Vector2f(m_image.getGlobalBounds().width, m_image.getGlobalBounds().height);
}

void GuiButton::setFont(const sf::Font& font)
{
	m_text.setFont(font);
}

void GuiButton::setTextString(std::string text)
{
	m_text.setString(text);
}

void GuiButton::setTextPosition(sf::Vector2f position)
{
	m_text.setPosition(position);
}

sf::Vector2f GuiButton::getTextPosition()
{
	return m_text.getPosition();
}

void GuiButton::setTextOrigin(sf::Vector2f origin)
{
	m_text.setOrigin(origin);
}

void GuiButton::setTextFillColor(sf::Color color)
{
	m_text.setFillColor(color);
}

void GuiButton::setTextCharacterSize(int size)
{
	m_text.setCharacterSize(size);
}

sf::Vector2f GuiButton::getTextSize()
{
	return sf::Vector2f(m_text.getGlobalBounds().width, m_text.getGlobalBounds().height);
}

bool GuiButton::isMouseOn(sf::Vector2f mousePosition)
{
	return m_image.getGlobalBounds().contains(mousePosition);
}

void GuiButton::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(m_image);
	
	target.draw(m_text);
}
