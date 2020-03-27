#include "MonsterManager.h"

MonsterManager::MonsterManager(Element* element, Resource* resource)
{
	m_element = element;
	m_resource = resource;

	m_element->addMonster(getMonster({ "Fire" }, "Fire", 11, 50));
	m_element->addMonster(getMonster({ "Earth" }, "Earth", 4, 100));
	m_element->addMonster(getMonster({ "Fire", "Earth" }, "Cinder", 13, 1300));
}

Monster* MonsterManager::getMonster(std::vector<std::string> elements, std::string name, int minuteGain, int price)
{
	return new Monster(elements, name, minuteGain, price);
}
