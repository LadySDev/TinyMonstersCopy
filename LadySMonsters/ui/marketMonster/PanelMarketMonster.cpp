#include "PanelMarketMonster.h"

PanelMarketMonster::PanelMarketMonster(GameUI* gameUI, sf::Vector2f position)
{
	m_gameUI = gameUI;
	m_window = m_gameUI->getRenderWindow();
	m_resource = m_gameUI->getResource();
	m_element = m_gameUI->getElement();

	m_position = position;

	m_btnCardMonsters = NULL;
}

bool PanelMarketMonster::processEvent(sf::Event event)
{
	bool eventFounded = false;

	sf::Vector2f mousePosition = sf::Vector2f(sf::Mouse::getPosition(*m_window));

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		for (int i = 0; i < m_btnCardMonsters->size(); i++)
		{
			if (m_btnCardMonsters->at(i)->isMouseOn(mousePosition))
			{
				m_btnCardMonsters->at(i)->onClick();
				eventFounded = true;
				break;
			}
		}
	}

	return eventFounded;
}

void PanelMarketMonster::update(float deltaTime)
{
}

void PanelMarketMonster::render()
{
	for (int i =0;i<m_btnCardMonsters->size();i++)
	{
		m_window->draw(*m_btnCardMonsters->at(i));
	}
}

void PanelMarketMonster::create()
{
	m_btnCardMonsters = new std::vector<ButtonCardMarketMonster*>();

	sf::Vector2f startPosition = sf::Vector2f(m_position.x, m_position.y + 54);

	int counter = 0;
	std::vector<std::string>* elements = m_element->getElements();
	// for each element
	for (int i = 0; i < elements->size(); i++)
	{
		std::string element = elements->at(i);
		std::vector<Monster*>* monsters = m_element->getMonsters(element);
		// for each monster
		for (int j = 0; j < monsters->size(); j++)
		{
			Monster* monster = monsters->at(j);

			std::map<std::string, Monster*>::iterator it = m_monsters.find(monster->getName());

			if (it == m_monsters.end())
			{
				m_monsters[monster->getName()] = monster;

				ButtonCardMarketMonster* btnCard = new ButtonCardMarketMonster(m_gameUI, monster->getName(), monster->getPrice());
				btnCard->setPosition(sf::Vector2f(startPosition.x + (counter * btnCard->getSize().x), startPosition.y));

				btnCard->onClick = [this, element, monster] {
					if (m_gameUI->getGameScene()->getCoins() >= monster->getPrice() && !m_gameUI->getGameScene()->getGameMap()->isNurseryFull())
					{
						m_gameUI->getGameScene()->getGameMap()->addEgg(m_element->getEgg(element, monster->getName()));
						m_gameUI->getGameScene()->addCoins(-monster->getPrice());
						if (m_gameUI->isBarBottomNurseryCreated() == false)
						{
							m_gameUI->showBarBottomNursery();
						}
						m_gameUI->hideMarketMonster();
					}
				};

				m_btnCardMonsters->push_back(btnCard);

				counter = counter + 1;
			}
		}
	}
}

void PanelMarketMonster::destroy()
{
	m_monsters = std::map<std::string, Monster*>();
	m_btnCardMonsters = NULL;
}
