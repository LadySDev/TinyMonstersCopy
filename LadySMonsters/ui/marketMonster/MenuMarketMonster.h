#pragma once

#include "../Menu.h"
#include "PanelMarketMonster.h"

class GameUI;
class Menu;
class PanelMarketMonster;

class MenuMarketMonster
{
public:
	MenuMarketMonster(GameUI* gameUI, std::string name);

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

	PanelMarketMonster* m_panel;
};