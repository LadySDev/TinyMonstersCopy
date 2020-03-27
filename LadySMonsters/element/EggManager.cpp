#include "EggManager.h"

EggManager::EggManager(Element* element, Resource* resource)
{
	m_element = element;
	m_resource = resource;

	float minute = 60;
	float hour = 60 * minute;

	m_element->addEgg(getEgg({ "Fire" }, "Fire", 5));
	m_element->addEgg(getEgg({ "Earth" }, "Earth", 12 * minute));
	m_element->addEgg(getEgg({ "Fire", "Earth" }, "Cinder", 13 * hour));
}

Egg* EggManager::getEgg(std::vector<std::string> elements, std::string name, float hatchingTime)
{
	return new Egg(elements, name, hatchingTime);
}
