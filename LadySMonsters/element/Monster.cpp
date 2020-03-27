#include "Monster.h"

Monster::Monster(std::vector<std::string> elements, std::string name, int minuteGain, int price)
{
	m_elements = elements;
	m_name = name;
	m_minuteGain = minuteGain;
	m_price = price;

	m_shape.setSize(sf::Vector2f(16, 16));
	m_shape.setPosition(sf::Vector2f(0, 0));
	m_shape.setOrigin(sf::Vector2f(m_shape.getSize().x / 2, m_shape.getSize().y / 2));
}

std::vector<std::string>* Monster::getElements()
{
	return &m_elements;
}

std::string Monster::getName()
{
	return m_name;
}

int Monster::getMinuteGain()
{
	return m_minuteGain;
}

int Monster::getPrice()
{
	return m_price;
}

void Monster::setPosition(sf::Vector2f position)
{
	m_shape.setPosition(position);
}

void Monster::update(float deltaTime)
{
}

Monster* Monster::getClone()
{
	Monster* monster = new Monster(m_elements, m_name, m_minuteGain, m_price);

	return monster;
}

void Monster::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(m_shape);
}
