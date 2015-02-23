#pragma once

class Paddle : public Game_Object
{
public:
	Paddle(void);
	~Paddle(void);

	void initialize();
	void update(float deltaTime);
	void resetLives();
	void loseLife();
	int livesLeft();

	float m_Speed;

private:
	int	m_Lives;
	
};