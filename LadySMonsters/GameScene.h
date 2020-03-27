#pragma once

#include "Game.h"
#include "Resource.h"
#include "IsometricConvertion.h"
#include "element/Element.h"
#include "GameMap.h"
#include "GameUI.h"

class Game;
class GameMap;
class GameUI;

class GameScene
{
public:
	GameScene(Game& game);

	void processEvent(sf::Event event);
	void update(float deltaTime);
	void render();

	sf::RenderWindow* getRenderWindow();
	Resource* getResource();
	IsometricConvertion* getIsoConvert();
	Element* getElement();

	GameMap* getGameMap();
	GameUI* getGameUI();

	void addCoins(int number);
	int getCoins();

private:
	Game* m_game;
	sf::RenderWindow* m_window;
	Resource* m_resource;

	IsometricConvertion* m_isoConvert;

	Element* m_element;

	GameMap* m_gameMap;
	GameUI* m_gameUI;

	int m_coins;
};