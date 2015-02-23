#include "StdAfx.h"
#include "Paddle.h"


Paddle::Paddle(void) : m_Speed(0.0f)
{
	
}


Paddle::~Paddle(void)
{
}

void Paddle::initialize()
{
	m_Sprite.setPosition((SCREENWIDTH / 2) - (m_Sprite.getLocalBounds().width / 2), PADDLEYPOS);
	m_Speed = 0.0f;
}

void Paddle::resetLives()
{
	m_Lives = 5;
}

void Paddle::loseLife()
{
	m_Lives -= 1;
	/*if ( m_Lives < 0 )
		m_Lives = 0;*/
}

int Paddle::livesLeft()
{
	return m_Lives;
}

void Paddle::update(float deltaTime)
{
	m_Sprite.move(m_Speed * deltaTime, 0.0f);

	if (m_Sprite.getPosition().x < 0.0f)			// If the sprite goes past the bounds of the window
		m_Sprite.setPosition(sf::Vector2f(0.0f, PADDLEYPOS));	// the position is reset to keep it inside the window

	else if (m_Sprite.getPosition().x + m_Sprite.getLocalBounds().width > (float)SCREENWIDTH)
		m_Sprite.setPosition(sf::Vector2f((float)SCREENWIDTH - m_Sprite.getLocalBounds().width , PADDLEYPOS));
}