#ifndef CONSOLELOG_H
#define CONSOLELOG_H
#include "olcPixelGameEngine.h"
#include <string>



class ConsoleLog
{
private : 
	std::vector<std::string> vLog; 
	int mScreenWidth, mScreenHeight;

public:
	ConsoleLog(int screenWidth, int screenHeight);
	~ConsoleLog();
    
	void ResetLog(); 
	void AddLog(std::string std); 
	void Render(olc::PixelGameEngine& p) const; 
};

#endif // !CONSOLELOG_H