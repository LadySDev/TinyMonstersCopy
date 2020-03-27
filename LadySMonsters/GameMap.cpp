#include "GameMap.h"

GameMap::GameMap(GameScene& gameScene)
{
	m_gameScene = &gameScene;
	m_window = m_gameScene->getRenderWindow();
	m_resource = m_gameScene->getResource();

	m_isoConvert = m_gameScene->getIsoConvert();

	m_element = m_gameScene->getElement();

	m_mouseClickCounter = 0;

	m_isSomethingCanMove = false;
	m_isSomethingFollowTheMouse = false;

	createMap();
}

void GameMap::processEvent(sf::Event event)
{
	sf::Vector2f mousePosition = sf::Vector2f(sf::Mouse::getPosition(*m_window));

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		bool isTerrainFounded = false;
		for (int i = 0; i < m_terrains.size(); i++)
		{
			if (m_terrains[i]->isMouseOn(mousePosition, m_isoConvert))
			{
				m_focusedTerrain = m_terrains[i];
				isTerrainFounded = true;
				break;
			}
		}

		if (isTerrainFounded == true)
		{
			if (m_isSomethingCanMove == true)
			{
				m_mouseClickCounter = m_mouseClickCounter + 1;
				if (m_mouseClickCounter == 1)
				{
					m_isSomethingFollowTheMouse = true;
				}
				else if (m_mouseClickCounter == 2)
				{
					m_isSomethingFollowTheMouse = false;
					m_mouseClickCounter = 0;
				}
			}
			else if (m_eggToPlace != NULL && m_focusedTerrain->checkTerrainsAvailability(*m_eggToPlace->getElements()))
			{
				m_focusedTerrain->addMonster(*m_element->getMonster(m_eggToPlace->getElements()->at(0), m_eggToPlace->getName()));
				m_gameScene->getGameUI()->showBarBottomDefault();
				hideAvailability();
				m_focusedTerrain = NULL;
				m_eggToPlace = NULL;
			}
			else if(m_eggToPlace == NULL)
			{
				m_gameScene->getGameUI()->showBarBottomTerrain(m_focusedTerrain);
			}
		}
		else if(m_isSomethingCanMove == false && m_eggToPlace == NULL)
		{
			m_focusedTerrain = NULL;

			if (m_nursery->isMouseOn(mousePosition, m_isoConvert))
			{
				m_gameScene->getGameUI()->showBarBottomNursery();
			}
			else
			{
				m_gameScene->getGameUI()->showBarBottomDefault();
			}
		}

		/*if (m_gameScene->getGameUI()->isBarBottomMoveCreated() == false && m_eggToPlace == NULL)
		{
			if (isTerrainFounded == true)
			{
				m_gameScene->getGameUI()->showBarBottomTerrain(m_focusedTerrain);
			}
			else if (isTerrainFounded == false)
			{
				m_focusedTerrain = NULL;

				if (m_nursery->isMouseOn(mousePosition, m_isoConvert))
				{
					m_gameScene->getGameUI()->showBarBottomNursery();
				}
				else
				{
					m_gameScene->getGameUI()->showBarBottomDefault();
				}
			}
		}
		else if(m_gameScene->getGameUI()->isBarBottomMoveCreated() == true)
		{
			m_mouseClickCounter = m_mouseClickCounter + 1;
			if (m_mouseClickCounter == 2)
			{
				m_focusedTerrain = NULL;
				m_isSomethingFollowTheMouse = false;
				m_mouseClickCounter = 0;
			}
		}
		else if (m_eggToPlace != NULL && m_focusedTerrain->checkTerrainsAvailability(*m_eggToPlace->getElements()))
		{
			m_focusedTerrain->addMonster(*m_element->getMonster(m_eggToPlace->getElements()->at(0), m_eggToPlace->getName()));
			m_gameScene->getGameUI()->showBarBottomDefault();
			hideAvailability();
			m_focusedTerrain = NULL;
			m_eggToPlace = NULL;
		}*/
	}
}

void GameMap::update(float deltaTime)
{
	for (int i = 0; i < m_terrains.size(); i++)
	{
		m_terrains[i]->update(deltaTime);
	}

	if (m_nursery != NULL)
	{
		m_nursery->update(deltaTime);
	}

	if (m_isSomethingCanMove == true && m_isSomethingFollowTheMouse == true)
	{
		sf::Vector2f mousePosition = sf::Vector2f(sf::Mouse::getPosition(*m_window));
		m_focusedTerrain->setPosition(mousePosition);
	}

	/*if (m_gameScene->getGameUI()->isBarBottomMoveCreated() == true)
	{
		sf::Vector2f mousePosition = sf::Vector2f(sf::Mouse::getPosition(*m_window));
		if (m_focusedTerrain != NULL)
		{
			if (m_isSomethingFollowTheMouse == false)
			{
				m_isSomethingFollowTheMouse = true;
			}

			m_focusedTerrain->setPosition(mousePosition);
		}

	}*/

	/*if (m_eggToPlace != NULL && m_gameScene->getGameUI()->isBarBottomNurseryCreated() == true)
	{
		m_gameScene->getGameUI()->hideBarBottomNursery();
	}*/
}

void GameMap::render()
{
	for (int i = 0; i < m_terrains.size(); i++)
	{
		m_window->draw(*m_terrains[i]);
	}
	if (m_nursery != NULL)
	{
		m_window->draw(*m_nursery);
	}
}

bool GameMap::isNurseryFull()
{
	return m_nursery->isFull();
}

void GameMap::addEgg(Egg* egg)
{
	m_nursery->addEgg(egg);
}

void GameMap::setIsSomethingCanMove(bool canIt)
{
	m_isSomethingCanMove = canIt;
}

bool GameMap::isSomethingFollowTheMouse()
{
	return m_isSomethingFollowTheMouse;
}

Nursery* GameMap::getNursery()
{
	return m_nursery;
}

bool GameMap::checkTerrainsAvailability(std::vector<std::string> elements)
{
	bool availability = false;
	for (int i = 0; i < m_terrains.size(); i++)
	{
		if (m_terrains.at(i)->checkTerrainsAvailability(elements) == true)
		{
			availability = true;
			break;
		}
	}
	return availability;
}

void GameMap::showAvailability(std::vector<std::string> elements)
{
	for (int i = 0; i < m_terrains.size(); i++)
	{
		m_terrains.at(i)->checkTerrainsAvailability(elements);
		m_terrains.at(i)->showAvailability(elements);
	}
}

void GameMap::hideAvailability()
{
	for (int i = 0; i < m_terrains.size(); i++)
	{
		m_terrains.at(i)->hideAvailability();
	}
}

void GameMap::setEggToPlace(Egg* egg)
{
	m_eggToPlace = egg;
}

void GameMap::createMap()
{
	sf::Vector2f center = sf::Vector2f(m_window->getSize().x / 2, m_window->getSize().y / 2);
	
	m_nursery = new Nursery(m_isoConvert);
	m_nursery->setPosition(center);

	Terrain* t1 = m_element->getTerrain("Fire");
	t1->setPosition(sf::Vector2f(center.x + m_nursery->getSize().x / 2 + t1->getSize().x / 2, center.y));

	m_terrains.push_back(t1);

	Terrain* t2 = m_element->getTerrain("Earth");
	t2->setPosition(sf::Vector2f(t1->getPosition().x + t1->getSize().x / 2 + t2->getSize().x / 2, center.y));

	m_terrains.push_back(t2);
}
