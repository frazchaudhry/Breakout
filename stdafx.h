// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>



// TODO: reference additional headers your program requires here
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <memory>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <vector>
#include <fstream>
#include <sstream>

#include "Random.h"
#include "Game_Object.h"
#include "Paddle.h"
#include "Brick.h"
#include "Ball.h"
#include "Image_Manager.h"
#include "Input_Manager.h"
#include "Level_Manager.h"
#include "Game.h"

const int SCREENWIDTH = 832;
const int SCREENHEIGHT = 600;
const int PADDLEYPOS = 550.0f;
const int MAXPADDLESPEED = 400.0f;