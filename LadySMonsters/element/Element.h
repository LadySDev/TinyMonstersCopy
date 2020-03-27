#pragma once

#include <string>
#include <map>
#include "Terrain.h"
#include "Monster.h"
#include "Egg.h"
#include "../IsometricConvertion.h"
#include "../Resource.h"
#include "ElementManager.h"

class ElementManager;
class Terrain;
class Egg;

class Element
{
public:
	Element(IsometricConvertion* isoConvert, Resource* resource);

	void addElement(std::string name);
	std::vector<std::string>* getElements();

	void addTerrain(Terrain* terrain);
	Terrain* getTerrain(std::string element);

	void addMonster(Monster* monster);
	std::vector<Monster*>* getMonsters(std::string element);
	Monster* getMonster(std::string firstElement, std::string name);

	void addEgg(Egg* egg);
	std::map<std::string, Egg*>* getEggs(std::string element);
	Egg* getEgg(std::string element, std::string name);
private:
	std::vector<std::string>* m_elements;
	std::map<std::string, Terrain*> m_terrains;
	std::map<std::string, std::vector<Monster*>*> m_monsters;
	std::map<std::string, std::map<std::string, Egg*>*> m_eggs;

	IsometricConvertion* m_isoConvert;
	Resource* m_resource;
	ElementManager* m_elementManager;
};
