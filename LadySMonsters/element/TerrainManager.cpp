#include "TerrainManager.h"

TerrainManager::TerrainManager(Element* element, IsometricConvertion* isoConvert, Resource* resource)
{
	m_element = element;
	m_isoConvert = isoConvert;
	m_resource = resource;

	m_element->addTerrain(getTerrain("Fire", "Small Fire", 100, 100, 48, *m_resource->getTexture("terrainSmallFire").first, m_resource->getTexture("terrainSmallFire").second, sf::Vector2f(96 / 2, 56 / 2), *m_resource->getTexture("notAvailable").first, m_resource->getTexture("notAvailable").second, sf::Vector2f(32/2,32/2)));
	m_element->addTerrain(getTerrain("Earth", "Small Earth", 1000, 500, 64, *m_resource->getTexture("terrainSmallEarth").first, m_resource->getTexture("terrainSmallEarth").second, sf::Vector2f(128 / 2, 72 / 2), *m_resource->getTexture("notAvailable").first, m_resource->getTexture("notAvailable").second, sf::Vector2f(32 / 2, 32 / 2)));
}

Terrain* TerrainManager::getTerrain(std::string element, std::string name, int coinsMax, int price, int unit, sf::Texture& texture, sf::IntRect textureRect, sf::Vector2f spriteOrigin, sf::Texture& textureAvailability, sf::IntRect textureRectAvailability, sf::Vector2f spriteAvailabilityOrigin)
{
	Terrain* terrain = new Terrain(element, name, coinsMax, price);
	terrain->setShapePointCount(4);
	terrain->setShapePoints(m_isoConvert->orthoQuadToIso(unit));
	terrain->setShapeOrigin(sf::Vector2f(0, unit / 2));
	terrain->setTexture(texture, textureRect);
	terrain->setSpriteOrigin(spriteOrigin);
	terrain->setTextureAvailability(textureAvailability, textureRectAvailability);
	terrain->setSpriteAvailabilityOrigin(spriteAvailabilityOrigin);

	return terrain;
}
