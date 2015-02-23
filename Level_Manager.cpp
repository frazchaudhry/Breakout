#include "StdAfx.h"
#include "Level_Manager.h"


Level_Manager::Level_Manager(void) : m_Current_Level(1)
{
	
}


Level_Manager::~Level_Manager(void)
{
}

void Level_Manager::setLevel(int level)
{
	m_Current_Level = level;
}

void Level_Manager::setupLevel(std::vector<std::unique_ptr<Brick>>& bricks, Image_Manager& m_imgMgr)
{
	m_brickType.clear();
	const int MAXBRICKS = 65;
	float xPos = 0.0f, yPos = 50.0f;
	const float HOFFSET = 64.0f;
	const float VOFFSET = 20.0f;
	const int BRICKROW = 13;
	int count = 0;
	std::ifstream inFile("levels/Walls.txt");
	if (inFile)
	{
		int numLevel = 0, level = 0, type = 0;
		std::string garbage = "";
		inFile >> garbage >> numLevel;
		inFile >> garbage >> level;
		for ( int i = 0; i < MAXBRICKS; ++i )
		{
			inFile >> type;
			m_brickType.push_back(type);
		}

		for (auto iter = m_brickType.begin(); iter != m_brickType.end(); ++iter)
			{
				std::string type = "";
				if ( *iter == 1 )
				{
					type = "blue";
					bricks.push_back(std::unique_ptr<Brick>(new Brick(m_imgMgr.getBlue(), type)));
					
				}
				else if ( *iter == 2)
				{
					type = "red";
					bricks.push_back(std::unique_ptr<Brick>(new Brick(m_imgMgr.getRed(), type)));
				}
			}

		for (auto iter = bricks.begin(); iter != bricks.end(); iter++)
			{
				(*iter)->setPos(sf::Vector2f(xPos, yPos));
				xPos += HOFFSET;
				count++;
				if ( count % BRICKROW == 0 )
				{
					xPos = 0.0f;
					yPos += VOFFSET;
				}
			}
		
	}
	else
		std::cout << "Could not open file!" << std::endl;
}

int Level_Manager::getCurrentLevel()
{
	return m_Current_Level;
}

int Level_Manager::getNumberOfLevels()
{
	return 1;						// To be updated later!!!!
}

void Level_Manager::addBrick(int num)
{
	m_brickType.push_back(num);
}
