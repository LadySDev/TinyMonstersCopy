#include "BarBottomMove.h"
#include <iostream>

BarBottomMove::BarBottomMove(GameUI* gameUI)
{
	m_gameUI = gameUI;
	m_window = m_gameUI->getRenderWindow();
	m_resource = m_gameUI->getResource();

	m_timer = 0;
	m_timerBarBottom = 0;

	m_isCreated = false;
	m_isShowing = false;
	m_isHiding = false;

	m_btnValid = NULL;
	m_btnCancel = NULL;
	m_btnSell = NULL;

	m_positionXStart = m_window->getSize().x + 109;
	m_positionXEnd = m_window->getSize().x;

	m_isSomethingSelected = false;
	m_selectedTerrain = NULL;
	m_selectedNursery = NULL;
}

bool BarBottomMove::processEvent(sf::Event event)
{
	bool eventFounded = false;

	sf::Vector2f mousePosition = sf::Vector2f(sf::Mouse::getPosition(*m_window));

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		if (m_btnValid->isMouseOn(mousePosition) && m_gameUI->getGameScene()->getGameMap()->isSomethingFollowTheMouse() == false)
		{
			m_btnValid->onClick();
			eventFounded = true;
		}
	}

	return eventFounded;
}

void BarBottomMove::update(float deltaTime)
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

		if (m_btnValid->getPosition().x != m_positionXEnd && m_timerBarBottom >= 0.1)
		{
			m_btnValid->setPosition(sf::Vector2f(m_btnValid->getPosition().x - ((m_positionXStart - m_positionXEnd) / 8.f), m_btnValid->getPosition().y));
			m_timerBarBottom = 0;
		}
		else if (m_btnValid->getPosition().x == m_positionXEnd && m_timerBarBottom >= 0.1)
		{
			m_isShowing = false;
			m_timerBarBottom = 0;
		}
	}
	else if (m_isShowing == false && m_isHiding == true)
	{
		m_timerBarBottom = m_timerBarBottom + m_timer;

		if (m_btnValid->getPosition().x != m_positionXStart && m_timerBarBottom >= 0.1)
		{
			m_btnValid->setPosition(sf::Vector2f(m_btnValid->getPosition().x + ((m_positionXStart - m_positionXEnd) / 8.f), m_btnValid->getPosition().y));
			m_timerBarBottom = 0;
		}
		else if (m_btnValid->getPosition().x == m_positionXStart && m_timerBarBottom >= 0.1)
		{
			destroy();
			m_isCreated = false;
			m_isHiding = false;
			m_timerBarBottom = 0;
		}
	}
}

void BarBottomMove::render()
{
	if (m_isCreated == true)
	{
		m_window->draw(*m_btnValid);
	}
}

void BarBottomMove::create()
{
	//Button Cancel
	sf::RectangleShape imgBtnCancel = *m_resource->getImage("imgBtnMarket"); // TODO

	m_btnValid = new GuiButton("btnAddEgg");
	m_btnValid->setImage(imgBtnCancel);
	m_btnValid->setPosition(sf::Vector2f(m_positionXStart, m_window->getSize().y - 108));
	m_btnValid->setOrigin(sf::Vector2f(imgBtnCancel.getGlobalBounds().width, imgBtnCancel.getGlobalBounds().height));

	m_btnValid->setFont(*m_resource->getFont("eternityTime"));
	m_btnValid->setTextFillColor(sf::Color::Black);
	m_btnValid->setTextString("Valid");
	m_btnValid->setTextCharacterSize(20);
	m_btnValid->setTextPosition(sf::Vector2f(m_btnValid->getPosition().x - m_btnValid->getSize().x / 2, m_btnValid->getPosition().y - 15));
	m_btnValid->setTextOrigin(sf::Vector2f(m_btnValid->getTextSize().x / 2, m_btnValid->getTextSize().y));

	m_btnValid->onClick = [this] {
		m_gameUI->getGameScene()->getGameMap()->setIsSomethingCanMove(false);
		m_gameUI->showBarBottomDefault();
	};
}

void BarBottomMove::destroy()
{
	m_btnValid = NULL;
}

bool BarBottomMove::getIsCreated()
{
	return m_isCreated;
}

void BarBottomMove::setIsShowing(bool isShowing)
{
	m_isShowing = isShowing;
}

bool BarBottomMove::getIsShowing()
{
	return m_isShowing;
}

void BarBottomMove::setIsHiding(bool isHiding)
{
	m_isHiding = isHiding;
}

bool BarBottomMove::getIsHiding()
{
	return m_isHiding;
}
