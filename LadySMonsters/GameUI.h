#pragma once

#include "GameScene.h"
#include "Resource.h"
#include "ui/GuiButton.h"
#include "element/Terrain.h"
#include "ui/barBottom/GameUIBarBottomDefault.h"
#include "ui/barBottom/BarBottomMove.h"
#include "ui/barBottom/GameUIBarBottomTerrain.h"
#include "ui/barBottom/BarBottomNursery.h"

#include "ui/market/MenuMarket.h"
#include "ui/marketMonster/MenuMarketMonster.h"
#include "ui/marketTerrain/MenuMarketTerrain.h"
#include "ui/marketBuilding/MenuMarketBuilding.h"

class GameScene;
class GameUIBarBottomDefault;
class BarBottomMove;
class GameUIBarBottomTerrain;
class BarBottomNursery;

class MenuMarket;
class MenuMarketMonster;
class MenuMarketTerrain;
class MenuMarketBuilding;

class GameUI
{
public:
	enum SelectedObjects {
		None, Terrains
	};

	GameUI(GameScene& gameScene);

	bool processEvent(sf::Event event);
	void update(float deltaTime);
	void render();

	sf::RenderWindow* getRenderWindow();
	Resource* getResource();
	GameScene* getGameScene();
	Element* getElement();

	void showBarBottomTerrain(Terrain* terrain);
	void hideBarBottomTerrain();
	void showBarBottomDefault();
	void hideBarBottomDefault();
	void showBarBottomNursery();
	void hideBarBottomNursery();
	bool isBarBottomNurseryCreated();

	void showBarBottomMove();
	void hideBarBottomMove();
	bool isBarBottomMoveCreated();

	void hideBarBottom();

	void showMarket();
	void hideMarket();

	void showMarketMonster();
	void backFromMarketMonster();
	void hideMarketMonster();

	void showMarketTerrain();
	void backFromMarketTerrain();
	void hideMarketTerrain();

	void showMarketBuilding();
	void backFromMarketBuilding();
	void hideMarketBuilding();

private:
	GameScene* m_gameScene;
	sf::RenderWindow* m_window;
	Resource* m_resource;
	Element* m_element;

	sf::Clock m_clock;
	float m_timer;

	sf::RectangleShape* m_imgBarUp;
	sf::RectangleShape* m_imgPlayerCoins;
	sf::Text m_txtPlayerCoins;

	GameUIBarBottomDefault* m_barBottomDefault;
	BarBottomMove* m_barBottomMove;
	bool m_isWaitingSomethingToMove;

	GameUIBarBottomTerrain* m_barBottomTerrain;
	BarBottomNursery* m_barBottomNursery;

	float m_timerProcessEventMenus;
	bool m_isProcessEventMenusAllowed;

	void launchTimerProcessEventMenu();

	bool m_isMarketCreated;
	MenuMarket* m_market;

	bool m_isMarketMonsterCreated;
	MenuMarketMonster* m_marketMonster;

	bool m_isMarketTerrainCreated;
	MenuMarketTerrain* m_marketTerrain;

	bool m_isMarketBuildingCreated;
	MenuMarketBuilding* m_marketBuilding;

	void createBarUp();
};