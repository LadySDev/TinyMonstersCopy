#include "Element.h"
#include <iostream>

Element::Element(IsometricConvertion* isoConvert, Resource* resource)
{
	m_elements = new std::vector<std::string>();

	m_isoConvert = isoConvert;
	m_resource = resource;
	m_elementManager = new ElementManager(this, m_isoConvert, m_resource);
}

void Element::addElement(std::string name)
{
	m_elements->push_back(name);
	m_terrains[name] = NULL;
	m_monsters[name] = new std::vector<Monster*>();
	m_eggs[name] = new std::map<std::string, Egg*>();
}

std::vector<std::string>* Element::getElements()
{
	return m_elements;
}

void Element::addTerrain(Terrain* terrain)
{
	m_terrains[terrain->getElement()] = terrain;
}

Terrain* Element::getTerrain(std::string element)
{
	return m_terrains[element]->getClone();
}

void Element::addMonster(Monster* monster)
{
	for (int i=0;i<monster->getElements()->size();i++)
	{
		std::string element = monster->getElements()->at(i);
		std::vector<Monster*>* monsters = m_monsters[element];
		monsters->push_back(monster);
	}
}

std::vector<Monster*>* Element::getMonsters(std::string element)
{
	return m_monsters[element];
}

Monster* Element::getMonster(std::string firstElement, std::string name)
{
	std::vector<Monster*>* monsters = getMonsters(firstElement);
	Monster* monster = NULL;
	for (int i = 0; i < monsters->size(); i++)
	{
		if (name == monsters->at(i)->getName())
		{
			monster = monsters->at(i)->getClone();
			break;
		}
	}

	return monster;
}

void Element::addEgg(Egg* egg)
{
	for (int i =0; i < egg->getElements()->size(); i++)
	{
		std::string element = egg->getElements()->at(i);
		std::map<std::string, Egg*>* eggs = m_eggs[element];
		m_eggs[element]->insert(std::pair<std::string, Egg*>(egg->getName(), egg));
	}
}

std::map<std::string, Egg*>* Element::getEggs(std::string element)
{
	return m_eggs.at(element);
}

Egg* Element::getEgg(std::string element, std::string name)
{
	std::map<std::string, Egg*>* mapEgg = m_eggs[element];
	Egg* egg = mapEgg->at(name);
	return egg->getClone();
}

