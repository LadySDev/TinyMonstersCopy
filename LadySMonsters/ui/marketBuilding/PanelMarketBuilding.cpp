#include "PanelMarketBuilding.h"

PanelMarketBuilding::PanelMarketBuilding(GameUI* gameUI, sf::Vector2f position)
{
	m_gameUI = gameUI;
	m_window = m_gameUI->getRenderWindow();
	m_resource = m_gameUI->getResource();

	m_position = position;

	m_buildings = NULL;
}

bool PanelMarketBuilding::processEvent(sf::Event event)
{
	bool eventFounded = false;

	sf::Vector2f mousePosition = sf::Vector2f(sf::Mouse::getPosition(*m_window));

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		for (int i=0;i<m_buildings->size();i++)
		{
			if (m_buildings->at(i)->isMouseOn(mousePosition))
			{
				m_buildings->at(i)->onClick();
				eventFounded = true;
				break;
			}
		}
	}

	return eventFounded;
}

void PanelMarketBuilding::update(float deltaTime)
{
}

void PanelMarketBuilding::render()
{
	for (int i = 0; i < m_buildings->size(); i++)
	{
		m_window->draw(*m_buildings->at(i));
	}
}

void PanelMarketBuilding::create()
{
	m_buildings = new std::vector<ButtonCardMarketBuilding*>();

	sf::Vector2f startPosition = sf::Vector2f(m_position.x, m_position.y + 54);
	sf::Vector2f cardSize;

	//Small Farm
	ButtonCardMarketBuilding* m_smallFarm = new ButtonCardMarketBuilding(m_gameUI, "Small Farm");
	m_smallFarm->setPosition(sf::Vector2f(startPosition.x, startPosition.y));
	m_smallFarm->setOrigin(sf::Vector2f(0, 0));
	m_smallFarm->setTextPosition(sf::Vector2f(m_smallFarm->getPosition().x + m_smallFarm->getSize().x / 2, m_smallFarm->getPosition().y + m_smallFarm->getSize().y - 11));
	m_smallFarm->setTextOrigin(sf::Vector2f(m_smallFarm->getTextSize().x / 2, m_smallFarm->getTextSize().y));

	m_smallFarm->onClick = [this] {

	};

	m_buildings->push_back(m_smallFarm);

	cardSize = m_smallFarm->getSize();
}

void PanelMarketBuilding::destroy()
{
	m_buildings = NULL;
}
