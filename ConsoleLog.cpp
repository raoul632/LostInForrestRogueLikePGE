#include "ConsoleLog.h"



ConsoleLog::ConsoleLog(int screenWidth, int screenHeight):mScreenWidth(screenWidth), mScreenHeight(screenHeight)
{

}


ConsoleLog::~ConsoleLog()
{
}

void ConsoleLog::ResetLog()
{

	vLog.clear(); 
}

void ConsoleLog::AddLog(std::string std)
{
	vLog.insert(vLog.begin(), std); 
}

void ConsoleLog::Render(olc::PixelGameEngine & p) const
{
	int index = 12; 
	for (auto &i : vLog) {
		p.DrawString(12 , mScreenHeight - index, i);
		index += 12; 
	 }
	
}
