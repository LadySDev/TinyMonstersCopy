#pragma once

#include "../Menu.h"
#include "PanelMarketTerrain.h"

class GameUI;
class Menu;
class PanelMarketTerrain;

class MenuMarketTerrain
{
public:
	MenuMarketTerrain(GameUI* gameUI, std::string name);

	bool processEvent(sf::Event event);
	void update(float deltaTime);
	void render();

	void create();
	void destroy();

private:
	GameUI* m_gameUI;
	sf::RenderWindow* m_window;
	Resource* m_resource;

	Menu* m_menu;

	GuiButton* m_btnBack;

	PanelMarketTerrain* m_panel;
};