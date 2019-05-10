
#include "MenuHero.h"
#include "Main.h"




MenuHero::MenuHero(int width, int height, int x, int y, std::string title, Entity  * heros ) : mWidth(width), mHeight(height), mx(x), my(y), mTitle(title)
{
	mHeros = heros; 

}

void MenuHero::Update()
{

}

void MenuHero::Render(olc::PixelGameEngine& p) const
{
	p.DrawString(mx + 5, my, mTitle,olc::GREEN); 

	//FORCE
	std::string f = "FORCE:"; 
	f.append(std::to_string(mHeros->get<Skill>().force));
	p.DrawString(mx + 5, my + 40, f);
	//HABILITE
	f = "HAB:";
	f.append(std::to_string(mHeros->get<Skill>().hability));
	p.DrawString(mx + 5, my + 50, f);

	//ENDURANCE
	f = "PV:";
	f.append(std::to_string(mHeros->get<Skill>().Endurance));
	p.DrawString(mx + 5, my + 60, f);

	if (mHeros->has_component<Plague>()) {

		f = "Plague"; 
		p.DrawString(mx + 5, my + 80, f, olc::DARK_GREEN);

	}
	
	
	//p.DrawString(mx + 25, my + 40, "FORCE : mHeros->get<Skill>().force")


}



MenuHero::~MenuHero()
{
	mHeros = nullptr; 

}
