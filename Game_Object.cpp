#include "StdAfx.h"
#include "Game_Object.h"


Game_Object::Game_Object(void)
{
}


Game_Object::~Game_Object(void)
{
}

void Game_Object::setTexture(sf::Texture &texture)
{
	m_Sprite.setTexture(texture);
}

sf::Sprite& Game_Object::getSprite()
{
	return m_Sprite;
}

void Game_Object::initialize()
{
}

sf::Vector2f Game_Object::getCenter()
{
	return sf::Vector2f(m_Sprite.getGlobalBounds().left + m_Sprite.getGlobalBounds().width / 2, m_Sprite.getGlobalBounds().top + m_Sprite.getGlobalBounds().height / 2);
}