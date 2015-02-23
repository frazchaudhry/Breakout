#pragma once
class Game_Object
{
public:
	Game_Object(void);
	~Game_Object(void);

	virtual void initialize();
	void setTexture(sf::Texture &texture);
	sf::Sprite& getSprite();
	sf::Vector2f getCenter();

protected:
	sf::Sprite			m_Sprite;
};

