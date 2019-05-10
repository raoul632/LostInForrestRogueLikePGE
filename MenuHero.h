#ifndef MENUHERO_H
#define MENUHERO_H
#include <string>
#include "olcPixelGameEngine.h"
#include "Entity.h"



class MenuHero
{
private: 
	int mWidth, mHeight, mx, my; 
	std::string mTitle; 
	Entity * mHeros; 

public:
	MenuHero(int width, int height, int x, int y, std::string title,Entity  * h);
	void Update();
	void Render(olc::PixelGameEngine & p) const;
	
	~MenuHero();



};

#endif // !MENUHERO_H
