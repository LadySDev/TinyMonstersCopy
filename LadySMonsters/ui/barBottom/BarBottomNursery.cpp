#include "BarBottomNursery.h"
#include <iostream>

BarBottomNursery::BarBottomNursery(GameUI* gameUI, Nursery* nursery)
{
	m_gameUI = gameUI;
	m_window = m_gameUI->getRenderWindow();
	m_resource = m_gameUI->getResource();

	m_timer = 0;
	m_timerBarBottom = 0;
	m_counterPosition = 0;

	m_nursery = nursery;

	m_btnAddEggStart = sf::Vector2f(-109, m_window->getSize().y);
	m_btnAddEggEnd = sf::Vector2f(0, m_window->getSize().y);

	m_btnEggFirstEnd = sf::Vector2f(108, m_window->getSize().y);

	m_isCreated = false;
	m_isShowing = false;
	m_isHiding = false;

	m_btnAddEgg = NULL;

	m_btnEggFirst = NULL;
	m_btnEggFirstTimer = NULL;
}

bool BarBottomNursery::processEvent(sf::Event event)
{
	bool eventFounded = false;

	sf::Vector2f mousePosition = sf::Vector2f(sf::Mouse::getPosition(*m_window));

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		if (m_btnAddEgg->isMouseOn(mousePosition)) 
		{
			m_btnAddEgg->onClick();
			eventFounded = true;
		}
		else if (m_btnEggFirst != NULL && m_btnEggFirst->isMouseOn(mousePosition))
		{
			m_btnEggFirst->onClick();
			eventFounded = true;
		}
	}

	return eventFounded;
}

void BarBottomNursery::update(float deltaTime)
{
	m_timer = m_clock.restart().asSeconds();

	if (m_isShowing == true && m_isHiding == false)
	{
		m_timerBarBottom = m_timerBarBottom + m_timer;

		if (m_isCreated == false)
		{
			create();
			m_isCreated = true;
		}

		if (m_btnAddEgg->getPosition() != m_btnAddEggEnd && m_timerBarBottom >= 0.1)
		{
			m_counterPosition = m_counterPosition + 1;

			m_btnAddEgg->setPosition(sf::Vector2f(m_btnAddEgg->getPosition().x + ((m_btnAddEggEnd.x - m_btnAddEggStart.x) / 8.f), m_btnAddEgg->getPosition().y));
		
			if (m_nursery->getEggsCount() == 1)
			{
				if (m_btnEggFirst == NULL)
				{
					createButtonEggFirst(sf::Vector2f(m_btnAddEggStart.x + (((m_btnEggFirstEnd.x - m_btnAddEggStart.x) / 8.f) * m_counterPosition), m_btnAddEggStart.y));
				}
				else
				{
					m_btnEggFirst->setPosition(sf::Vector2f(m_btnEggFirst->getPosition().x + ((m_btnEggFirstEnd.x - m_btnAddEggStart.x) / 8.f), m_btnEggFirst->getPosition().y));
					m_btnEggFirstTimer->setPosition(sf::Vector2f(m_btnEggFirst->getPosition().x + m_btnEggFirst->getSize().x / 2, m_btnEggFirst->getPosition().y - 85));
				}
			}

			m_timerBarBottom = 0;
		}
		else if (m_btnAddEgg->getPosition() == m_btnAddEggEnd && m_timerBarBottom >= 0.1)
		{
			m_counterPosition = 0;
			m_isShowing = false;
			m_timerBarBottom = 0;
		}
	}
	else if (m_isShowing == false && m_isHiding == true)
	{
		m_timerBarBottom = m_timerBarBottom + m_timer;

		if (m_btnAddEgg->getPosition() != m_btnAddEggStart && m_timerBarBottom >= 0.1)
		{
			m_counterPosition = m_counterPosition + 1;

			m_btnAddEgg->setPosition(sf::Vector2f(m_btnAddEgg->getPosition().x - ((m_btnAddEggEnd.x - m_btnAddEggStart.x) / 8.f), m_btnAddEgg->getPosition().y));

			if (m_nursery->getEggsCount() == 1)
			{
				if (m_btnEggFirst == NULL)
				{
					createButtonEggFirst(sf::Vector2f(m_btnEggFirstEnd.x + (((m_btnEggFirstEnd.x - m_btnAddEggStart.x) / 8.f) * m_counterPosition), m_btnEggFirstEnd.y));
				}
				else
				{
					m_btnEggFirst->setPosition(sf::Vector2f(m_btnEggFirst->getPosition().x - ((m_btnEggFirstEnd.x - m_btnAddEggStart.x) / 8.f), m_btnEggFirst->getPosition().y));
					m_btnEggFirstTimer->setPosition(sf::Vector2f(m_btnEggFirst->getPosition().x + m_btnEggFirst->getSize().x / 2, m_btnEggFirst->getPosition().y - 85));
				}
			}

			m_timerBarBottom = 0;
		}
		else if (m_btnAddEgg->getPosition() == m_btnAddEggStart && m_timerBarBottom >= 0.1)
		{
			m_counterPosition = 0;
			destroy();
			m_isCreated = false;
			m_isHiding = false;
			m_timerBarBottom = 0;
		}
	}

	if (m_isCreated == true)
	{
		if (m_nursery->getEggsCount() == 1 && m_btnEggFirstTimer == NULL)
		{
			createButtonEggFirst(m_btnEggFirstEnd);
		}

		if (m_btnEggFirstTimer != NULL)
		{
			float hatchingTimer = m_nursery->getEggFirst()->getHatchingTimer();
			int ht = hatchingTimer;

			if (hatchingTimer > 0)
			{
				m_btnEggFirstTimer->setString(std::to_string(ht) + "s");
			}
			else
			{
				m_btnEggFirstTimer->setString("");
			}

			m_btnEggFirstTimer->setOrigin(sf::Vector2f(m_btnEggFirstTimer->getGlobalBounds().width / 2, m_btnEggFirstTimer->getGlobalBounds().height));
		}
	}
}

void BarBottomNursery::render()
{
	if (m_isCreated == true)
	{
		if (m_btnAddEgg != NULL)
		{
			m_window->draw(*m_btnAddEgg);
		}
		
		if (m_btnEggFirst != NULL)
		{
			m_window->draw(*m_btnEggFirst);
			m_window->draw(*m_btnEggFirstTimer);
		}
	}
}

void BarBottomNursery::create()
{
	//Button Add Egg
	sf::RectangleShape imgBtnAddEgg = *m_resource->getImage("imgBtnMarket"); // TODO

	m_btnAddEgg = new GuiButton("btnAddEgg");
	m_btnAddEgg->setImage(imgBtnAddEgg);
	m_btnAddEgg->setPosition(m_btnAddEggStart);
	m_btnAddEgg->setOrigin(sf::Vector2f(0, imgBtnAddEgg.getGlobalBounds().height));

	m_btnAddEgg->setFont(*m_resource->getFont("eternityTime"));
	m_btnAddEgg->setTextFillColor(sf::Color::Black);
	m_btnAddEgg->setTextString("Add Egg");
	m_btnAddEgg->setTextCharacterSize(20);
	m_btnAddEgg->setTextPosition(sf::Vector2f(m_btnAddEgg->getPosition().x + m_btnAddEgg->getSize().x / 2, m_btnAddEgg->getPosition().y - 15));
	m_btnAddEgg->setTextOrigin(sf::Vector2f(m_btnAddEgg->getTextSize().x / 2, m_btnAddEgg->getTextSize().y));

	m_btnAddEgg->onClick = [this] {
		m_gameUI->showMarketMonster();
	};

	if (m_nursery->getEggsCount() == 1)
	{
		createButtonEggFirst(m_btnAddEggStart);
	}
}

void BarBottomNursery::createButtonEggFirst(sf::Vector2f position)
{
	sf::RectangleShape imgBtnEggFirst = *m_resource->getImage("imgBtnMarket"); // TODO

	m_btnEggFirst = new GuiButton("btnEggFirst");
	m_btnEggFirst->setImage(imgBtnEggFirst);
	m_btnEggFirst->setPosition(position);
	m_btnEggFirst->setOrigin(sf::Vector2f(0, imgBtnEggFirst.getGlobalBounds().height));

	m_btnEggFirst->setFont(*m_resource->getFont("eternityTime"));
	m_btnEggFirst->setTextFillColor(sf::Color::Black);
	m_btnEggFirst->setTextString("Hatch");
	m_btnEggFirst->setTextCharacterSize(20);
	m_btnEggFirst->setTextPosition(sf::Vector2f(m_btnEggFirst->getPosition().x + m_btnEggFirst->getSize().x / 2, m_btnEggFirst->getPosition().y - 15));
	m_btnEggFirst->setTextOrigin(sf::Vector2f(m_btnEggFirst->getTextSize().x / 2, m_btnEggFirst->getTextSize().y));

	m_btnEggFirst->onClick = [this] {
		if (m_nursery->getEggFirst()->getHatchingTimer() <= 0)
		{
			if (m_gameUI->getGameScene()->getGameMap()->checkTerrainsAvailability(*m_nursery->getEggFirst()->getElements()))
			{
				m_gameUI->getGameScene()->getGameMap()->setEggToPlace(m_nursery->getEggFirst());
				m_gameUI->getGameScene()->getGameMap()->showAvailability(*m_nursery->getEggFirst()->getElements());
				m_nursery->removeEgg(0);
				m_isHiding = true;
				destroyButtonEggFirst();
			}
		}
	};

	int ht = m_nursery->getEggFirst()->getHatchingTimer();

	m_btnEggFirstTimer = new sf::Text();
	m_btnEggFirstTimer->setFont(*m_resource->getFont("eternityTime"));
	m_btnEggFirstTimer->setFillColor(sf::Color::Black);
	m_btnEggFirstTimer->setString(std::to_string(ht) + "s");
	m_btnEggFirstTimer->setCharacterSize(20);
	m_btnEggFirstTimer->setPosition(sf::Vector2f(m_btnEggFirst->getPosition().x + m_btnEggFirst->getSize().x / 2, m_btnEggFirst->getPosition().y - 85));
	m_btnEggFirstTimer->setOrigin(sf::Vector2f(m_btnEggFirstTimer->getGlobalBounds().width / 2, m_btnEggFirstTimer->getGlobalBounds().height));
}

void BarBottomNursery::destroy()
{
	m_btnAddEgg = NULL;

	destroyButtonEggFirst();
}

void BarBottomNursery::destroyButtonEggFirst()
{
	m_btnEggFirst = NULL;
	m_btnEggFirstTimer = NULL;
}

bool BarBottomNursery::getIsCreated()
{
	return m_isCreated;
}

void BarBottomNursery::setIsShowing(bool isShowing)
{
	m_isShowing = isShowing;
}

bool BarBottomNursery::getIsShowing()
{
	return m_isShowing;
}

void BarBottomNursery::setIsHiding(bool isHiding)
{
	m_isHiding = isHiding;
}

bool BarBottomNursery::getIsHiding()
{
	return m_isHiding;
}
