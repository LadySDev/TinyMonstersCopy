#include "GameUI.h"

GameUI::GameUI(GameScene& gameScene)
{
	m_gameScene = &gameScene;
	m_window = m_gameScene->getRenderWindow();
	m_resource = m_gameScene->getResource();
	m_element = m_gameScene->getElement();

	m_timer = 0;
	
	createBarUp();

	m_barBottomDefault = new GameUIBarBottomDefault(this);
	m_barBottomDefault->create("start");

	m_barBottomMove = new BarBottomMove(this);
	m_isWaitingSomethingToMove = false;

	m_barBottomTerrain = new GameUIBarBottomTerrain(this);

	m_barBottomNursery = new BarBottomNursery(this, m_gameScene->getGameMap()->getNursery());

	m_timerProcessEventMenus = 0;
	m_isProcessEventMenusAllowed = false;

	m_market = new MenuMarket(this, "Market");
	m_isMarketCreated = false;

	m_marketMonster = new MenuMarketMonster(this, "Monsters");
	m_isMarketMonsterCreated = false;

	m_marketTerrain = new MenuMarketTerrain(this, "Terrains");
	m_isMarketTerrainCreated = false;

	m_marketBuilding = new MenuMarketBuilding(this, "Buildings");
	m_isMarketBuildingCreated = false;
}

bool GameUI::processEvent(sf::Event event)
{
	bool eventFounded = false;

	bool isAllNotShowingAndNotHiding =
		m_barBottomDefault->getIsShowing() == false && m_barBottomDefault->getIsHiding() == false
		&& m_barBottomTerrain->getIsShowing() == false && m_barBottomTerrain->getIsHiding() == false
		&& m_barBottomNursery->getIsShowing() == false && m_barBottomNursery->getIsHiding() == false
		&& m_barBottomMove->getIsShowing() == false && m_barBottomMove->getIsHiding() == false
		;

	if (m_isMarketCreated == true && m_isProcessEventMenusAllowed == true)
	{
		eventFounded = m_market->processEvent(event);
	}
	else if (m_isMarketMonsterCreated == true && m_isProcessEventMenusAllowed == true)
	{
		eventFounded = m_marketMonster->processEvent(event);
	}
	else if (m_isMarketTerrainCreated == true && m_isProcessEventMenusAllowed == true)
	{
		eventFounded = m_marketTerrain->processEvent(event);
	}
	else if (m_isMarketBuildingCreated == true && m_isProcessEventMenusAllowed == true)
	{
		eventFounded = m_marketBuilding->processEvent(event);
	}
	else if (m_barBottomDefault->getIsCreated() == true	&& isAllNotShowingAndNotHiding == true)
	{
		eventFounded = m_barBottomDefault->processEvent(event);
	}
	else if (m_barBottomTerrain->getIsCreated() == true && isAllNotShowingAndNotHiding == true)
	{
		eventFounded = m_barBottomTerrain->processEvent(event);
	}
	else if (m_barBottomNursery->getIsCreated() == true && isAllNotShowingAndNotHiding == true)
	{
		eventFounded = m_barBottomNursery->processEvent(event);
	}
	else if (m_barBottomMove->getIsCreated() == true && isAllNotShowingAndNotHiding == true)
	{
		eventFounded = m_barBottomMove->processEvent(event);
	}
	
	return eventFounded;
}

void GameUI::update(float deltaTime)
{
	m_timer = m_clock.restart().asSeconds();

	if (m_isMarketCreated == true)//TODO put in market class
	{
		if (m_isProcessEventMenusAllowed == false)
		{
			launchTimerProcessEventMenu();
		}
		
		m_market->update(deltaTime);
	}
	else if (m_isMarketMonsterCreated == true)//TODO put in marketMonster class
	{
		if (m_isProcessEventMenusAllowed == false)
		{
			launchTimerProcessEventMenu();
		}

		m_marketMonster->update(deltaTime);
	}
	else if (m_isMarketTerrainCreated == true)//TODO put in marketTerrain class
	{
		if (m_isProcessEventMenusAllowed == false)
		{
			launchTimerProcessEventMenu();
		}

		m_marketTerrain->update(deltaTime);
	}
	else if (m_isMarketBuildingCreated == true)//TODO put in marketBuilding class
	{
		if (m_isProcessEventMenusAllowed == false)
		{
			launchTimerProcessEventMenu();
		}

		m_marketBuilding->update(deltaTime);
	}
	else
	{
			m_barBottomDefault->update(deltaTime);
			m_barBottomTerrain->update(deltaTime);
			m_barBottomNursery->update(deltaTime);
			m_barBottomMove->update(deltaTime);
	}

	m_txtPlayerCoins.setString(std::to_string(m_gameScene->getCoins()));
	m_txtPlayerCoins.setOrigin(sf::Vector2f(m_txtPlayerCoins.getGlobalBounds().width, 0));
}

void GameUI::render()
{
	m_barBottomDefault->render();
	m_barBottomTerrain->render();
	m_barBottomNursery->render();
	m_barBottomMove->render();

	if (m_isMarketCreated == true)
	{
		m_market->render();//TODO put in market class
	}
	else if (m_isMarketMonsterCreated == true)
	{
		m_marketMonster->render();//TODO put in marketMonster class
	}
	else if (m_isMarketTerrainCreated == true)
	{
		m_marketTerrain->render();//TODO put in marketTerrain class
	}
	else if (m_isMarketBuildingCreated == true)
	{
		m_marketBuilding->render();//TODO put in marketBuilding class
	}

	m_window->draw(*m_imgBarUp);
	m_window->draw(*m_imgPlayerCoins);
	m_window->draw(m_txtPlayerCoins);
}

sf::RenderWindow* GameUI::getRenderWindow()
{
	return m_window;
}

Resource* GameUI::getResource()
{
	return m_resource;
}

GameScene* GameUI::getGameScene()
{
	return m_gameScene;
}

Element* GameUI::getElement()
{
	return m_element;
}

void GameUI::showBarBottomTerrain(Terrain* terrain)
{
	hideBarBottom();

	m_barBottomTerrain->setFocusedTerrain(terrain);

	if (m_barBottomTerrain->getIsHiding() == true)
	{
		m_barBottomTerrain->setIsHiding(false);
	}

	m_barBottomTerrain->setIsShowing(true);
}

void GameUI::hideBarBottomTerrain()
{
	if (m_barBottomTerrain->getIsShowing() == true)
	{
		m_barBottomTerrain->setIsShowing(false);
	}
	m_barBottomTerrain->setIsHiding(true);
}

void GameUI::showBarBottomDefault()
{
	hideBarBottom();

	if (m_barBottomDefault->getIsHiding() == true)
	{
		m_barBottomDefault->setIsHiding(false);
	}

	m_barBottomDefault->setIsShowing(true);
}

void GameUI::hideBarBottomDefault()
{
	if (m_barBottomDefault->getIsShowing() == true)
	{
		m_barBottomDefault->setIsShowing(false);
	}

	m_barBottomDefault->setIsHiding(true);
}

void GameUI::showBarBottomNursery()
{
	hideBarBottom();

	if (m_barBottomNursery->getIsHiding() == true)
	{
		m_barBottomNursery->setIsHiding(false);
	}

	m_barBottomNursery->setIsShowing(true);
}

void GameUI::hideBarBottomNursery()
{
	if (m_barBottomNursery->getIsShowing() == true)
	{
		m_barBottomNursery->setIsShowing(false);
	}

	m_barBottomNursery->setIsHiding(true);
}

bool GameUI::isBarBottomNurseryCreated()
{
	return m_barBottomNursery->getIsCreated();
}

void GameUI::showBarBottomMove()
{
	hideBarBottom();

	if(m_barBottomMove->getIsHiding() == true)
	{
		m_barBottomMove->setIsHiding(false);
	}

	m_barBottomMove->setIsShowing(true);

	m_isWaitingSomethingToMove = true;
}

void GameUI::hideBarBottomMove()
{
	if (m_barBottomMove->getIsShowing() == true)
	{
		m_barBottomMove->setIsShowing(false);
	}

	m_barBottomMove->setIsHiding(true);
}

bool GameUI::isBarBottomMoveCreated()
{
	return m_barBottomMove->getIsCreated();
}

void GameUI::hideBarBottom()
{
	if (m_barBottomDefault->getIsCreated() == true)
	{
		hideBarBottomDefault();
	}

	if (m_barBottomTerrain->getIsCreated() == true)
	{
		hideBarBottomTerrain();
	}

	if (m_barBottomNursery->getIsCreated() == true)
	{
		hideBarBottomNursery();
	}

	if (m_barBottomMove->getIsCreated() == true)
	{
		hideBarBottomMove();
	}
}

void GameUI::showMarket()
{
	if (m_barBottomDefault->getIsCreated() == false)
	{
		showBarBottomDefault();
	}
	
	m_market->create();
	m_isMarketCreated = true;
}

void GameUI::hideMarket()
{
	m_market->destroy();
	m_isMarketCreated = false;
	m_isProcessEventMenusAllowed = false;
}

void GameUI::showMarketMonster()
{
	if (m_isMarketCreated == true)
	{
		hideMarket();
	}

	m_marketMonster->create();
	m_isMarketMonsterCreated = true;
}

void GameUI::backFromMarketMonster()
{
	hideMarketMonster();

	showMarket();
}

void GameUI::hideMarketMonster()
{
	m_marketMonster->destroy();
	m_isMarketMonsterCreated = false;
	m_isProcessEventMenusAllowed = false;
}

void GameUI::showMarketTerrain()
{
	hideMarket();

	m_marketTerrain->create();
	m_isMarketTerrainCreated = true;
}

void GameUI::backFromMarketTerrain()
{
	hideMarketTerrain();
	showMarket();
}

void GameUI::hideMarketTerrain()
{
	m_marketTerrain->destroy();
	m_isMarketTerrainCreated = false;
	m_isProcessEventMenusAllowed = false;
}

void GameUI::showMarketBuilding()
{
	hideMarket();

	m_marketBuilding->create();
	m_isMarketBuildingCreated = true;
}

void GameUI::backFromMarketBuilding()
{
	hideMarketBuilding();
	showMarket();
}

void GameUI::hideMarketBuilding()
{
	m_marketBuilding->destroy();
	m_isMarketBuildingCreated = false;
	m_isProcessEventMenusAllowed = false;
}

void GameUI::launchTimerProcessEventMenu()
{
	m_timerProcessEventMenus = m_timerProcessEventMenus + m_timer;
	if (m_timerProcessEventMenus >= 0.75)
	{
		m_isProcessEventMenusAllowed = true;
		m_timerProcessEventMenus = 0;
	}
}

void GameUI::createBarUp()
{
	m_imgBarUp = m_resource->getImage("imgBarUp");
	m_imgBarUp->setPosition(sf::Vector2f(0, 0));

	m_imgPlayerCoins = m_resource->getImage("imgPlayerCoins");
	m_imgPlayerCoins->setPosition(sf::Vector2f(m_window->getSize().x, 0));
	m_imgPlayerCoins->setOrigin(sf::Vector2f(m_imgPlayerCoins->getGlobalBounds().width, 0));

	m_txtPlayerCoins.setFont(*m_resource->getFont("eternityTime"));
	m_txtPlayerCoins.setFillColor(sf::Color::Black);
	m_txtPlayerCoins.setCharacterSize(18);
	m_txtPlayerCoins.setString(std::to_string(m_gameScene->getCoins()));
	m_txtPlayerCoins.setPosition(sf::Vector2f(m_imgPlayerCoins ->getPosition().x - 20, m_imgPlayerCoins->getPosition().y + 7));
	m_txtPlayerCoins.setOrigin(sf::Vector2f(m_txtPlayerCoins.getGlobalBounds().width, 0));
}
