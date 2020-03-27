#include "Nursery.h"
#include <iostream>

Nursery::Nursery(IsometricConvertion* isoConvert)
{
	m_eggsMax = 1;
	
	m_isoConvert = isoConvert;

	m_unitX = 64;
	m_unitY = 48;

	std::vector<sf::Vector2f> rectangle = m_isoConvert->orthoRectToIso(m_unitX, m_unitY);
	m_shape.setPointCount(rectangle.size());

	for (int i = 0; i < rectangle.size(); i++)
	{
		m_shape.setPoint(i, rectangle.at(i));
	}

	m_shape.setOrigin(sf::Vector2f(0, m_unitX / 2));
	m_shape.setPosition(sf::Vector2f(0, 0));
	m_sprite.setPosition(sf::Vector2f(0, 0));

	m_eggsPositions.push_back(sf::Vector2f(m_shape.getPosition().x + 10, m_shape.getPosition().y - 10));

	m_shape.setFillColor(sf::Color::Green);
}

bool Nursery::isFull()
{
	return !(m_eggs.size() < m_eggsMax);
}

void Nursery::addEgg(Egg* egg)
{
	if (m_eggs.size() < m_eggsMax)
	{
		sf::Vector2f position = m_eggsPositions.at(m_eggs.size());
		egg->setPosition(position);
		egg->launchTimer();
		m_eggs.push_back(egg);
	}
}

int Nursery::getEggsCount()
{
	return m_eggs.size();
}

Egg* Nursery::getEggFirst()
{
	return m_eggs.at(0);
}

void Nursery::removeEgg(int index)
{
	m_eggs.erase(m_eggs.begin() + index);
}

void Nursery::setPosition(sf::Vector2f position)
{
	m_sprite.setPosition(position);
	m_shape.setPosition(position);

	m_eggsPositions[0] = sf::Vector2f(m_shape.getPosition().x + 10, m_shape.getPosition().y - 10);
}

sf::Vector2f Nursery::getSize()
{
	return sf::Vector2f(m_shape.getGlobalBounds().width, m_shape.getGlobalBounds().height);
}

void Nursery::setSpriteOrigin(sf::Vector2f origin)
{
	m_sprite.setOrigin(origin);
}

void Nursery::setTexture(sf::Texture& texture, sf::IntRect textureRect)
{
	m_sprite.setTexture(texture);
	m_sprite.setTextureRect(textureRect);
}

bool Nursery::isMouseOn(sf::Vector2f mousePosition, IsometricConvertion* util)
{
	sf::Vector2f point0 = sf::Vector2f(m_shape.getPosition().x, m_shape.getPosition().y - m_shape.getGlobalBounds().height / 2);
	sf::Vector2f point1 = sf::Vector2f(m_shape.getPosition().x + m_shape.getGlobalBounds().width / 2, m_shape.getPosition().y);
	sf::Vector2f point2 = sf::Vector2f(m_shape.getPosition().x, m_shape.getPosition().y + m_shape.getGlobalBounds().height / 2);
	sf::Vector2f point3 = sf::Vector2f(m_shape.getPosition().x - m_shape.getGlobalBounds().width / 2, m_shape.getPosition().y);

	bool isInsideTriangle1 = util->isInsideTriangle(point0, point1, point2, mousePosition);
	bool isInsideTriangle2 = util->isInsideTriangle(point2, point3, point0, mousePosition);

	return (isInsideTriangle1 || isInsideTriangle2);
}

void Nursery::update(float deltaTime)
{
	for (int i = 0; i < m_eggs.size(); i++)
	{
		m_eggs.at(i)->update(deltaTime);
	}
}

void Nursery::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(m_shape);
	target.draw(m_sprite);

	for (int i = 0; i < m_eggs.size(); i++)
	{
		target.draw(*m_eggs.at(i));
	}
}
