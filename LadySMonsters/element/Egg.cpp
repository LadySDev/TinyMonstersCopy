#include "Egg.h"

Egg::Egg(std::vector<std::string> elements, std::string name, float hatchingTime)
{
	m_elements = elements;
	m_name = name;
	m_hatchingTime = hatchingTime;

	m_shape.setSize(sf::Vector2f(16, 16));
	m_shape.setPosition(sf::Vector2f(0, 0));
	m_shape.setOrigin(sf::Vector2f(m_shape.getSize().x / 2, m_shape.getSize().y / 2));

	m_timer = 0;

	m_isTimerLaunched = false;
	m_timerEgg = 0;
}

std::vector<std::string>* Egg::getElements()
{
	return &m_elements;
}

std::string Egg::getName()
{
	return m_name;
}

float Egg::getHatchingTimer()
{
	return m_hatchingTime - m_timerEgg;
}

void Egg::setPosition(sf::Vector2f position)
{
	m_shape.setPosition(position);
}

void Egg::launchTimer()
{
	m_isTimerLaunched = true;
}

void Egg::update(float deltaTime)
{
	if (m_isTimerLaunched == true)
	{
		m_timer = m_clock.restart().asSeconds();

		m_timerEgg = m_timerEgg + m_timer;

		if (m_timerEgg >= m_hatchingTime)
		{
			m_isTimerLaunched = false;
		}
	}
}

Egg* Egg::getClone()
{
	Egg* egg = new Egg(m_elements, m_name, m_hatchingTime);

	return egg;
}

void Egg::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(m_shape);
}
