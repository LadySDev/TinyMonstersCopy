#pragma once

#include "ButtonCardMarketTerrain.h"

class ButtonCardMarketTerrain;

class PanelMarketTerrain
{
public:
	PanelMarketTerrain(GameUI* gameUI, sf::Vector2f position);

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

	std::vector<ButtonCardMarketTerrain*>* m_terrains;
};