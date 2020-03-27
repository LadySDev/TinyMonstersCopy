#include "ElementManager.h"

ElementManager::ElementManager(Element* element, IsometricConvertion* isoConvert, Resource* resource)
{
	m_element = element;

	m_isoConvert = isoConvert;
	m_resource = resource;

	m_element->addElement("Fire");
	m_element->addElement("Earth");

	m_terrainManager = new TerrainManager(m_element, m_isoConvert, m_resource);
	m_monsterManager = new MonsterManager(m_element, m_resource);
	m_eggManager = new EggManager(m_element, m_resource);
}
