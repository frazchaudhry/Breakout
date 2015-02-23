#pragma once

class Ball : public Game_Object
{
public:
	Ball(void);
	~Ball(void);

	void update(float deltaTime, Paddle& paddle, std::vector<std::unique_ptr<Brick>>& bricks);
	void initialize();
	void normalizeDirectionVec();
	void updatePosition(float deltaTime);
	bool lineIntersects(sf::Vector2f p1, sf::Vector2f p2, sf::Vector2f p3, sf::Vector2f p4);
	void handleCollisions(Paddle& paddle, std::vector<std::unique_ptr<Brick>>& bricks);

	bool			isBallMoving;
	sf::Vector2f	m_Position;
	sf::Vector2f	m_Direction;
private:
	float			m_Speed;
	sf::Vector2f	m_LastPosition;
};

