#pragma once

#define _USE_MATH_DEFINES
#include <math.h>
#include <stdlib.h>
#include <SFML/Graphics.hpp>

class IsometricConvertion
{
public:
	std::vector<sf::Vector2f> orthoRectToIso(int unitX, int unitY);
	std::vector<sf::Vector2f> orthoQuadToIso(int unit);
	sf::Vector2f orthographicToIsometric(sf::Vector2f pivot, sf::Vector2f point, int angleDegree);
	bool isInsideTriangle(sf::Vector2f pointT0, sf::Vector2f pointT1, sf::Vector2f pointT2, sf::Vector2f point);
	/*bool onSegment(sf::Vector2f start, sf::Vector2f end, sf::Vector2f point);
	int orientation(sf::Vector2f start, sf::Vector2f end, sf::Vector2f point);
	bool doIntersect(sf::Vector2f start1, sf::Vector2f end1, sf::Vector2f start2, sf::Vector2f end2);
	bool isInside(std::vector<sf::Vector2f*> polygon, int n, sf::Vector2f point);*/
};
