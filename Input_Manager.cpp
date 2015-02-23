#include "StdAfx.h"


Input_Manager::Input_Manager(void)
{
}


Input_Manager::~Input_Manager(void)
{
}

Input_Manager::titleResult Input_Manager::titleEvents(sf::Event &Event)
{
	switch(Event.type)
		{
		case sf::Event::Closed:
			return exit;
			break;
		case sf::Event::KeyPressed:
			switch(Event.key.code)
			{
			case sf::Keyboard::Escape:
				return exit;
				break;
			default:
				return nothing;
				break;
			}
		case sf::Event::MouseButtonPressed:
			if (Event.mouseButton.button == sf::Mouse::Left)		// If mouse click is inside the Quit button
			{														// The application will exit.
				if(Event.mouseButton.x > 675.0f
					&& Event.mouseButton.x < 675.0f + 54.0f
					&& Event.mouseButton.y > 540.0f
					&& Event.mouseButton.y < 540.0f + 16.0f)
					return exit;
				else if (Event.mouseButton.x > 675.0f
					&& Event.mouseButton.x < 675.0f + 64.0f			// If mouse click is inside the about button
					&& Event.mouseButton.y > 500.0f					// The application will display the about screen.
					&& Event.mouseButton.y < 500.0f + 22.0f)
					return about;
				else if (Event.mouseButton.x > 670.0f				// If mouse click is inside the new game button
					&& Event.mouseButton.x < 675.0f + 108.0f		// The application will display the game screen.
					&& Event.mouseButton.y > 460.0f
					&& Event.mouseButton.y < 460.0f + 32.0f)
					return newGame;
				else
					return nothing;
			}
			else
				return nothing;
			break;
		default:
			return nothing;
			break;
		}
	return nothing;
}

Input_Manager::aboutResult Input_Manager::aboutEvents(sf::Event& Event)
{
	switch(Event.type)
		{
		case sf::Event::Closed:
			return back;
			break;
		case sf::Event::KeyPressed:
			switch(Event.key.code)
			{
			case sf::Keyboard::Escape:
				return back;
				break;
			default:
				return noAction;
				break;
			}
		case sf::Event::MouseButtonPressed:
			if (Event.mouseButton.button == sf::Mouse::Left)
			{
				if(Event.mouseButton.x > 0.0f						// Clicking the mouse button anywhere inside the
					&& Event.mouseButton.x < (float)SCREENWIDTH					// window will take it back to the title screen.
					&& Event.mouseButton.y > 0.0f
					&& Event.mouseButton.y < (float)SCREENHEIGHT)
					return back;
				else
					return noAction;
			}
		default:
			return noAction;
			break;
		}
	return noAction;
}

Input_Manager::gameResult Input_Manager::gameEvents(sf::Event& Event, Paddle& paddle, Ball& ball)
{
	switch(Event.type)
		{
		case sf::Event::Closed:
			return prev;
			break;
		case sf::Event::KeyPressed:
			switch(Event.key.code)
			{
			case sf::Keyboard::Escape:
				return paused;
				break;
			case sf::Keyboard::Left:
				if (ball.isBallMoving)
				{
					paddle.m_Speed -= 40.0f;
					if (paddle.m_Speed < -MAXPADDLESPEED)
						paddle.m_Speed = -MAXPADDLESPEED;
				}
				return idle;
				break;
			case sf::Keyboard::Right:
				if (ball.isBallMoving)
				{
					paddle.m_Speed += 40.0f;
				    if (paddle.m_Speed > MAXPADDLESPEED)
						paddle.m_Speed = MAXPADDLESPEED;
				}
				return idle;
				break;
			case sf::Keyboard::Space:
				if(!ball.isBallMoving)
					ball.isBallMoving = true;
				return idle;
				break;
			default:
				return idle;
				break;
			}
		case sf::Event::KeyReleased:
			switch(Event.key.code)
			{
			case sf::Keyboard::Left:
				paddle.m_Speed = 0.0f;
				return idle;
				break;
			case sf::Keyboard::Right:
				paddle.m_Speed = 0.0f;
				return idle;
				break;
			default:
				return idle;
				break;
			}
		default:
			return idle;
			break;
		}
	return idle;
}

Input_Manager::gamelostResult Input_Manager::lostEvents(sf::Event &Event)
{
	switch (Event.type)
	{
	case sf::Event::MouseButtonPressed:
		if (Event.mouseButton.button == sf::Mouse::Left)
		{
			if (Event.mouseButton.x	>= 380.0f &&
				Event.mouseButton.x <= 460.0f &&
				Event.mouseButton.y	>= 385.0f &&
				Event.mouseButton.y	<= 400.0f)
				return mainMenu;
		}
		break;
	default:
		break;
	}
	return nada;
}

Input_Manager::gamewonResult Input_Manager::wonEvents(sf::Event &Event)
{
	switch (Event.type)
	{
	case sf::Event::MouseButtonPressed:
		if (Event.mouseButton.button == sf::Mouse::Left)
		{
			if (Event.mouseButton.x	>= 380.0f &&
				Event.mouseButton.x <= 460.0f &&
				Event.mouseButton.y	>= 375.0f &&
				Event.mouseButton.y	<= 385.0f)
				return menu;
		}
		break;
	default:
		break;
	}
	return idling;
}

Input_Manager::pauseResult Input_Manager::pauseEvents(sf::Event &Event)
{
	switch (Event.type)
	{
	case sf::Event::MouseButtonPressed:
		if (Event.mouseButton.button == sf::Mouse::Left)
		{
			if (Event.mouseButton.x	>= 385.0f &&
				Event.mouseButton.x <= 445.0f &&
				Event.mouseButton.y	>= 260.0f &&
				Event.mouseButton.y	<= 280.0f)
				return resume;
			else if (Event.mouseButton.x >= 370.0f &&
					 Event.mouseButton.x <= 440.0f &&
					 Event.mouseButton.y >= 375.0f &&
					 Event.mouseButton.y <= 390.0f)
					 return theMainMenu;
		}
		break;
	case sf::Event::KeyPressed:
		switch (Event.key.code)
		{
		case sf::Keyboard::Escape:
			return resume;
		}
	default:
		break;
	}
	return doNothing;
}