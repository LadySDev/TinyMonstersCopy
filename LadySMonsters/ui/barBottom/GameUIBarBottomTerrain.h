#pragma once

#include "../../GameUI.h"

class GameUI;

class GameUIBarBottomTerrain
{
public:
	GameUIBarBottomTerrain(GameUI* gameUI);

	bool processEvent(sf::Event event);
	void update(float deltaTime);
	void render();

	void setFocusedTerrain(Terrain* terrain);

	void create();
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
	float m_timerBarBottomTerrain;

	Terrain* m_focusedTerrain;

	sf::Vector2f m_btnCollectStart;
	sf::Vector2f m_btnCollectEnd;

	bool m_isCreated;
	bool m_isShowing;
	bool m_isHiding;

	GuiButton* m_btnCollect;
	sf::Text* m_btnCollectCoins;
};