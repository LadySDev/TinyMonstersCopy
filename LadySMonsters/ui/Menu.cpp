#include "Menu.h"

Menu::Menu(GameUI* gameUI, std::string name)
{
	m_gameUI = gameUI;
	m_window = m_gameUI->getRenderWindow();
	m_resource = m_gameUI->getResource();

	m_name = name;

	m_imgMenuBg = NULL;
	m_imgMenuTitleBg = NULL;
	m_txtTitle = NULL;
	m_btnClose = NULL;
}

void Menu::update(float deltaTime)
{
}

void Menu::render()
{
	m_window->draw(*m_imgMenuBg);
	m_window->draw(*m_imgMenuTitleBg);
	m_window->draw(*m_txtTitle);
	m_window->draw(*m_btnClose);
}

void Menu::create()
{
	//Background
	m_imgMenuBg = m_resource->getImage("imgMenuBg");
	m_imgMenuBg->setPosition(sf::Vector2f(0, 36));

	//Title
	m_imgMenuTitleBg = m_resource->getImage("imgMenuTitleBg");
	m_imgMenuTitleBg->setPosition(sf::Vector2f(m_window->getSize().x / 2, 66));
	m_imgMenuTitleBg->setOrigin(sf::Vector2f(m_imgMenuTitleBg->getGlobalBounds().width / 2, 0));

	m_txtTitle = new sf::Text();
	m_txtTitle->setFont(*m_resource->getFont("eternityTime"));
	m_txtTitle->setFillColor(sf::Color::Black);
	m_txtTitle->setString(m_name);
	m_txtTitle->setCharacterSize(35);
	m_txtTitle->setPosition(sf::Vector2f(m_window->getSize().x / 2, m_imgMenuTitleBg->getPosition().y + 36));
	m_txtTitle->setOrigin(sf::Vector2f(m_txtTitle->getGlobalBounds().width / 2, 0));

	//Button Close
	m_btnClose = new GuiButton("btnClose");

	sf::RectangleShape* imgBtnClose = m_resource->getImage("imgMenuBtnClose");

	m_btnClose->setImage(*imgBtnClose);
	m_btnClose->setPosition(sf::Vector2f(m_window->getSize().x, 36));
	m_btnClose->setOrigin(sf::Vector2f(m_btnClose->getSize().x, 0));
}

void Menu::destroy()
{
	m_imgMenuBg = NULL;
	m_imgMenuTitleBg = NULL;
	m_txtTitle = NULL;
	m_btnClose = NULL;
}

GuiButton* Menu::getButtonClose()
{
	return m_btnClose;
}
