#include "Game.h"

Game::Game(sf::RenderWindow& window)
{
	m_window = &window;
	m_resource = new Resource();
	
	m_isoConvert = new IsometricConvertion();

	m_element = new Element(m_isoConvert, m_resource);

	m_gameScene = new GameScene(*this);
}

void Game::processEvent(sf::Event event)
{
	m_gameScene->processEvent(event);
}

void Game::update(float deltaTime)
{
	m_gameScene->update(deltaTime);
}

void Game::render()
{
	m_gameScene->render();
}

sf::RenderWindow* Game::getRenderWindow()
{
	return m_window;
}

Resource* Game::getResource()
{
	return m_resource;
}

Element* Game::getElement()
{
	return m_element;
}

IsometricConvertion* Game::getIsoConvert()
{
	return m_isoConvert;
}
