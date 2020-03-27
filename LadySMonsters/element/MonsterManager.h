#pragma once

#include "Element.h"
#include "ElementManager.h"
#include "../Resource.h"
#include "Monster.h"

class Element;
class ElementManager;

class MonsterManager
{
public:
	MonsterManager(Element* element, Resource* resource);
private:
	Element* m_element;
	Resource* m_resource;

	Monster* getMonster(std::vector<std::string> elements, std::string name, int minuteGain, int price);
};