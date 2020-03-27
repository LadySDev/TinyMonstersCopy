#pragma once

#include "../../GameUI.h"
#include "../../element/building/Nursery.h"

class GameUI;
class Nursery;

class BarBottomNursery
{
public:
	BarBottomNursery(GameUI* gameUI, Nursery* nursery);

	bool processEvent(sf::Event event);
	void update(float deltaTime);
	void render();

	void create();
	void createButtonEggFirst(sf::Vector2f position);
	void destroy();
	void destroyButtonEggFirst();

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

	float m_timerBarBottom;
	int m_counterPosition;

	Nursery* m_nursery;

	sf::Vector2f m_btnAddEggStart;
	sf::Vector2f m_btnAddEggEnd;

	sf::Vector2f m_btnEggFirstEnd;

	bool m_isCreated;
	bool m_isShowing;
	bool m_isHiding;

	GuiButton* m_btnAddEgg;

	GuiButton* m_btnEggFirst;
	sf::Text* m_btnEggFirstTimer;
};