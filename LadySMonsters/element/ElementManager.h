#pragma once

#include "Element.h"
#include "../IsometricConvertion.h"
#include "../Resource.h"
#include "TerrainManager.h"
#include "MonsterManager.h"
#include "EggManager.h"

class Element;
class TerrainManager;
class MonsterManager;
class EggManager;

class ElementManager
{
public:
	ElementManager(Element* element, IsometricConvertion* isoConvert, Resource* resource);
private:
	Element* m_element;
	IsometricConvertion* m_isoConvert;
	Resource* m_resource;
	TerrainManager* m_terrainManager;
	MonsterManager* m_monsterManager;
	EggManager* m_eggManager;
};