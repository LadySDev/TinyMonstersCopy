#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include "../../IsometricConvertion.h"
#include "../Egg.h"

class Egg;

class Nursery : public sf::Drawable
{
public:
	Nursery(IsometricConvertion* isoConvert);

	bool isFull();
	void addEgg(Egg* egg);
	int getEggsCount();
	Egg* getEggFirst();
	void removeEgg(int index);

	void setPosition(sf::Vector2f position);
	sf::Vector2f getSize();
	void setSpriteOrigin(sf::Vector2f origin);
	void setTexture(sf::Texture& texture, sf::IntRect textureRect);

	bool isMouseOn(sf::Vector2f mousePosition, IsometricConvertion* util);

	void update(float deltaTime);

private:
	int m_eggsMax;
	std::vector<Egg*> m_eggs;
	std::vector<sf::Vector2f> m_eggsPositions;

	IsometricConvertion* m_isoConvert;

	int m_unitX;
	int m_unitY;
	sf::ConvexShape m_shape;
	sf::Sprite m_sprite;

	// Hérité via Drawable
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};