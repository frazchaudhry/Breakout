#pragma once

class Game
{
public:
	Game(void);
	~Game(void);

	void run();
	void setTextures();
	void update();
	void drawAll();
	bool isExiting();
	void loseLife();
	int  livesLeft();
	bool isLevelWon();

	enum GAMESTATE	 { uninitialized, title, about, running, paused, gamelost, gamewon, exiting };
	sf::RenderWindow m_Window;
	sf::Event		 m_Event;

	

private:
	sf::VideoMode							m_VMode;
	GAMESTATE								m_GameState;
	Image_Manager							m_imgMgr;
	Input_Manager							m_inpMgr;
	Level_Manager							m_lvlMgr;
	sf::Clock								m_Clock;
	float									m_deltaTime;
	Paddle									m_Paddle;
	Ball									m_Ball;
	sf::Sprite								m_Background;
	sf::Sprite								m_Quit;
	sf::Sprite								m_About;
	sf::Sprite								m_NewGame;
	sf::Sprite								m_GameOver;
	sf::Sprite								m_GameWon;
	sf::Sprite								m_Paused;
	sf::Text								m_AboutText;
	sf::Text								m_LivesText;
	sf::Font								m_Font;
	std::vector<std::unique_ptr<Brick>>		m_Bricks;
};