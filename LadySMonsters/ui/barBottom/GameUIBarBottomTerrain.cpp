#include "GameUIBarBottomTerrain.h"

GameUIBarBottomTerrain::GameUIBarBottomTerrain(GameUI* gameUI)
{
	m_gameUI = gameUI;
	m_window = m_gameUI->getRenderWindow();
	m_resource = m_gameUI->getResource();

	m_timer = 0;
	m_timerBarBottomTerrain = 0;

	m_focusedTerrain = NULL;

	m_btnCollectStart = sf::Vector2f(-109, m_window->getSize().y);
	m_btnCollectEnd = sf::Vector2f(0, m_window->getSize().y);

	m_isCreated = false;
	m_isShowing = false;
	m_isHiding = false;

	m_btnCollect = NULL;
	m_btnCollectCoins = NULL;
}

bool GameUIBarBottomTerrain::processEvent(sf::Event event)
{
	bool eventFounded = false;

	sf::Vector2f mousePosition = sf::Vector2f(sf::Mouse::getPosition(*m_window));

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		if (m_btnCollect->isMouseOn(mousePosition))
		{
			m_btnCollect->onClick();
			eventFounded = true;
		}
	}

	return eventFounded;
}

void GameUIBarBottomTerrain::update(float deltaTime)
{
	m_timer = m_clock.restart().asSeconds();

	if (m_isShowing == true && m_isHiding == false)
	{
		m_timerBarBottomTerrain = m_timerBarBottomTerrain + m_timer;

		if (m_isCreated == false)
		{
			create();
			m_isCreated = true;
		}

		if (m_btnCollect->getPosition() != m_btnCollectEnd && m_timerBarBottomTerrain >= 0.1)
		{
			m_btnCollect->setPosition(sf::Vector2f(m_btnCollect->getPosition().x + ((m_btnCollectEnd.x - m_btnCollectStart.x) / 8.f), m_btnCollect->getPosition().y));
			m_btnCollect->setTextPosition(sf::Vector2f(m_btnCollect->getPosition().x + m_btnCollect->getSize().x / 2, m_btnCollect->getPosition().y - 15));
			m_btnCollectCoins->setPosition(sf::Vector2f(m_btnCollect->getPosition().x + m_btnCollect->getSize().x - 19, m_btnCollect->getPosition().y - 118));

			m_timerBarBottomTerrain = 0;
		}
		else if (m_btnCollect->getPosition() == m_btnCollectEnd && m_timerBarBottomTerrain >= 0.1)
		{
			m_isShowing = false;
			m_timerBarBottomTerrain = 0;
		}
	}
	else if (m_isShowing == false && m_isHiding == true)
	{
		m_timerBarBottomTerrain = m_timerBarBottomTerrain + m_timer;

		if (m_btnCollect->getPosition() != m_btnCollectStart && m_timerBarBottomTerrain >= 0.1)
		{
			m_btnCollect->setPosition(sf::Vector2f(m_btnCollect->getPosition().x - ((m_btnCollectEnd.x - m_btnCollectStart.x) / 8.f), m_btnCollect->getPosition().y));
			m_btnCollect->setTextPosition(sf::Vector2f(m_btnCollect->getPosition().x + m_btnCollect->getSize().x / 2, m_btnCollect->getPosition().y - 15));
			m_btnCollectCoins->setPosition(sf::Vector2f(m_btnCollect->getPosition().x + m_btnCollect->getSize().x - 19, m_btnCollect->getPosition().y - 118));

			m_timerBarBottomTerrain = 0;
		}
		else if (m_btnCollect->getPosition() == m_btnCollectStart && m_timerBarBottomTerrain >= 0.1)
		{
			destroy();
			m_focusedTerrain = NULL;
			m_isCreated = false;

			m_isHiding = false;
			m_timerBarBottomTerrain = 0;
		}
	}

	if (m_isCreated == true)
	{
		m_btnCollectCoins->setString(std::to_string(m_focusedTerrain->getCoins()));
		m_btnCollectCoins->setOrigin(sf::Vector2f(m_btnCollectCoins->getGlobalBounds().width, m_btnCollectCoins->getGlobalBounds().height));
	}
}

void GameUIBarBottomTerrain::render()
{
	if (m_isCreated == true)
	{
		m_window->draw(*m_btnCollect);
		m_window->draw(*m_btnCollectCoins);
	}
}

void GameUIBarBottomTerrain::setFocusedTerrain(Terrain* terrain)
{
	m_focusedTerrain = terrain;
}

void GameUIBarBottomTerrain::create()
{
	sf::RectangleShape imgBtnCollect = *m_resource->getImage("imgBtnCollect");

	m_btnCollect = new GuiButton("btnCollect");
	m_btnCollect->setImage(imgBtnCollect);
	m_btnCollect->setPosition(m_btnCollectStart);
	m_btnCollect->setOrigin(sf::Vector2f(0, imgBtnCollect.getGlobalBounds().height));

	m_btnCollect->setFont(*m_resource->getFont("eternityTime"));
	m_btnCollect->setTextFillColor(sf::Color::Black);
	m_btnCollect->setTextString("Collecter");
	m_btnCollect->setTextCharacterSize(20);
	m_btnCollect->setTextPosition(sf::Vector2f(m_btnCollect->getPosition().x + m_btnCollect->getSize().x / 2, m_btnCollect->getPosition().y - 15));
	m_btnCollect->setTextOrigin(sf::Vector2f(m_btnCollect->getTextSize().x / 2, m_btnCollect->getTextSize().y));

	m_btnCollect->onClick = [this] {
		m_gameUI->getGameScene()->addCoins(m_focusedTerrain->getCoins());
		m_focusedTerrain->resetCoins();
	};

	m_btnCollectCoins = new sf::Text();
	m_btnCollectCoins->setFont(*m_resource->getFont("eternityTime"));
	m_btnCollectCoins->setFillColor(sf::Color::Black);
	m_btnCollectCoins->setString(std::to_string(m_focusedTerrain->getCoins()));
	m_btnCollectCoins->setCharacterSize(20);
	m_btnCollectCoins->setPosition(sf::Vector2f(m_btnCollect->getPosition().x + m_btnCollect->getSize().x - 19, m_btnCollect->getPosition().y - 118));
	m_btnCollectCoins->setOrigin(sf::Vector2f(m_btnCollectCoins->getGlobalBounds().width, m_btnCollectCoins->getGlobalBounds().height));
}

void GameUIBarBottomTerrain::destroy()
{
	m_btnCollect = NULL;
	m_btnCollectCoins = NULL;
}

bool GameUIBarBottomTerrain::getIsCreated()
{
	return m_isCreated;
}

void GameUIBarBottomTerrain::setIsShowing(bool isShowing)
{
	m_isShowing = isShowing;
}

bool GameUIBarBottomTerrain::getIsShowing()
{
	return m_isShowing;
}

void GameUIBarBottomTerrain::setIsHiding(bool isHiding)
{
	m_isHiding = isHiding;
}

bool GameUIBarBottomTerrain::getIsHiding()
{
	return m_isHiding;
}
