#pragma once

#include "Element.h"
#include "ElementManager.h"
#include "../IsometricConvertion.h"
#include "../Resource.h"
#include "Terrain.h"

class Element;
class ElementManager;
class Terrain;

class TerrainManager
{
public:
	TerrainManager(Element* element, IsometricConvertion* isoConvert, Resource* resource);
private:
	Element* m_element;
	IsometricConvertion* m_isoConvert;
	Resource* m_resource;

	Terrain* getTerrain(std::string element, std::string name, int coinsMax, int price, int unit, sf::Texture& texture, sf::IntRect textureRect, sf::Vector2f spriteOrigin, sf::Texture& textureAvailability, sf::IntRect textureRectAvailability, sf::Vector2f spriteAvailabilityOrigin);
};