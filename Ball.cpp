#include "StdAfx.h"
#include "Ball.h"


Ball::Ball(void) : isBallMoving(false), m_Speed(MAXPADDLESPEED)
{
}


Ball::~Ball(void)
{
}

void Ball::initialize()
{
	if(isBallMoving)
		isBallMoving = false;

	m_Direction.x = 0.0f;
	m_Direction.y = 0.0f;

	int x = Random(-1, 1);		// Generates a random number between -1 and 1 so that the direction of the ball is randomly chosen
	m_Direction.x = static_cast<float>(x);	// between three possible directions.
	m_Direction.y = 1.0f;

	normalizeDirectionVec();

	m_Position.x = (SCREENWIDTH / 2) - (m_Sprite.getLocalBounds().width / 2);
	m_Position.y = PADDLEYPOS - 300.0f;
	m_Sprite.setPosition(m_Position);
}

void Ball::normalizeDirectionVec()
{
	float len = sqrtf(m_Direction.x * m_Direction.x + m_Direction.y * m_Direction.y); // Get the length of the vector

	m_Direction.x /= len;
	m_Direction.y /= len;
}

void Ball::update(float deltaTime, Paddle& paddle, std::vector<std::unique_ptr<Brick>>& bricks)
{
	if (isBallMoving)
	{
		updatePosition(deltaTime);

		if (m_Sprite.getPosition().x + m_Sprite.getLocalBounds().width > static_cast<float>(SCREENWIDTH))
		{
			m_Sprite.setPosition(static_cast<float>(SCREENWIDTH) - m_Sprite.getLocalBounds().width, m_Sprite.getPosition().y);
			m_Direction.x = m_Direction.x * (-1);
		}
		else if (m_Sprite.getPosition().x  < 0.0f)
		{
			m_Sprite.setPosition(0.0f , m_Sprite.getPosition().y);
			m_Direction.x = m_Direction.x * (-1);
		}
		else if (m_Sprite.getPosition().y < 0.0f)
		{
			m_Sprite.setPosition(m_Sprite.getPosition().x, 0.0f);
			m_Direction.y *= (-1);
		}
		else if (m_Sprite.getPosition().y + m_Sprite.getLocalBounds().height > static_cast<float>(SCREENHEIGHT))
		{
			initialize();
			paddle.initialize();
			paddle.loseLife();
		}
		else
			handleCollisions(paddle, bricks);
	}
}

void Ball::updatePosition(float deltaTime)
{
	m_Sprite.move(m_Direction.x * m_Speed * deltaTime, m_Direction.y * m_Speed * deltaTime);
}

bool Ball::lineIntersects(sf::Vector2f p1, sf::Vector2f p2, sf::Vector2f p3, sf::Vector2f p4)
{
	float ua = (p4.x - p3.x) * (p1.y - p3.y) - (p4.y - p3.y) * (p1.x - p3.x);
	float ub = (p2.x - p1.x) * (p1.y - p3.y) - (p2.y - p1.y) * (p1.x - p3.x);
	float de = (p4.y - p3.y) * (p2.x - p1.x) - (p4.x - p3.x) * (p2.y - p1.y);
	bool intersects = false;

	if (fabsf(de) >= 0.00001f)
	{
		ua /= de;
		ub /= de;

		if (ua >= 0.0f && ua <= 1.0f && ub >= 0.0f && ub <= 1.0f)
			intersects = true;
	}
	return intersects;
}

void Ball::handleCollisions(Paddle& paddle, std::vector<std::unique_ptr<Brick>>& bricks)
{
	if (m_Sprite.getGlobalBounds().top > static_cast<float>(SCREENHEIGHT) / 2.0f)	// Check the position of the ball and only check for collisions with the appropriate object
	{
		if (m_Direction.y > 0.0f && paddle.getSprite().getGlobalBounds().intersects(this->getSprite().getGlobalBounds()))
		{
			m_Direction.y *= (-1);
			m_Sprite.setPosition(m_Sprite.getPosition().x, paddle.getSprite().getGlobalBounds().top - m_Sprite.getLocalBounds().height);

			m_Direction.x = (getCenter().x - paddle.getCenter().x) / (paddle.getSprite().getGlobalBounds().width / 2); // Changes the direction
			// of the ball depending upon where the ball hits the paddle.

			normalizeDirectionVec();
		}
	}
	else
	{
		sf::Vector2f centerTop(this->getSprite().getGlobalBounds().width / 2.0f, 0.0f);
		sf::Vector2f centerLeft(0.0f, this->getSprite().getGlobalBounds().height / 2.0f);
		sf::Vector2f centerRight(this->getSprite().getGlobalBounds().width, this->getSprite().getGlobalBounds().height / 2.0f);
		sf::Vector2f centerBottom(this->getSprite().getGlobalBounds().width / 2.0f, this->getSprite().getGlobalBounds().height);
		sf::Vector2f newDirection(m_Direction.x, m_Direction.y);
		bool hit = false;
		bool hitRed = false;

		for (auto iter = bricks.begin(); iter != bricks.end(); ++iter)
		{
			if (!hit)
			{
			if ((*iter)->getSprite().getGlobalBounds().intersects(this->getSprite().getGlobalBounds()))
			{
				if ((*iter)->isAlive())
				{
					bool changed = false;
					sf::Vector2f topLeft((*iter)->getSprite().getGlobalBounds().left, (*iter)->getSprite().getGlobalBounds().top);
					sf::Vector2f topRight((*iter)->getSprite().getGlobalBounds().left + (*iter)->getSprite().getGlobalBounds().width, (*iter)->getSprite().getGlobalBounds().top);
					sf::Vector2f bottomLeft((*iter)->getSprite().getGlobalBounds().left, (*iter)->getSprite().getGlobalBounds().top + (*iter)->getSprite().getGlobalBounds().height);
					sf::Vector2f bottomRight((*iter)->getSprite().getGlobalBounds().left + (*iter)->getSprite().getGlobalBounds().width, (*iter)->getSprite().getGlobalBounds().top + (*iter)->getSprite().getGlobalBounds().height);

					if (m_Direction.x > 0.0f && lineIntersects(m_LastPosition + centerRight, this->getSprite().getPosition() + centerRight, topLeft, bottomLeft))
					{
						newDirection.x *= -1.0f;
						std::cout << "left" << std::endl;
						if ((*iter)->getType() == "blue")
						{
							(*iter)->kill();
							changed = true;
							hit = true;
							break;
						}
						else if ((*iter)->getType() == "red")
						{
							initialize();
							paddle.initialize();
							paddle.loseLife();
							hitRed = true;
							break;
						}
					}
					else if (m_Direction.x < 0.0f && lineIntersects(m_LastPosition + centerLeft, this->getSprite().getPosition() + centerLeft, topRight, bottomRight))
					{
						newDirection.x *= -1.0f;
						std::cout << "right" << std::endl;
						if ((*iter)->getType() == "blue")
						{
							(*iter)->kill();
							changed = true;
							hit = true;
							break;
						}
						else if ((*iter)->getType() == "red")
						{
							initialize();
							paddle.initialize();
							paddle.loseLife();
							hitRed = true;
							break;
						}
					}

					if (m_Direction.y > 0.0f && lineIntersects(m_LastPosition + centerBottom, this->getSprite().getPosition() + centerBottom, topLeft, topRight))
					{
						newDirection.y *= -1.0f;
						std::cout << "top" << std::endl;
						if ((*iter)->getType() == "blue")
						{
							(*iter)->kill();
							changed = true;
							hit = true;
							break;
						}
						else if ((*iter)->getType() == "red")
						{
							initialize();
							paddle.initialize();
							paddle.loseLife();
							hitRed = true;
							break;
						}
					}
					else if (m_Direction.y < 0.0f && lineIntersects(m_LastPosition + centerTop, this->getSprite().getPosition() + centerTop, bottomLeft, bottomRight))
					{
						newDirection.y *= -1.0f;
						std::cout << "bottom" << std::endl;
						if ((*iter)->getType() == "blue")
						{
							(*iter)->kill();
							changed = true;
							hit = true;
							break;
						}
						else if ((*iter)->getType() == "red")
						{
							initialize();
							paddle.initialize();
							paddle.loseLife();
							hitRed = true;
							break;
						}
					}

					// Hit a corner
					if (!changed)
					{
						if (m_Direction.x > 0.0f && m_Direction.y < 0.0f)
						{
							if (this->getSprite().getPosition().x < (*iter)->getSprite().getGlobalBounds().left + (*iter)->getSprite().getGlobalBounds().width / 2.0f && this->getSprite().getPosition().y > (*iter)->getSprite().getGlobalBounds().top + (*iter)->getSprite().getGlobalBounds().height / 2.0f)
							{
								newDirection.x *= -1.0f;
								newDirection.y *= -1.0f;
								if ((*iter)->getType() == "blue")
								{
									(*iter)->kill();
									changed = true;
									hit = true;
									break;
								}
								else if ((*iter)->getType() == "red")
								{
									initialize();
									paddle.initialize();
									paddle.loseLife();
									hitRed = true;
									break;
								}
								std::cout << "corner" << std::endl;
							}
							else if (this->getSprite().getPosition().x > (*iter)->getSprite().getGlobalBounds().left + (*iter)->getSprite().getGlobalBounds().width / 2.0f && this->getSprite().getPosition().y > (*iter)->getSprite().getGlobalBounds().top + (*iter)->getSprite().getGlobalBounds().height / 2.0f)
							{
								newDirection.y *= -1.0f;
								if ((*iter)->getType() == "blue")
								{
									(*iter)->kill();
									changed = true;
									hit = true;
									break;
								}
								else if ((*iter)->getType() == "red")
								{
									initialize();
									paddle.initialize();
									paddle.loseLife();
									hitRed = true;
									break;
								}
								std::cout << "corner" << std::endl;
							}
							else
							{
								newDirection.x *= -1.0f;
								if ((*iter)->getType() == "blue")
								{
									(*iter)->kill();
									changed = true;
									hit = true;
									break;
								}
								else if ((*iter)->getType() == "red")
								{
									initialize();
									paddle.initialize();
									paddle.loseLife();
									hitRed = true;
									break;
								}
								std::cout << "corner" << std::endl;
							}
						}
						else if (m_Direction.x < 0.0f && m_Direction.y < 0.0f)
						{
							if (this->getSprite().getPosition().x > (*iter)->getSprite().getGlobalBounds().left + (*iter)->getSprite().getGlobalBounds().width / 2.0f && this->getSprite().getPosition().y > (*iter)->getSprite().getGlobalBounds().top + (*iter)->getSprite().getGlobalBounds().height / 2.0f)
							{
								newDirection.x *= -1.0f;
								newDirection.y *= -1.0f;
								if ((*iter)->getType() == "blue")
								{
									(*iter)->kill();
									changed = true;
									hit = true;
									break;
								}
								else if ((*iter)->getType() == "red")
								{
									initialize();
									paddle.initialize();
									paddle.loseLife();
									hitRed = true;
									break;
								}
								std::cout << "corner" << std::endl;
							}
							else if (this->getSprite().getPosition().x < (*iter)->getSprite().getGlobalBounds().left + (*iter)->getSprite().getGlobalBounds().width / 2.0f && this->getSprite().getPosition().y > (*iter)->getSprite().getGlobalBounds().top + (*iter)->getSprite().getGlobalBounds().height / 2.0f)
							{
								newDirection.y *= -1.0f;
								if ((*iter)->getType() == "blue")
								{
									(*iter)->kill();
									changed = true;
									hit = true;
									break;
								}
								else if ((*iter)->getType() == "red")
								{
									initialize();
									paddle.initialize();
									paddle.loseLife();
									hitRed = true;
									break;
								}
								std::cout << "corner" << std::endl;
							}
							else
							{
								newDirection.x *= -1.0f;
								if ((*iter)->getType() == "blue")
								{
									(*iter)->kill();
									changed = true;
									hit = true;
									hitRed = true;
									break;
								}
								else if ((*iter)->getType() == "red")
								{
									initialize();
									paddle.initialize();
									paddle.loseLife();
									hitRed = true;
									break;
								}
								std::cout << "corner" << std::endl;
							}
						}
						else if (m_Direction.x > 0.0f && m_Direction.y > 0.0f)
						{
							if (this->getSprite().getPosition().x < (*iter)->getSprite().getGlobalBounds().left + (*iter)->getSprite().getGlobalBounds().width / 2.0f && this->getSprite().getPosition().y < (*iter)->getSprite().getGlobalBounds().top + (*iter)->getSprite().getGlobalBounds().height / 2.0f)
							{
								newDirection.x *= -1.0f;
								newDirection.y *= -1.0f;
								if ((*iter)->getType() == "blue")
								{
									(*iter)->kill();
									changed = true;
									hit = true;
									break;
								}
								else if ((*iter)->getType() == "red")
								{
									initialize();
									paddle.initialize();
									paddle.loseLife();
									hitRed = true;
									break;
								}
								std::cout << "corner" << std::endl;
							}
							else if (this->getSprite().getPosition().x > (*iter)->getSprite().getGlobalBounds().left + (*iter)->getSprite().getGlobalBounds().width / 2.0f && this->getSprite().getPosition().y < (*iter)->getSprite().getGlobalBounds().top + (*iter)->getSprite().getGlobalBounds().height / 2.0f)
							{
								newDirection.y *= -1.0f;
								if ((*iter)->getType() == "blue")
								{
									(*iter)->kill();
									changed = true;
									hit = true;
									break;
								}
								else if ((*iter)->getType() == "red")
								{
									initialize();
									paddle.initialize();
									paddle.loseLife();
									hitRed = true;
									break;
								}
								std::cout << "corner" << std::endl;
							}
							else
							{
								newDirection.x *= -1.0f;
								if ((*iter)->getType() == "blue")
								{
									(*iter)->kill();
									changed = true;
									hit = true;
									break;
								}
								else if ((*iter)->getType() == "red")
								{
									initialize();
									paddle.initialize();
									paddle.loseLife();
									hitRed = true;
									break;
								}
								std::cout << "corner" << std::endl;
							}
						}
						else
						{
							if (this->getSprite().getPosition().x > (*iter)->getSprite().getGlobalBounds().left + (*iter)->getSprite().getGlobalBounds().width / 2.0f && this->getSprite().getPosition().y < (*iter)->getSprite().getGlobalBounds().top + (*iter)->getSprite().getGlobalBounds().height / 2.0f)
							{
								newDirection.x *= -1.0f;
								newDirection.y *= -1.0f;
								if ((*iter)->getType() == "blue")
								{
									(*iter)->kill();
									changed = true;
									hit = true;
									break;
								}
								else if ((*iter)->getType() == "red")
								{
									initialize();
									paddle.initialize();
									paddle.loseLife();
									hitRed = true;
									break;
								}
								std::cout << "corner" << std::endl;
							}
							else if (this->getSprite().getPosition().x < (*iter)->getSprite().getGlobalBounds().left + (*iter)->getSprite().getGlobalBounds().width / 2.0f && this->getSprite().getPosition().y < (*iter)->getSprite().getGlobalBounds().top + (*iter)->getSprite().getGlobalBounds().height / 2.0f)
							{
								newDirection.y *= -1.0f;
								if ((*iter)->getType() == "blue")
								{
									(*iter)->kill();
									changed = true;
									hit = true;
									break;
								}
								else if ((*iter)->getType() == "red")
								{
									initialize();
									paddle.initialize();
									paddle.loseLife();
									hitRed = true;
									break;
								}
								std::cout << "corner" << std::endl;
							}
							else
							{
								newDirection.x *= -1.0f;
								if ((*iter)->getType() == "blue")
								{
									(*iter)->kill();
									changed = true;
									hit = true;
									break;
								}
								else if ((*iter)->getType() == "red")
								{
									initialize();
									paddle.initialize();
									paddle.loseLife();
									hitRed = true;
									break;
								}
								std::cout << "corner" << std::endl;
							}
						}
					}
				}
			}
			}
			
		}
		if(!hitRed)
			m_Direction = newDirection;
		m_LastPosition = this->getSprite().getPosition();
	}

}