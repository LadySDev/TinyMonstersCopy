#pragma once

#include "ButtonCardMarketMonster.h"

class ButtonCardMarketMonster;

class PanelMarketMonster
{
public:
	PanelMarketMonster(GameUI* gameUI, sf::Vector2f position);

	bool processEvent(sf::Event event);
	void update(float deltaTime);
	void render();

	void create();
	void destroy();

private:
	GameUI* m_gameUI;
	sf::RenderWindow* m_window;
	Resource* m_resource;
	Element* m_element;

	sf::Vector2f m_position;
	sf::Vector2f m_origin;

	std::map<std::string, Monster*> m_monsters;
	std::vector<ButtonCardMarketMonster*>* m_btnCardMonsters;
};