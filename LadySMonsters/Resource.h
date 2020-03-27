#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include<utility>

class Resource
{
public:
	Resource();
	sf::Font* getFont(std::string name);
	std::pair<sf::Texture*, sf::IntRect> getTexture(std::string name);
	sf::RectangleShape* getImage(std::string name);
private:
	sf::Font m_eternityTime;

	sf::Texture m_uiSpritesheet;
	sf::Texture m_imageMenuBg;

	sf::Texture m_terrainsBuildingsSpritesheet;

	std::map<std::string, sf::RectangleShape> m_images;
};