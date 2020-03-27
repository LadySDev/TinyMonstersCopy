#pragma once

#include "../../GameUI.h"
#include "../../element/building/Nursery.h"

class GameUI;
class Nursery;

class BarBottomMove
{
public:
	BarBottomMove(GameUI* gameUI);

	bool processEvent(sf::Event event);
	void update(float deltaTime);
	void render();

	void create();
	void createValid();
	void createSell();
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

	float m_timerBarBottom;

	bool m_isCreated;
	bool m_isShowing;
	bool m_isHiding;

	GuiButton* m_btnValid;
	GuiButton* m_btnCancel;
	GuiButton* m_btnSell;

	float m_positionXStart;
	float m_positionXEnd;

	bool m_isSomethingSelected;
	Terrain* m_selectedTerrain;
	Nursery* m_selectedNursery;

	void unselectAll();
	void selectTerrain(Terrain* terrain);
	void selectNursery(Nursery* nursery);
};