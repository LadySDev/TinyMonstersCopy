#include "PanelMarket.h"

PanelMarket::PanelMarket(GameUI* gameUI, sf::Vector2f position)
{
	m_gameUI = gameUI;
	m_window = m_gameUI->getRenderWindow();
	m_resource = m_gameUI->getResource();

	m_position = position;

	m_btnMonsters = NULL;
	m_btnTerrains = NULL;
	m_btnBuildings = NULL;
}

bool PanelMarket::processEvent(sf::Event event)
{
	bool eventFounded = false;

	sf::Vector2f mousePosition = sf::Vector2f(sf::Mouse::getPosition(*m_window));

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		if (m_btnMonsters->isMouseOn(mousePosition))
		{
			m_btnMonsters->onClick();
			eventFounded = true;
		}
		else if (m_btnTerrains->isMouseOn(mousePosition))
		{
			m_btnTerrains->onClick();
			eventFounded = true;
		}
		else if (m_btnBuildings->isMouseOn(mousePosition))
		{
			m_btnBuildings->onClick();
			eventFounded = true;
		}
	}

	return eventFounded;
}

void PanelMarket::update(float deltaTime)
{
}

void PanelMarket::render()
{
	m_window->draw(*m_btnMonsters);
	m_window->draw(*m_btnTerrains);
	m_window->draw(*m_btnBuildings);
}

void PanelMarket::create()
{
	//Button Monsters
	m_btnMonsters = new ButtonCardMarket(m_gameUI, "Monsters");
	m_btnMonsters->setPosition(sf::Vector2f(m_position.x, m_position.y));
	m_btnMonsters->setOrigin(sf::Vector2f(0, 0));
	m_btnMonsters->setTextPosition(sf::Vector2f(m_btnMonsters->getPosition().x + m_btnMonsters->getSize().x / 2, m_btnMonsters->getPosition().y + m_btnMonsters->getSize().y - 15));
	m_btnMonsters->setTextOrigin(sf::Vector2f(m_btnMonsters->getTextSize().x / 2, m_btnMonsters->getTextSize().y));
	
	m_btnMonsters->onClick = [this] {
		m_gameUI->showMarketMonster();
	};

	//Button Terrains
	m_btnTerrains = new ButtonCardMarket(m_gameUI, "Terrains");
	m_btnTerrains->setPosition(sf::Vector2f(m_position.x + 288, m_position.y));
	m_btnTerrains->setOrigin(sf::Vector2f(0, 0));
	m_btnTerrains->setTextPosition(sf::Vector2f(m_btnTerrains->getPosition().x + m_btnTerrains->getSize().x / 2, m_btnTerrains->getPosition().y + m_btnTerrains->getSize().y - 15));
	m_btnTerrains->setTextOrigin(sf::Vector2f(m_btnTerrains->getTextSize().x / 2, m_btnTerrains->getTextSize().y));
	
	m_btnTerrains->onClick = [this] {
		m_gameUI->showMarketTerrain();
	};

	//ButtonBuildings
	m_btnBuildings = new ButtonCardMarket(m_gameUI, "Buildings");
	m_btnBuildings->setPosition(sf::Vector2f(m_position.x + (288 * 2), m_position.y));
	m_btnBuildings->setOrigin(sf::Vector2f(0, 0));
	m_btnBuildings->setTextPosition(sf::Vector2f(m_btnBuildings->getPosition().x + m_btnBuildings->getSize().x / 2, m_btnBuildings->getPosition().y + m_btnBuildings->getSize().y - 15));
	m_btnBuildings->setTextOrigin(sf::Vector2f(m_btnBuildings->getTextSize().x / 2, m_btnBuildings->getTextSize().y));

	m_btnBuildings->onClick = [this] {
		m_gameUI->showMarketBuilding();
	};
}

void PanelMarket::destroy()
{
	m_btnMonsters = NULL;
	m_btnTerrains = NULL;
	m_btnBuildings = NULL;
}
