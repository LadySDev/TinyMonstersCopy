#include "PanelMarketTerrain.h"

PanelMarketTerrain::PanelMarketTerrain(GameUI* gameUI, sf::Vector2f position)
{
	m_gameUI = gameUI;
	m_window = m_gameUI->getRenderWindow();
	m_resource = m_gameUI->getResource();

	m_position = position;

	m_terrains = NULL;
}

bool PanelMarketTerrain::processEvent(sf::Event event)
{
	bool eventFounded = false;

	sf::Vector2f mousePosition = sf::Vector2f(sf::Mouse::getPosition(*m_window));

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		for (int i = 0; i < m_terrains->size(); i++)
		{
			if (m_terrains->at(i)->isMouseOn(mousePosition))
			{
				m_terrains->at(i)->onClick();
				eventFounded = true;
				break;
			}
		}
	}

	return eventFounded;
}

void PanelMarketTerrain::update(float deltaTime)
{
}

void PanelMarketTerrain::render()
{
	for (int i = 0; i < m_terrains->size(); i++)
	{
		m_window->draw(*m_terrains->at(i));
	}
}

void PanelMarketTerrain::create()
{
	m_terrains = new std::vector<ButtonCardMarketTerrain*>();

	sf::Vector2f startPosition = sf::Vector2f(m_position.x, m_position.y + 54);
	sf::Vector2f cardSize;

	//Fire
	ButtonCardMarketTerrain* m_fire = new ButtonCardMarketTerrain(m_gameUI, "Fire");
	m_fire->setPosition(sf::Vector2f(startPosition.x, startPosition.y));
	m_fire->setOrigin(sf::Vector2f(0, 0));
	m_fire->setTextPosition(sf::Vector2f(m_fire->getPosition().x + m_fire->getSize().x / 2, m_fire->getPosition().y + m_fire->getSize().y - 11));
	m_fire->setTextOrigin(sf::Vector2f(m_fire->getTextSize().x / 2, m_fire->getTextSize().y));

	m_fire->onClick = [this] {

	};

	m_terrains->push_back(m_fire);

	cardSize = m_fire->getSize();

	//Earth
	ButtonCardMarketTerrain* m_earth = new ButtonCardMarketTerrain(m_gameUI, "Earth");
	m_earth->setPosition(sf::Vector2f(startPosition.x + (cardSize.x * 1), startPosition.y));
	m_earth->setOrigin(sf::Vector2f(0, 0));
	m_earth->setTextPosition(sf::Vector2f(m_earth->getPosition().x + m_earth->getSize().x / 2, m_earth->getPosition().y + m_earth->getSize().y - 11));
	m_earth->setTextOrigin(sf::Vector2f(m_earth->getTextSize().x / 2, m_earth->getTextSize().y));

	m_earth->onClick = [this] {

	};

	m_terrains->push_back(m_earth);
}

void PanelMarketTerrain::destroy()
{
	m_terrains = NULL;
}
