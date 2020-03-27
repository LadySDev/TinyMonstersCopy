#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <string>
#include "Element.h"

class Egg : public sf::Drawable
{
public:
	Egg(std::vector<std::string> elements, std::string name, float hatchingTime);

	std::vector<std::string>* getElements();
	std::string getName();
	float getHatchingTimer();

	void setPosition(sf::Vector2f position);
	void launchTimer();

	void update(float deltaTime);

	Egg* getClone();
private:
	std::vector<std::string> m_elements;
	std::string m_name;
	float m_hatchingTime;

	sf::Clock m_clock;
	float m_timer;

	bool m_isTimerLaunched;
	float m_timerEgg;

	sf::RectangleShape m_shape;

	// Hérité via Drawable
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};