#pragma once

#include "../../GameUI.h"
#include <string>

class ButtonCardMarketMonster : public GuiButton
{
public:
	ButtonCardMarketMonster(GameUI* gameUI, std::string name, int price);

	virtual void setPosition(sf::Vector2f position);

	std::string getMonsterName();
	int getMonsterPrice();

private:
	sf::Text m_txtPrice;

	// Hérité via Drawable
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};