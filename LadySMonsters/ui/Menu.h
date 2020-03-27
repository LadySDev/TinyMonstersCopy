#pragma once

#include "../GameUI.h"

class Menu
{
public:
	Menu(GameUI* gameUI, std::string name);

	void update(float deltaTime);
	void render();

	void create();
	void destroy();

	GuiButton* getButtonClose();

protected:
	GameUI* m_gameUI;
	sf::RenderWindow* m_window;
	Resource* m_resource;

	std::string m_name;

	sf::RectangleShape* m_imgMenuBg;
	sf::RectangleShape* m_imgMenuTitleBg;
	sf::Text* m_txtTitle;

	GuiButton* m_btnClose;
};