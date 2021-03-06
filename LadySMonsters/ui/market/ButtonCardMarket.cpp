#include "ButtonCardMarket.h"

ButtonCardMarket::ButtonCardMarket(GameUI* gameUI, std::string name) : GuiButton(name)
{
	m_image = *gameUI->getResource()->getImage("imgMenuBtnSmallCard");

	m_text.setFont(*gameUI->getResource()->getFont("eternityTime"));
	m_text.setFillColor(sf::Color::Black);
	m_text.setString(m_name);
	m_text.setCharacterSize(20);
}
