#include "MenuMarket.h"

MenuMarket::MenuMarket(GameUI* gameUI, std::string name)
{
	m_gameUI = gameUI;
	m_window = m_gameUI->getRenderWindow();
	m_resource = m_gameUI->getResource();

	m_menu = new Menu(m_gameUI, name);

	m_panel = new PanelMarket(m_gameUI, sf::Vector2f(144, 162));
}

bool MenuMarket::processEvent(sf::Event event)
{
	bool eventFounded = false;

	sf::Vector2f mousePosition = sf::Vector2f(sf::Mouse::getPosition(*m_window));

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && m_menu->getButtonClose()->isMouseOn(mousePosition))
	{
		m_menu->getButtonClose()->onClick();
		eventFounded = true;
	}
	else
	{
		eventFounded = m_panel->processEvent(event);
	}

	return eventFounded;
}

void MenuMarket::update(float deltaTime)
{
	m_menu->update(deltaTime);

	m_panel->update(deltaTime);
}

void MenuMarket::render()
{
	m_menu->render();

	m_panel->render();
}

void MenuMarket::create()
{
	m_menu->create();

	m_menu->getButtonClose()->onClick = [this] {
		m_gameUI->hideMarket();
	};

	m_panel->create();
}

void MenuMarket::destroy()
{
	m_menu->destroy();

	m_panel->destroy();
}
