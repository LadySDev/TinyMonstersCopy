#pragma once

#include <SFML/Graphics.hpp>
#include "Resource.h"
#include "IsometricConvertion.h"
#include "element/Element.h"
#include "GameScene.h"

class GameScene;

class Game
{
public:
	Game(sf::RenderWindow& window);

	void processEvent(sf::Event event);
	void update(float deltaTime);
	void render();
	
	sf::RenderWindow* getRenderWindow();
	Resource* getResource();
	Element* getElement();
	IsometricConvertion* getIsoConvert();
private:
	sf::RenderWindow* m_window;
	Resource* m_resource;
	
	IsometricConvertion* m_isoConvert;

	Element* m_element;
	
	GameScene* m_gameScene;
};
