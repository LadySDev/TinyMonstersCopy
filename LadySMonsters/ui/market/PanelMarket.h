#pragma once

#include "ButtonCardMarket.h"

class ButtonCardMarket;

class PanelMarket
{
public:
	PanelMarket(GameUI* gameUI, sf::Vector2f position);

	bool processEvent(sf::Event event);
	void update(float deltaTime);
	void render();

	void create();
	void destroy();

private:
	GameUI* m_gameUI;
	sf::RenderWindow* m_window;
	Resource* m_resource;

	sf::Vector2f m_position;
	sf::Vector2f m_origin;

	ButtonCardMarket* m_btnMonsters;
	ButtonCardMarket* m_btnTerrains;
	ButtonCardMarket* m_btnBuildings;
};