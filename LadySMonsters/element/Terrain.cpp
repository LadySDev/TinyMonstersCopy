#include "Terrain.h"

Terrain::Terrain(std::string element, std::string name, int coinsMax, int price)
{
	m_element = element;
	m_name = name;
	m_coinsMax = coinsMax;
	m_coins = 0;
	m_price = price;

	m_shape.setPosition(sf::Vector2f(0, 0));
	m_sprite.setPosition(sf::Vector2f(0, 0));

	m_texture = NULL;

	m_timer = 0;

	isAvailable = false;
	isAvailabilityShown = false;
	m_spriteNotAvailable.setPosition(sf::Vector2f(0, 0));
}

std::string Terrain::getElement()
{
	return m_element;
}

void Terrain::update(float deltaTime)
{
	m_timer = m_timer + m_clock.restart().asSeconds();

	if (m_timer >= 1)
	{
		m_timer = 0;

		for (int i=0;i<m_monsters.size();i++)
		{
			addCoins((float)m_monsters[i].getMinuteGain() / 60.f);
		}

	}

	for (int i = 0; i < m_monsters.size(); i++)
	{
		m_monsters[i].update(deltaTime);
	}
}

Terrain* Terrain::getClone()
{
	Terrain* terrain = new Terrain(m_element, m_name, m_coinsMax, m_price);
	terrain->setShapePointCount(m_shape.getPointCount());

	for (int i=0;i<m_shape.getPointCount();i++)
	{
		terrain->setShapePoint(i, m_shape.getPoint(i));
	}

	terrain->setShapeOrigin(m_shape.getOrigin());
	terrain->setTexture(*m_texture, m_sprite.getTextureRect());
	terrain->setSpriteOrigin(m_sprite.getOrigin());
	terrain->setTextureAvailability(*m_textureNotAvailable, m_spriteNotAvailable.getTextureRect());
	terrain->setSpriteAvailabilityOrigin(m_spriteNotAvailable.getOrigin());

	return terrain;
}

int Terrain::getCoins()
{
	return int(m_coins);
}

void Terrain::addCoins(float number)
{
	if (m_coins + number <= m_coinsMax)
	{
		m_coins = m_coins + number;
	}
	else
	{
		m_coins = m_coinsMax;
	}
	
}

void Terrain::resetCoins()
{
	m_coins = 0;
}

void Terrain::setShapePointCount(int number)
{
	m_shape.setPointCount(number);
}

void Terrain::setShapePoints(std::vector<sf::Vector2f> points)
{
	for (int i=0;i<points.size();i++)
	{
		m_shape.setPoint(i, points.at(i));
	}
}

void Terrain::setShapePoint(int position, sf::Vector2f point)
{
	m_shape.setPoint(position, point);
}

sf::Vector2f Terrain::getSize()
{
	return sf::Vector2f(m_shape.getGlobalBounds().width, m_shape.getGlobalBounds().height);
}

void Terrain::setPosition(sf::Vector2f position)
{
	m_sprite.setPosition(position);
	m_shape.setPosition(position);
	m_spriteNotAvailable.setPosition(position);

	for (int i = 0; i < m_monsters.size(); i++)
	{
		m_monsters.at(i).setPosition(position);
	}
}

sf::Vector2f Terrain::getPosition()
{
	return m_shape.getPosition();;
}

void Terrain::setShapeOrigin(sf::Vector2f origin)
{
	m_shape.setOrigin(origin);
}

void Terrain::setSpriteOrigin(sf::Vector2f origin)
{
	m_sprite.setOrigin(origin);
}

void Terrain::setTexture(sf::Texture& texture, sf::IntRect textureRect)
{
	m_texture = &texture;

	m_sprite.setTexture(texture);
	m_sprite.setTextureRect(textureRect);
}

void Terrain::setTextureAvailability(sf::Texture& texture, sf::IntRect textureRect)
{
	m_textureNotAvailable = &texture;

	m_spriteNotAvailable.setTexture(texture);
	m_spriteNotAvailable.setTextureRect(textureRect);
}

void Terrain::setSpriteAvailabilityOrigin(sf::Vector2f origin)
{
	m_spriteNotAvailable.setOrigin(origin);
}

bool Terrain::checkTerrainsAvailability(std::vector<std::string> elements)
{
	bool availability = false;
	for (int i = 0; i < elements.size(); i++)
	{
		if (m_element == elements.at(i))
		{
			availability = true;
			break;
		}
	}
	return availability;
}

void Terrain::showAvailability(std::vector<std::string> elements)
{
	isAvailable = checkTerrainsAvailability(elements);
	isAvailabilityShown = true;
}

void Terrain::hideAvailability()
{
	isAvailabilityShown = false;
}

bool Terrain::isMouseOn(sf::Vector2f mousePosition, IsometricConvertion* util)
{
	sf::Vector2f point0 = sf::Vector2f(m_shape.getPosition().x, m_shape.getPosition().y - m_shape.getGlobalBounds().height / 2);
	sf::Vector2f point1 = sf::Vector2f(m_shape.getPosition().x + m_shape.getGlobalBounds().width / 2, m_shape.getPosition().y);
	sf::Vector2f point2 = sf::Vector2f(m_shape.getPosition().x, m_shape.getPosition().y + m_shape.getGlobalBounds().height / 2);
	sf::Vector2f point3 = sf::Vector2f(m_shape.getPosition().x - m_shape.getGlobalBounds().width / 2, m_shape.getPosition().y);

	bool isInsideTriangle1 = util->isInsideTriangle(point0, point1, point2, mousePosition);
	bool isInsideTriangle2 = util->isInsideTriangle(point2, point3, point0, mousePosition);

	return (isInsideTriangle1 || isInsideTriangle2);
}

void Terrain::addMonster(Monster monster)
{
	monster.setPosition(m_shape.getPosition());
	m_monsters.push_back(monster);
}

void Terrain::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(m_shape);
	target.draw(m_sprite);

	for (int i = 0; i < m_monsters.size(); i++)
	{
		target.draw(m_monsters[i]);
	}

	if (isAvailable == false && isAvailabilityShown == true)
	{
		target.draw(m_spriteNotAvailable);
	}
}
