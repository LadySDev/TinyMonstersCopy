#pragma once

#include "GameScene.h"
#include "Resource.h"
#include <vector>
#include "IsometricConvertion.h"
#include "element/Element.h"
#include "element/Terrain.h"
#include "element/building/Nursery.h"

class GameScene;

class GameMap
{
public:
	GameMap(GameScene& gameScene);

	void processEvent(sf::Event event);
	void update(float deltaTime);
	void render();

	Nursery* getNursery();
	bool isNurseryFull();
	void addEgg(Egg* egg);

	void setIsSomethingCanMove(bool canIt);
	bool isSomethingFollowTheMouse();

	bool checkTerrainsAvailability(std::vector<std::string> elements);
	void showAvailability(std::vector<std::string> elements);
	void hideAvailability();

	void setEggToPlace(Egg* egg);
private:
	GameScene* m_gameScene;
	sf::RenderWindow* m_window;
	Resource* m_resource;

	IsometricConvertion* m_isoConvert;

	Element* m_element;

	std::vector<Terrain*> m_terrains;
	Terrain* m_focusedTerrain;

	Nursery* m_nursery;

	Egg* m_eggToPlace;

	int m_mouseClickCounter;

	bool m_isSomethingCanMove;
	bool m_isSomethingFollowTheMouse;

	void createMap();
};
