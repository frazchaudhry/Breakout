#pragma once

class Level_Manager
{
public:
	Level_Manager(void);
	~Level_Manager(void);

	void setLevel(int level);
	void setupLevel(std::vector<std::unique_ptr<Brick>>& bricks, Image_Manager& m_imgMgr);
	int getCurrentLevel();
	int getNumberOfLevels();
	void addBrick(int num);

private:
	int				m_Current_Level;
	std::vector<int>	m_brickType;
};

