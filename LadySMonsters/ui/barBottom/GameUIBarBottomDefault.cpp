#include "GameUIBarBottomDefault.h"

GameUIBarBottomDefault::GameUIBarBottomDefault(GameUI* gameUI)
{
	m_gameUI = gameUI;
	m_window = m_gameUI->getRenderWindow();
	m_resource = m_gameUI->getResource();

	m_timer = 0;
	m_timerBarBottomDefault = 0;

	m_btnMarketStart = sf::Vector2f(0, m_window->getSize().y);
	m_btnMarketEnd = sf::Vector2f(0, m_window->getSize().y + 107);

	m_btnMoveStart = sf::Vector2f(m_window->getSize().x, m_window->getSize().y);

	m_isCreated = true;
	m_isShowing = false;
	m_isHiding = false;

	m_btnMarket = NULL;
	m_btnMove = NULL;
}

bool GameUIBarBottomDefault::processEvent(sf::Event event)
{
	bool eventFounded = false;

	sf::Vector2f mousePosition = sf::Vector2f(sf::Mouse::getPosition(*m_window));

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		if (m_btnMarket->isMouseOn(mousePosition))
		{
			m_btnMarket->onClick();
			eventFounded = true;
		}
		else if (m_btnMove->isMouseOn(mousePosition))
		{
			m_btnMove->onClick();
			eventFounded = true;
		}
	}

	return eventFounded;
}

void GameUIBarBottomDefault::update(float deltaTime)
{
	m_timer = m_clock.restart().asSeconds();

	if (m_isHiding == true && m_isShowing == false)
	{
		m_timerBarBottomDefault = m_timerBarBottomDefault + m_timer;

		if (m_btnMarket->getPosition() != m_btnMarketEnd && m_timerBarBottomDefault >= 0.1)
		{
			m_btnMarket->setPosition(sf::Vector2f(m_btnMarket->getPosition().x, m_btnMarket->getPosition().y + ((m_btnMarketEnd.y - m_btnMarketStart.y) / 8.f)));
			m_btnMarket->setTextPosition(sf::Vector2f(m_btnMarket->getPosition().x + m_btnMarket->getSize().x / 2, m_btnMarket->getPosition().y - 15));

			m_btnMove->setPosition(sf::Vector2f(m_btnMove->getPosition().x, m_btnMove->getPosition().y + ((m_btnMarketEnd.y - m_btnMoveStart.y) / 8.f)));
			m_btnMove->setTextPosition(sf::Vector2f(m_btnMove->getPosition().x - m_btnMove->getSize().x / 2, m_btnMove->getPosition().y - 15));

			m_timerBarBottomDefault = 0;
		}
		else if (m_btnMarket->getPosition() == m_btnMarketEnd && m_timerBarBottomDefault >= 0.1)
		{
			destroy();
			m_isCreated = false;
			m_isHiding = false;

			m_timerBarBottomDefault = 0;
		}
	}
	else if (m_isHiding == false && m_isShowing == true)
	{
		m_timerBarBottomDefault = m_timerBarBottomDefault + m_timer;

		if (m_isCreated == false)
		{
			create("end");
			m_isCreated = true;
		}

		if (m_btnMarket->getPosition() != m_btnMarketStart && m_timerBarBottomDefault >= 0.1)
		{
			m_btnMarket->setPosition(sf::Vector2f(m_btnMarket->getPosition().x, m_btnMarket->getPosition().y - ((m_btnMarketEnd.y - m_btnMarketStart.y) / 8.f)));
			m_btnMarket->setTextPosition(sf::Vector2f(m_btnMarket->getPosition().x + m_btnMarket->getSize().x / 2, m_btnMarket->getPosition().y - 15));

			m_btnMove->setPosition(sf::Vector2f(m_btnMove->getPosition().x, m_btnMove->getPosition().y - ((m_btnMarketEnd.y - m_btnMoveStart.y) / 8.f)));
			m_btnMove->setTextPosition(sf::Vector2f(m_btnMove->getPosition().x - m_btnMove->getSize().x / 2, m_btnMove->getPosition().y - 15));

			m_timerBarBottomDefault = 0;
		}
		else if (m_btnMarket->getPosition() == m_btnMarketStart && m_timerBarBottomDefault >= 0.1)
		{
			m_isShowing = false;
			m_timerBarBottomDefault = 0;
		}
	}
}

void GameUIBarBottomDefault::render()
{
	if (m_isCreated == true)
	{
		m_window->draw(*m_btnMarket);
		m_window->draw(*m_btnMove);
	}
}

void GameUIBarBottomDefault::create(std::string position)
{
	sf::RectangleShape imgBtnMarket = *m_resource->getImage("imgBtnMarket");

	m_btnMarket = new GuiButton("btnMarket");
	m_btnMarket->setImage(imgBtnMarket);

	if (position == "start")
	{
		m_btnMarket->setPosition(m_btnMarketStart);
	}
	else if (position == "end")
	{
		m_btnMarket->setPosition(m_btnMarketEnd);
	}

	m_btnMarket->setOrigin(sf::Vector2f(0, imgBtnMarket.getGlobalBounds().height));

	m_btnMarket->setFont(*m_resource->getFont("eternityTime"));
	m_btnMarket->setTextFillColor(sf::Color::Black);
	m_btnMarket->setTextString("Market");
	m_btnMarket->setTextCharacterSize(20);
	m_btnMarket->setTextPosition(sf::Vector2f(m_btnMarket->getPosition().x + m_btnMarket->getSize().x / 2, m_btnMarket->getPosition().y - 15));
	m_btnMarket->setTextOrigin(sf::Vector2f(m_btnMarket->getTextSize().x / 2, m_btnMarket->getTextSize().y));

	m_btnMarket->onClick = [this] {
		m_gameUI->showMarket();
	};

	//Button Move
	sf::RectangleShape imgBtnMove = *m_resource->getImage("imgBtnMarket"); // TODO

	m_btnMove = new GuiButton("btnMove");
	m_btnMove->setImage(imgBtnMove);

	if (position == "start")
	{
		m_btnMove->setPosition(m_btnMoveStart);
	}
	else if (position == "end")
	{
		m_btnMove->setPosition(sf::Vector2f(m_btnMoveStart.x, m_btnMarketEnd.y));
	}

	m_btnMove->setOrigin(sf::Vector2f(imgBtnMarket.getGlobalBounds().width, imgBtnMarket.getGlobalBounds().height));

	m_btnMove->setFont(*m_resource->getFont("eternityTime"));
	m_btnMove->setTextFillColor(sf::Color::Black);
	m_btnMove->setTextString("Move");
	m_btnMove->setTextCharacterSize(20);
	m_btnMove->setTextPosition(sf::Vector2f(m_btnMove->getPosition().x - m_btnMove->getSize().x / 2, m_btnMove->getPosition().y - 15));
	m_btnMove->setTextOrigin(sf::Vector2f(m_btnMove->getTextSize().x / 2, m_btnMove->getTextSize().y));

	m_btnMove->onClick = [this] {
		m_gameUI->getGameScene()->getGameMap()->setIsSomethingCanMove(true);
		m_gameUI->showBarBottomMove();
	};
}

void GameUIBarBottomDefault::destroy()
{
	m_btnMarket = NULL;
	m_btnMove = NULL;
}

bool GameUIBarBottomDefault::getIsCreated()
{
	return m_isCreated;
}

void GameUIBarBottomDefault::setIsShowing(bool isShowing)
{
	m_isShowing = isShowing;
}

bool GameUIBarBottomDefault::getIsShowing()
{
	return m_isShowing;
}

void GameUIBarBottomDefault::setIsHiding(bool isHiding)
{
	m_isHiding = isHiding;
}

bool GameUIBarBottomDefault::getIsHiding()
{
	return m_isHiding;
}
