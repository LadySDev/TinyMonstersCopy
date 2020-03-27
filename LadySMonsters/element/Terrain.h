#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include "Element.h"
#include "../IsometricConvertion.h"
#include "Monster.h"

class Monster;

class Terrain : public sf::Drawable
{
public:
	Terrain(std::string element, std::string name, int coinsMax, int price);

	std::string getElement();

	int getCoins();
	void addCoins(float number);
	void resetCoins();

	void addMonster(Monster monster);

	void setShapePointCount(int number);
	void setShapePoints(std::vector<sf::Vector2f> points);
	void setShapePoint(int position, sf::Vector2f point);
	sf::Vector2f getSize();
	void setPosition(sf::Vector2f position);
	sf::Vector2f getPosition();
	void setShapeOrigin(sf::Vector2f origin);
	void setSpriteOrigin(sf::Vector2f origin);
	void setTexture(sf::Texture& texture, sf::IntRect textureRect);
	void setTextureAvailability(sf::Texture& texture, sf::IntRect textureRect);
	void setSpriteAvailabilityOrigin(sf::Vector2f origin);

	bool checkTerrainsAvailability(std::vector<std::string> elements);
	void showAvailability(std::vector<std::string> elements);
	void hideAvailability();

	bool isMouseOn(sf::Vector2f mousePosition, IsometricConvertion* util);

	void update(float deltaTime);

	Terrain* getClone();
private:
	std::string m_element;
	std::string m_name;
	float m_coinsMax;
	float m_coins;
	std::vector<Monster> m_monsters;
	int m_price;

	sf::ConvexShape m_shape;
	sf::Sprite m_sprite;
	sf::Texture* m_texture;

	sf::Clock m_clock;
	float m_timer;

	bool isAvailable;
	bool isAvailabilityShown;
	sf::Sprite m_spriteNotAvailable;
	sf::Texture* m_textureNotAvailable;

	// Hérité via Drawable
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};
