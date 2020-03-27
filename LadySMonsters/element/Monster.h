#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <string>
#include "Element.h"

class Monster : public sf::Drawable
{
public:
	Monster(std::vector<std::string> elements, std::string name, int minuteGain, int price);

	std::vector<std::string>* getElements();
	std::string getName();
	int getMinuteGain();
	int getPrice();

	void setPosition(sf::Vector2f position);

	void update(float deltaTime);

	Monster* getClone();
private:
	std::vector<std::string> m_elements;
	std::string m_name;
	int m_minuteGain;
	int m_price;

	sf::RectangleShape m_shape;

	// Hérité via Drawable
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};