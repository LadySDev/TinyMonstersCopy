#include "GameScene.h"

GameScene::GameScene(Game& game)
{
	m_game = &game;
	m_window = m_game->getRenderWindow();
	m_resource = m_game->getResource();

	m_isoConvert = m_game->getIsoConvert();
	m_element = m_game->getElement();

	m_gameMap = new GameMap(*this);
	m_gameUI = new GameUI(*this);

	m_coins = 1500;
}

void GameScene::processEvent(sf::Event event)
{
	if (!m_gameUI->processEvent(event))
	{
		m_gameMap->processEvent(event);
	}
}

void GameScene::update(float deltaTime)
{
	m_gameMap->update(deltaTime);
	m_gameUI->update(deltaTime);
}

void GameScene::render()
{
	m_gameMap->render();
	m_gameUI->render();
}

sf::RenderWindow* GameScene::getRenderWindow()
{
	return m_window;
}

Resource* GameScene::getResource()
{
	return m_resource;
}

IsometricConvertion* GameScene::getIsoConvert()
{
	return m_isoConvert;
}

Element* GameScene::getElement()
{
	return m_element;
}

GameMap* GameScene::getGameMap()
{
	return m_gameMap;
}

GameUI* GameScene::getGameUI()
{
	return m_gameUI;
}

void GameScene::addCoins(int number)
{
	m_coins = m_coins + number;
}

int GameScene::getCoins()
{
	return m_coins;
}
