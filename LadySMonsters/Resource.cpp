#include "Resource.h"

Resource::Resource()
{
	if (!m_eternityTime.loadFromFile("resource/Eternity Time.ttf"))
	{
		EXIT_FAILURE;
	}

	if (!m_uiSpritesheet.loadFromFile("resource/UI-spritesheet.png"))
	{
		EXIT_FAILURE;
	}

	sf::RectangleShape imgPlayerCoins;
	imgPlayerCoins.setSize(sf::Vector2f(144, 36));
	imgPlayerCoins.setTexture(&m_uiSpritesheet);
	imgPlayerCoins.setTextureRect(sf::IntRect(0, 0, 144, 36));
	m_images["imgPlayerCoins"] = imgPlayerCoins;

	sf::RectangleShape imgBtnCollect;
	imgBtnCollect.setSize(sf::Vector2f(108, 144));
	imgBtnCollect.setTexture(&m_uiSpritesheet);
	imgBtnCollect.setTextureRect(sf::IntRect(0, 36, 108, 144));
	m_images["imgBtnCollect"] = imgBtnCollect;

	sf::RectangleShape imgBtnMarket;
	imgBtnMarket.setSize(sf::Vector2f(108, 108));
	imgBtnMarket.setTexture(&m_uiSpritesheet);
	imgBtnMarket.setTextureRect(sf::IntRect(108, 72, 108, 108));
	m_images["imgBtnMarket"] = imgBtnMarket;

	sf::RectangleShape imgMenuTitleBg;
	imgMenuTitleBg.setSize(sf::Vector2f(216, 108));
	imgMenuTitleBg.setTexture(&m_uiSpritesheet);
	imgMenuTitleBg.setTextureRect(sf::IntRect(0, 180, 216, 108));
	m_images["imgMenuTitleBg"] = imgMenuTitleBg;

	sf::RectangleShape imgMenuBtnClose;
	imgMenuBtnClose.setSize(sf::Vector2f(36, 36));
	imgMenuBtnClose.setTexture(&m_uiSpritesheet);
	imgMenuBtnClose.setTextureRect(sf::IntRect(216, 216, 36, 36));
	m_images["imgMenuBtnClose"] = imgMenuBtnClose;

	sf::RectangleShape imgMenuBtnBack;
	imgMenuBtnBack.setSize(sf::Vector2f(36, 36));
	imgMenuBtnBack.setTexture(&m_uiSpritesheet);
	imgMenuBtnBack.setTextureRect(sf::IntRect(252, 216, 36, 36));
	m_images["imgMenuBtnBack"] = imgMenuBtnBack;

	sf::RectangleShape imgMenuBtnSmallCard;
	imgMenuBtnSmallCard.setSize(sf::Vector2f(288, 216));
	imgMenuBtnSmallCard.setTexture(&m_uiSpritesheet);
	imgMenuBtnSmallCard.setTextureRect(sf::IntRect(36, 288, 288, 216));
	m_images["imgMenuBtnSmallCard"] = imgMenuBtnSmallCard;

	sf::RectangleShape imgMenuBtnLargeCard;
	imgMenuBtnLargeCard.setSize(sf::Vector2f(288, 324));
	imgMenuBtnLargeCard.setTexture(&m_uiSpritesheet);
	imgMenuBtnLargeCard.setTextureRect(sf::IntRect(324, 180, 288, 324));
	m_images["imgMenuBtnLargeCard"] = imgMenuBtnLargeCard;

	if (!m_imageMenuBg.loadFromFile("resource/UI-menuBg.png"))
	{
		EXIT_FAILURE;
	}

	sf::RectangleShape imgBarUp;
	imgBarUp.setSize(sf::Vector2f(1152, 36));
	imgBarUp.setTexture(&m_imageMenuBg);
	imgBarUp.setTextureRect(sf::IntRect(0, 0, 1152, 36));
	m_images["imgBarUp"] = imgBarUp;

	sf::RectangleShape imgMenuBg;
	imgMenuBg.setSize(sf::Vector2f(1152, 648 - 36));
	imgMenuBg.setTexture(&m_imageMenuBg);
	imgMenuBg.setTextureRect(sf::IntRect(0, 36, 1152, 684 - 36));
	m_images["imgMenuBg"] = imgMenuBg;

	if (!m_terrainsBuildingsSpritesheet.loadFromFile("resource/terrains-buildings-spritesheet.png"))
	{
		EXIT_FAILURE;
	}
}

sf::Font* Resource::getFont(std::string name)
{
	if (name == "eternityTime")
	{
		return &m_eternityTime;
	}
	else
	{
		return nullptr;
	}
}

std::pair<sf::Texture*, sf::IntRect> Resource::getTexture(std::string name)
{
	std::pair<sf::Texture*, sf::IntRect> p;

	if (name == "terrainSmallFire")
	{
		p.first = &m_terrainsBuildingsSpritesheet;
		p.second = sf::IntRect(32, 0, 96, 56);
	}
	else if (name == "terrainSmallEarth")
	{
		p.first = &m_terrainsBuildingsSpritesheet;
		p.second = sf::IntRect(132, 0, 128, 72);
	}
	else if (name == "notAvailable")
	{
		p.first = &m_terrainsBuildingsSpritesheet;
		p.second = sf::IntRect(0, 0, 32, 32);
	}

	return p;
}

sf::RectangleShape* Resource::getImage(std::string name)
{
	return &m_images[name];
}
