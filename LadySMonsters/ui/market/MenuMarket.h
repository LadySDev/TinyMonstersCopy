#pragma once

#include "../Menu.h"
#include "PanelMarket.h"

class GameUI;
class Menu;
class PanelMarket;

class MenuMarket
{
public:
	MenuMarket(GameUI* gameUI, std::string name);

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
	PanelMarket* m_panel;
};