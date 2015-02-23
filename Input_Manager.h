#pragma once

class Input_Manager
{
public:
	Input_Manager(void);
	~Input_Manager(void);

	enum titleResult { newGame, about, exit, nothing };
	enum aboutResult { noAction, back };
	enum gameResult { idle, prev, paused };
	enum gamelostResult { mainMenu, nada };
	enum gamewonResult { menu, idling };
	enum pauseResult { theMainMenu, resume, doNothing };

	titleResult titleEvents(sf::Event &Event);
	aboutResult aboutEvents(sf::Event &Event);
	gamelostResult lostEvents(sf::Event &Event);
	gamewonResult wonEvents(sf::Event &Event);
	pauseResult pauseEvents(sf::Event &Event);
	gameResult gameEvents(sf::Event &Event, Paddle& paddle, Ball& ball);
};