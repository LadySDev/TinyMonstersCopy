#pragma once

#include "../../GameUI.h"

class GameUI;

class GameUIBarBottomDefault
{
public:
	GameUIBarBottomDefault(GameUI* gameUI);

	bool processEvent(sf::Event event);
	void update(float deltaTime);
	void render();

	void create(std::string position);
	void destroy();

	bool getIsCreated();
	void setIsShowing(bool isShowing);
	bool getIsShowing();
	void setIsHiding(bool isHiding);
	bool getIsHiding();

private:
	GameUI* m_gameUI;
	sf::RenderWindow* m_window;
	Resource* m_resource;

	sf::Clock m_clock;
	float m_timer;
	float m_timerBarBottomDefault;

	sf::Vector2f m_btnMarketStart;
	sf::Vector2f m_btnMarketEnd;

	sf::Vector2f m_btnMoveStart;

	bool m_isCreated;
	bool m_isShowing;
	bool m_isHiding;

	GuiButton* m_btnMarket;

	GuiButton* m_btnMove;
};