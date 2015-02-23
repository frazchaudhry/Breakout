#pragma once

#include "game_object.h"

class Brick : public Game_Object
{

public:
	Brick(void);
	Brick(sf::Texture& texture, std::string type);
	~Brick(void);

	void initialize();
	void setPos(sf::Vector2f pos);
	bool isAlive();
	void kill();
	std::string getType();
private:
	bool alive;
	std::string	m_Type;
};

