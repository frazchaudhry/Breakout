#pragma once



class Image_Manager
{
public:
	Image_Manager(void);
	~Image_Manager(void);

	void loadAssets();

	sf::Texture& getTitle();
	sf::Texture& getQuit();
	sf::Texture& getAbout();
	sf::Texture& getNewGame();
	sf::Texture& getPaddle();
	sf::Texture& getBall();
	sf::Texture& getBlue();
	sf::Texture& getRed();
	sf::Texture& getLost();
	sf::Texture& getWon();
	sf::Texture& getPaused();

private:
	sf::Texture		m_Title;
	sf::Image		m_Image_Quit;
	sf::Texture		m_Texture_Quit;
	sf::Image		m_Image_About;
	sf::Texture		m_Texture_About;
	sf::Image		m_Image_NewGame;
	sf::Texture		m_Texture_NewGame;
	sf::Texture		m_GameLost;
	sf::Texture		m_GameWon;
	sf::Texture		m_PauseMenu;
	sf::Texture		m_Texture_Paddle;
	sf::Image		m_Image_Ball;
	sf::Texture		m_Texture_Ball;
	sf::Texture		m_Texture_Blue;
	sf::Texture		m_Texture_Red;
};