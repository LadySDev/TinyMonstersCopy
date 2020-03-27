#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <map>
#include <functional>

class GuiButton : public sf::Drawable
{
public:
	GuiButton(std::string name);

	std::string getName();

	virtual void setPosition(sf::Vector2f position);
	sf::Vector2f getPosition();
	void setOrigin(sf::Vector2f origin);
	void setImage(sf::RectangleShape image);
	void setColor(sf::Color color);
	sf::Vector2f getSize();

	void setFont(const sf::Font& font);
	void setTextString(std::string text);
	void setTextPosition(sf::Vector2f position);
	sf::Vector2f getTextPosition();
	void setTextOrigin(sf::Vector2f origin);
	void setTextFillColor(sf::Color color);
	void setTextCharacterSize(int size);
	sf::Vector2f getTextSize();

	bool isMouseOn(sf::Vector2f mousePosition);
	std::function<void()> onClick;

protected:
	std::string m_name;
	sf::RectangleShape m_image;
	sf::Text m_text;
	
	// Hérité via Drawable
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};