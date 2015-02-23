#include "stdafx.h"


Image_Manager::Image_Manager(void)
{
}


Image_Manager::~Image_Manager(void)
{
}

void Image_Manager::loadAssets()
{
	m_Title.loadFromFile("images/title_background.png");

	m_Image_Quit.loadFromFile("images/quit.png");
	m_Image_Quit.createMaskFromColor(sf::Color::White);
	m_Texture_Quit.loadFromImage(m_Image_Quit);

	m_Image_About.loadFromFile("images/About.png");
	m_Image_About.createMaskFromColor(sf::Color::White);
	m_Texture_About.loadFromImage(m_Image_About);

	m_Image_NewGame.loadFromFile("images/new_game.png");
	m_Image_NewGame.createMaskFromColor(sf::Color::White);
	m_Texture_NewGame.loadFromImage(m_Image_NewGame);

	m_GameLost.loadFromFile("images/game_over.png");
	m_GameWon.loadFromFile("images/you_win.png");
	m_PauseMenu.loadFromFile("images/pause_menu.png");

	m_Texture_Paddle.loadFromFile("images/paddle.png");

	m_Image_Ball.loadFromFile("images/ball.png");
	m_Image_Ball.createMaskFromColor(sf::Color::White);
	m_Texture_Ball.loadFromImage(m_Image_Ball);

	m_Texture_Blue.loadFromFile("images/blue.png");
	m_Texture_Red.loadFromFile("images/red.png");
}

sf::Texture& Image_Manager::getTitle()
{
	return m_Title;
}

sf::Texture& Image_Manager::getQuit()
{
	return m_Texture_Quit;
}

sf::Texture& Image_Manager::getAbout()
{
	return m_Texture_About;
}

sf::Texture& Image_Manager::getNewGame()
{
	return m_Texture_NewGame;
}

sf::Texture& Image_Manager::getLost()
{
	return m_GameLost;
}

sf::Texture& Image_Manager::getWon()
{
	return m_GameWon;
}

sf::Texture& Image_Manager::getPaused()
{
	return this->m_PauseMenu;
}

sf::Texture& Image_Manager::getPaddle()
{
	return m_Texture_Paddle;
}

sf::Texture& Image_Manager::getBall()
{
	return m_Texture_Ball;
}

sf::Texture& Image_Manager::getBlue()
{
	return m_Texture_Blue;
}

sf::Texture& Image_Manager::getRed()
{
	return m_Texture_Red;
}