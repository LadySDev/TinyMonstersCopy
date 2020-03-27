#pragma once

#include "Element.h"
#include "ElementManager.h"
#include "../Resource.h"
#include "Egg.h"

class Element;
class ElementManager;
class Egg;

class EggManager
{
public:
	EggManager(Element* element, Resource* resource);

private:
	Element* m_element;
	Resource* m_resource;

	Egg* getEgg(std::vector<std::string> elements, std::string name, float hatchingTime);
};