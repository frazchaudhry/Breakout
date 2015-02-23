#include "StdAfx.h"
#include "Brick.h"


Brick::Brick(void) : alive(true), m_Type("")
{
}

Brick::Brick(sf::Texture& texture, std::string type)
{
	m_Sprite.setTexture(texture);
	m_Type = type;
	alive = true;
}


Brick::~Brick(void)
{
}

void Brick::initialize()
{
}

std::string Brick::getType()
{
	return m_Type;
}

void Brick::setPos(sf::Vector2f pos)
{
	m_Sprite.setPosition(pos);
}

bool Brick::isAlive()
{
	if (alive)
		return true;
	else
		return false;
}

void Brick::kill()
{
	alive = false;
}