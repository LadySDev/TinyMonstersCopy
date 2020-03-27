#include "MenuMarketBuilding.h"

MenuMarketBuilding::MenuMarketBuilding(GameUI* gameUI, std::string name)
{
	m_gameUI = gameUI;
	m_window = m_gameUI->getRenderWindow();
	m_resource = m_gameUI->getResource();

	m_menu = new Menu(m_gameUI, name);

	m_btnBack = NULL;

	m_panel = new PanelMarketBuilding(m_gameUI, sf::Vector2f(144, 162));
}

bool MenuMarketBuilding::processEvent(sf::Event event)
{
	bool eventFounded = false;

	sf::Vector2f mousePosition = sf::Vector2f(sf::Mouse::getPosition(*m_window));

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		if (m_menu->getButtonClose()->isMouseOn(mousePosition))
		{
			m_menu->getButtonClose()->onClick();
			eventFounded = true;
		}
		else if (m_btnBack->isMouseOn(mousePosition))
		{
			m_btnBack->onClick();
			eventFounded = true;
		}

	}
	else
	{
		eventFounded = m_panel->processEvent(event);
	}

	return eventFounded;
}

void MenuMarketBuilding::update(float deltaTime)
{
	m_menu->update(deltaTime);

	m_panel->update(deltaTime);
}

void MenuMarketBuilding::render()
{
	m_menu->render();

	m_window->draw(*m_btnBack);

	m_panel->render();
}

void MenuMarketBuilding::create()
{
	m_menu->create();

	//Button Back
	m_btnBack = new GuiButton("btnBack");

	sf::RectangleShape* imgBtnBack = m_resource->getImage("imgMenuBtnBack");

	m_btnBack->setImage(*imgBtnBack);
	m_btnBack->setPosition(sf::Vector2f(0, 36));
	m_btnBack->setOrigin(sf::Vector2f(0, 0));

	m_btnBack->onClick = [this] {
		m_gameUI->backFromMarketBuilding();
	};

	m_menu->getButtonClose()->onClick = [this] {
		m_gameUI->hideMarketBuilding();
	};

	m_panel->create();
}

void MenuMarketBuilding::destroy()
{
	m_menu->destroy();

	m_btnBack = NULL;

	m_panel->destroy();
}
