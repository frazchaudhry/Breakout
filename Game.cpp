#include "stdafx.h"


Game::Game(void) : m_deltaTime(0.0f)
{
	// Initialize the game object.
	m_VMode.width		 = SCREENWIDTH;
	m_VMode.height		 = SCREENHEIGHT;
	m_VMode.bitsPerPixel = 32;

	m_Window.create(m_VMode, "Eent Tord (Breakout/Arkanoid clone)", sf::Style::Titlebar);	// Actually creates the window.
	m_GameState = uninitialized;
	m_Font.loadFromFile("C:/Windows/Fonts/arial.ttf");
	m_AboutText.setFont(m_Font);
	m_AboutText.setCharacterSize(16);
	m_LivesText.setFont(m_Font);
	m_LivesText.setCharacterSize(16);
	m_imgMgr.loadAssets();		// Loads all the image files into memory.
	m_Paddle.resetLives();
	
}

Game::~Game(void)
{
}

void Game::setTextures()
{
	static GAMESTATE background = uninitialized;
	switch (m_GameState)
	{
	case title:
		if (background != title)
		{
			m_Background.setTexture(m_imgMgr.getTitle());
			m_Quit.setTexture(m_imgMgr.getQuit());
			m_About.setTexture(m_imgMgr.getAbout());
			m_NewGame.setTexture(m_imgMgr.getNewGame());
			m_GameOver.setTexture(m_imgMgr.getLost());
			m_GameWon.setTexture(m_imgMgr.getWon());
			m_Paused.setTexture(m_imgMgr.getPaused());
			m_Paddle.getSprite().setTexture(m_imgMgr.getPaddle());
			m_Ball.getSprite().setTexture(m_imgMgr.getBall());
		}
		background = title;
		break;
	case about:
		{
			background = about;
			m_AboutText.setString("Left and right keys for movement, escape to pause, and space to launch the ball! Avoid hitting the red bricks!");
		}
		break;
	case running:
		if (background != running && background != paused)
		{
			m_Paddle.initialize();
			m_Ball.initialize();
			m_Clock.restart();
			m_Paddle.resetLives();
			if (!m_Bricks.empty())
			{
				m_Bricks.clear();
				m_lvlMgr.setupLevel(m_Bricks, m_imgMgr);
			}
			else
				m_lvlMgr.setupLevel(m_Bricks, m_imgMgr);
		}
		background = running;
		break;
	default:
		break;
	}
}

void Game::update()
{
	switch (m_GameState)
	{
	case title:
		m_Quit.setPosition(675.0f, 540.0f);
		m_About.setPosition(675.0f, 500.0f);
		m_NewGame.setPosition(670.0f, 460.0f);
		break;
	case about:
		break;
	case running:
		{
		std::stringstream printLives;
		printLives << "Lives left = ";
		printLives << m_Paddle.livesLeft();
		m_LivesText.setString(printLives.str());
		m_Paddle.update(m_deltaTime);
		m_Ball.update(m_deltaTime, m_Paddle, m_Bricks);
		}
		break;
	case gamelost:
		m_GameOver.setPosition(350.0f, 250.0f);
		break;
	case gamewon:
		m_GameWon.setPosition(350.0f, 250.0f);
		break;
	case paused:
		m_Paused.setPosition(350.0f, 250.0f);
	default:
		break;
	}
}

void Game::drawAll()
{
	switch (m_GameState)
	{
	case title:
		m_Window.draw(m_Background);
		m_Window.draw(m_Quit);
		m_Window.draw(m_About);
		m_Window.draw(m_NewGame);
		break;
	case about:
		{
		m_Window.draw(m_AboutText);
		}
		break;
	case running:
		{
		m_Window.draw(m_LivesText);
		m_Window.draw(m_Paddle.getSprite());
		m_Window.draw(m_Ball.getSprite());
		for (auto iter = m_Bricks.begin(); iter != m_Bricks.end(); ++iter)
		{
			if ((*iter)->isAlive())
			{
				m_Window.draw((*iter)->getSprite());
			}
		}
		}		
		break;
	case gamelost:
		{
		m_Window.draw(m_LivesText);
		m_Window.draw(m_Paddle.getSprite());
		m_Window.draw(m_Ball.getSprite());
		for (auto iter = m_Bricks.begin(); iter != m_Bricks.end(); ++iter)
		{
			if ((*iter)->isAlive())
			{
				m_Window.draw((*iter)->getSprite());
			}
		}
		m_Window.draw(m_GameOver);
		}		
		break;
	case gamewon:
		{
		m_Window.draw(m_LivesText);
		m_Window.draw(m_Paddle.getSprite());
		m_Window.draw(m_Ball.getSprite());
		for (auto iter = m_Bricks.begin(); iter != m_Bricks.end(); ++iter)
		{
			if ((*iter)->isAlive())
			{
				m_Window.draw((*iter)->getSprite());
			}
		}
		m_Window.draw(m_GameWon);
		}		
		break;
	case paused:
		{
		m_Window.draw(m_LivesText);
		m_Window.draw(m_Paddle.getSprite());
		m_Window.draw(m_Ball.getSprite());
		for (auto iter = m_Bricks.begin(); iter != m_Bricks.end(); ++iter)
		{
			if ((*iter)->isAlive())
			{
				m_Window.draw((*iter)->getSprite());
			}
		}
		m_Window.draw(m_Paused);
		}		
		break;
	default:
		break;
	}
}

bool Game::isLevelWon()
{
	bool isWon = false;
	int aliveBricks = 0;
	for (auto iter = m_Bricks.begin(); iter != m_Bricks.end(); iter++)
	{
		if ((*iter)->getType() == "blue" && (*iter)->isAlive() == true)
		{
			aliveBricks++;
		}
	}
	if(aliveBricks > 0)
		return false;
	else
		return true;
}

void Game::run()
{
	//m_Window.setFramerateLimit(60);
	m_GameState = title;

	while (!isExiting())	// This is the main game loop responsible for handling events, updating game logic and drawing assets.
	{
		m_Window.pollEvent(m_Event);

		static Input_Manager::titleResult tresult;
		static Input_Manager::aboutResult aresult;
		static Input_Manager::gameResult  gresult;
		static Input_Manager::gamelostResult lresult;
		static Input_Manager::gamewonResult wresult;
		static Input_Manager::pauseResult presult;

		switch (m_GameState)
		{
		case title:
			tresult = m_inpMgr.titleEvents(m_Event);	// Accesses the titleEvents function in input manager class and returns a result.
			if (tresult == Input_Manager::exit)			// Based on the result the game state changes appropriately.
				m_GameState = exiting;
			else if (tresult == Input_Manager::about)
				m_GameState = about;
			else if (tresult == Input_Manager::newGame)
				m_GameState = running;
			else
				break;
			break;
		case about:
			aresult = m_inpMgr.aboutEvents(m_Event);	// Accesses the aboutEvents function in input manager class and returns a result.
			if (aresult == Input_Manager::back)			// Based on the result the game state changes appropriately.
				m_GameState = title;
			else
				break;
			break;
		case running:
			gresult = m_inpMgr.gameEvents(m_Event, m_Paddle, m_Ball);		// Accesses the gameEvents function in input manager class and returns a result.
			if (gresult == Input_Manager::prev)			// Based on the result the game state changes appropriately.
				m_GameState = title;
			else if (gresult == Input_Manager::paused)
				m_GameState = paused;
			else if (gresult == Input_Manager::idle && m_Paddle.livesLeft() > 0 && isLevelWon() == false);

			else if (gresult == Input_Manager::idle && m_Paddle.livesLeft() > 0 && isLevelWon() == true)
				m_GameState = gamewon;

			else if (gresult == Input_Manager::idle && m_Paddle.livesLeft() < 0)
				m_GameState = gamelost;
			
			else
				break;
			break;
		case gamelost:
			lresult = m_inpMgr.lostEvents(m_Event);
			if (lresult == Input_Manager::nada);

			else if (lresult == Input_Manager::mainMenu)
				m_GameState = title;
			break;
		case gamewon:
			wresult = m_inpMgr.wonEvents(m_Event);
			if (wresult == Input_Manager::idling);

			else if (wresult == Input_Manager::menu)
				m_GameState = title;
			break;
		case paused:
			presult = m_inpMgr.pauseEvents(m_Event);
			if (presult == Input_Manager::doNothing);

			else if (presult == Input_Manager::theMainMenu)
				m_GameState = title;
			else if (presult == Input_Manager::resume)
				m_GameState = running;
			break;
		default:
			break;
		}

		setTextures();		// Sets all the textures according to game states.

		m_deltaTime = m_Clock.getElapsedTime().asSeconds();

		m_Clock.restart();	// Reset the clock

		update();			// Updates the position of all the items on screen

		m_Window.clear();	// Clear the window to black color
		
		drawAll();			// Draws all the sprite members to the renderTarget.

		m_Window.display();	// Finally display the window.

		sf::sleep(sf::milliseconds(2));
	}

	m_Window.close();
}

bool Game::isExiting()
{
	return m_GameState == exiting;
}