// Eent Tord.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"


int main(int argc, _TCHAR* argv[])
{
	srand((unsigned int)time(0));	// Seed the random number generator

	Game game;	// Initialize the game object and create a window

	game.run();

	return 0;
}