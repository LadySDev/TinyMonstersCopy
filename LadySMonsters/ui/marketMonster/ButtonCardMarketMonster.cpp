#include "ButtonCardMarketMonster.h"

ButtonCardMarketMonster::ButtonCardMarketMonster(GameUI* gameUI, std::string name, int price) : GuiButton(name)
{
	m_image = *gameUI->getResource()->getImage("imgMenuBtnLargeCard");
	
	m_text.setFont(*gameUI->getResource()->getFont("eternityTime"));
	m_text.setFillColor(sf::Color::Black);
	m_text.setString(m_name);
	m_text.setCharacterSize(20);
	m_text.setPosition(sf::Vector2f(m_image.getPosition().x + m_image.getGlobalBounds().width / 2, m_image.getPosition().y + m_image.getGlobalBounds().height - 11));
	m_text.setOrigin(sf::Vector2f(m_text.getGlobalBounds().width / 2, m_text.getGlobalBounds().height));

	m_txtPrice.setFont(*gameUI->getResource()->getFont("eternityTime"));
	m_txtPrice.setFillColor(sf::Color::Black);
	m_txtPrice.setString(std::to_string(price));
	m_txtPrice.setCharacterSize(20);
	m_txtPrice.setPosition(sf::Vector2f(m_image.getPosition().x + m_image.getGlobalBounds().width / 2, m_image.getPosition().y + m_image.getGlobalBounds().height - 51));
	m_txtPrice.setOrigin(sf::Vector2f(m_txtPrice.getGlobalBounds().width / 2, m_txtPrice.getGlobalBounds().height));
}

void ButtonCardMarketMonster::setPosition(sf::Vector2f position)
{
	float x = position.x - m_image.getPosition().x;
	float y = position.y - m_image.getPosition().y;

	m_image.setPosition(position);
	m_text.setPosition(sf::Vector2f(m_text.getPosition().x + x, m_text.getPosition().y + y));
	m_txtPrice.setPosition(sf::Vector2f(m_txtPrice.getPosition().x + x, m_txtPrice.getPosition().y + y));
}

std::string ButtonCardMarketMonster::getMonsterName()
{
	return m_text.getString();
}

int ButtonCardMarketMonster::getMonsterPrice()
{
	std::string str = m_txtPrice.getString();
	return std::stoi(str);
}

void ButtonCardMarketMonster::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(m_image);
	target.draw(m_text);

	target.draw(m_txtPrice);
}
