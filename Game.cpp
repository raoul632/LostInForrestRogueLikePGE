
#include "Game.h"
#include "Entity.h"
#include "BuildRandomTreeMap.h"
#include "MenuHero.h"
#include <iostream>
#include "fov.h"
#include "ConsoleLog.h"
#include <cmath>

//THIS IS THE SYSTEM IN ECS ALL LOGICAL STUFF WAS HERE

Game::Game()
{
	sAppName = "Lost In the Forrest";


}

bool Game::OnUserCreate()
{

	pGameAtlasTexture = new olc::Sprite("images\\terminal16x16.png");
	pGameEnding = new olc::Sprite("images\\Victory.png"); 
	pGameIntro = new olc::Sprite("images\\intro.png");
	mScreenWidth = ScreenWidth();
	mScreenHeight = ScreenHeight(); //heightScreen;  //ScreenHeight()
	mGameScreen.w = mScreenWidth - 74;
	mGameScreen.h = mScreenHeight - 20;
	mGameScreen.x = 10;
	mGameScreen.y = 10;
	mCurrentState = GameState::INTRO;
	mFov = new fov(); 
	mConsoleLog = new ConsoleLog(mScreenWidth, mScreenHeight);
	LoadLevel();
	return true;
}



bool Game::ClearEntity() {

	mWorldPosition.x = 0; 
	mWorldPosition.y = 0; 
	for (std::vector<Entity*>::iterator it = sGameObject.begin(); it != sGameObject.end(); ++it) {
		delete(*it);
	}
	sGameObject.clear(); 

	if (player != nullptr) {
	 player = nullptr;
	}

	return true;

}

bool Game::LoadLevel() {

	if (sGameObject.size() > 0) ClearEntity(); 

	//Creation du joueur 
	CreatePlayer();
	

	//create map; 
	mBlrd = new BuildRandomTreeMap(50, 50, 0.4f);
	mBlrd->Walk();

	//create goal

	std::vector<int> treeMap = mBlrd->GetMap();

	mMenuHero = new MenuHero(mGameScreen.w, mScreenHeight, mGameScreen.w, 0, "LOST\nIN\nFOREST", player);

	int mapWidth = mBlrd->GetWidth();
	int mapHeight = mBlrd->GetHeight();

	for (int y = 0; y < mapWidth; y++)
	{
		for (int x = 0; x < mapHeight; x++)
		{
			

			if (treeMap.at(x + y * mapWidth) == 0) {

				int res = RoleDice(100);
				if (res <= 2) {
					CreateRandomEnemy(x * mSizeTile, y * mSizeTile);
					treeMap.at(x + y * mapWidth) = 2; 
				}
			};
			if (treeMap.at(x + y * mapWidth) == 1) {
				AddTreeToEntityList(x * mSizeTile, y * mSizeTile);
			};
			if (treeMap.at(x + y * mapWidth) == 9) {

				CreateGoal(x * mSizeTile, y * mSizeTile); 
			}
		}
		//
	}

/*	for (int y = 0; y < mapWidth; y++)
	{
		for (int x = 0; x < mapHeight; x++)
		{
			if (treeMap.at(x + y * mapWidth) == 0) {
				AddGroundToEntityList(x * mSizeTile, y * mSizeTile);
			}

			std::cout << treeMap.at(x + y * mapWidth);
		}
		std::cout << '\n';

	}*/
	//on rajoute a la liste des objets 

	sGameObject.push_back(player);

	//création des enemies sur la carte 
	//CreateEnemy(rat); 
	UpdateFov();
	return true; 
}

/*
rat
transmette la peste
DEGAT 1D2
1pv
2 FO
2D6 HAB

loup
1D6 de pv
DEGAT 1D4
2D6 FORCE
2D6 HAB

Serpent
1D4 PV
1D4 FO
2D6 + 2 HAB */
void Game::CreateRandomEnemy(int x, int y) {
	Entity* enemy = new Entity;
	listEnemy le; 
	int res = RoleDice(100);
	if (res <= 10) {
		le = listEnemy::wolf; 
	}
	else if (res <= 30 ) {
		le = listEnemy::snake; 
	}
	else {
		le = listEnemy::rat; 
	}

	

	switch (le)
	{
	case rat: {
		int FO = RoleDice(2) ;
		int HB = RoleDice(6) + RoleDice(6) ;
		int EN = RoleDice(2) ;
		enemy->add_component<Physical>(true, false, listImage::ratImage);
		enemy->add_component<Position>(x, y);
		enemy->add_component<Skill>(FO, HB, EN);
		enemy->add_component<Enemy>("rat");
		enemy->add_component<Plague>();
		enemy->add_component<Visibility>(); 

		break;
	}
	case snake: {
		int FO = RoleDice(3) + 1;
		int HB = RoleDice(6) + RoleDice(6) +2;
		int EN = RoleDice(4) + 1;
		enemy->add_component<Physical>(true, false, listImage::snakeImage);
		enemy->add_component<Position>(x, y);
		enemy->add_component<Skill>(FO, HB, EN);
		enemy->add_component<Enemy>("snake");
		enemy->add_component<Visibility>();
		break;
	 }
	case wolf: {
		int FO = RoleDice(10) ;
		int HB = RoleDice(6) + RoleDice(6);
		int EN = RoleDice(6);
		enemy->add_component<Physical>(true, false, listImage::wolfImage);
		enemy->add_component<Position>(x, y);
		enemy->add_component<Skill>(FO, HB, EN);
		enemy->add_component<Enemy>("wolf");
		enemy->add_component<Visibility>();

		}
	}
	sGameObject.push_back(enemy);

}

/*
paysans  peasant
1d10+2 de pv
8 FO + 1D10
8 HAB +1D10
DEGAT 1PV + FO /4*/
void Game::CreatePlayer() {
	
	player = new Entity;
	//player->add_component<Health>(6, 10);
	player->add_component<Player>("Hutin");
	//player->add_component<Attack>(4);
	player->add_component<Position>(0, 0);
	player->add_component<Physical>(true, false, listImage::peasantImage);
	int FO = RoleDice(10) + 8;
	int HB = RoleDice(10) + 8;
	int EN = RoleDice(10) + 2;
	player->add_component<Skill>(FO, HB, EN);
	player->add_component<Visibility>();
	player->get<Visibility>().areVisible = true; 

}

void Game::CreateGoal(int x, int y) {
	Entity* princess = new Entity;
	princess->add_component<Position>(x, y);
	princess->add_component<Physical>(true, false, listImage::princessImage);
	princess->add_component<Goal>(); 
	princess->add_component<Visibility>();

	sGameObject.push_back(princess);
}



void Game::AddGroundToEntityList(short x, short y) {
	Entity* ground = new Entity;
	ground->add_component<Physical>(false, false, solImage);
	ground->add_component<Position>(x, y);
	ground->add_component<Visibility>();
	sGameObject.insert(sGameObject.begin(), ground);
	//vLog.insert(vLog.begin(), std);

}

void Game::AddTreeToEntityList(short x, short y) {
	Entity* wall = new Entity; 
	wall->add_component<Physical>(true, false, arbreImage);
	wall->add_component<Position>(x, y);
	wall->add_component<Visibility>();
	sGameObject.push_back(wall);


}

//maj
void Game::Update()
{
	if (mCurrentState == GameState::END)
	{
		if (GetKey(olc::ENTER).bPressed) {
			mCurrentState = GameState::GAME;
			LoadLevel();
		}
	}

	if (mCurrentState == GameState::INTRO) {

		if (GetKey(olc::ENTER).bPressed) {
			mCurrentState = GameState::GAME;
			LoadLevel();
		}
		
	}

	if (mCurrentState == GameState::DEAD) {

		if (GetKey(olc::ENTER).bPressed) {
			mCurrentState = GameState::GAME;
			LoadLevel();
		}

	}

	if (mCurrentState == GameState::GAME)
	{
		Position pPos = player->get<Position>();
		if (GetKey(olc::RIGHT).bPressed) {
			mConsoleLog->ResetLog();
			pPos.x += mSizeTile;
			MovementUpdate(pPos);
		}
		if (GetKey(olc::LEFT).bPressed) {
			mConsoleLog->ResetLog();
			pPos.x -= mSizeTile;
			MovementUpdate(pPos);
		}
		if (GetKey(olc::UP).bPressed) {
			mConsoleLog->ResetLog();
			pPos.y -= mSizeTile;
			MovementUpdate(pPos);
		}
		if (GetKey(olc::DOWN).bPressed) {
			mConsoleLog->ResetLog();
			pPos.y += mSizeTile;
			MovementUpdate(pPos);
		}
		
	}
	
}



bool Game::CanMove(Position& newPos)
{
	bool moveAllowed = true;
	int sizeMapWidth = mBlrd->GetWidth() * mSizeTile; 
	int sizeMapHeight = mBlrd->GetHeight() * mSizeTile; 
	if ((newPos.x >= 0) && (newPos.x < sizeMapWidth) && (newPos.y >= 0) && (newPos.y < sizeMapHeight))
	{
		for (auto& const pGameObject  = sGameObject.begin(); pGameObject != sGameObject.end(); ++pGameObject)
		{
			const Position& p = (*pGameObject)->get<Position>(); 
			if (p.x == newPos.x && p.y == newPos.y) {
				if ((*pGameObject)->get<Physical>().blocksMovement == true) {
					moveAllowed = false; 

				}
			}
		}

	}
	else {
		moveAllowed = false; 
		return moveAllowed; 
	}	
	return moveAllowed;

}


void Game::Behavior() {

}


int Game::RoleDice(int num) {
	auto seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
	std::mt19937 mt_rand(seed);
	auto dice_rand = std::bind(std::uniform_int_distribution<int>(1, num),
	std::mt19937(mt_rand));
	return dice_rand(); 
}

//uniquement joueur 
bool Game::IsAttacking(Position& newPos) {

	for (auto& it = sGameObject.begin(); it != sGameObject.end(); ++it)
	{
		Position& p = (*it)->get<Position>();
		if ( p == newPos && (*it)->has_component<Enemy>()) {
			   
			Enemy& e = (*it)->get<Enemy>();

			//on lance deux D20  un pour l'attaquant l'autre pour le defenseur 
			int attaquant = RoleDice(20); 
			int defenseur = RoleDice(20); 
			std::string touche = "Player rolls the dice :";
			touche.append(std::to_string(attaquant));
			touche.append(" - ");
			touche.append(e.name);
			touche.append(" rolls the dice :");
			touche.append(std::to_string(defenseur));
			
			mConsoleLog->AddLog(touche);
			if ((player->get<Skill>().hability + attaquant) > (*it)->get<Skill>().hability + defenseur) {
				int numDegat = player->get<Skill>().force / 3; 
				(*it)->get<Skill>().Endurance -= numDegat; 
			
				std::string touche = "you touch "; 
				touche.append(e.name); 
				touche.append(" - ");
				touche.append(std::to_string(numDegat));
				touche.append(" Dmg"); 
				mConsoleLog->AddLog(touche); 

				if ((*it)->get<Skill>().Endurance <= 0) {
					Entity* t = (*it); 
					MakeDead(*t); 
				}
			}
			else {
				std::string touche = "you miss ";
				touche.append(e.name);
				mConsoleLog->AddLog(touche);

			}
			
			return true; 
		}
	}
	return false; 
}

void Game::MakeDead(Entity& corps) {
	corps.remove_component<Enemy>(); 
	corps.remove_component<Skill>();
	corps.get<Physical>().blocksMovement = false; 
	corps.get<Physical>().glyph = listImage::mortImage;
}


//random le joueur peux être mis a jour avant ou aprés les enemies peut être rajouté une cara qui change la donne
void Game::MovementUpdate(Position& newPos) {
	int res  = RoleDice(6); 
	if (res <= 2) {
		//std::cout << " 1 er enemie 2eme perso " << std::endl; 
		MovementEnemyUpdate();
		MovementPlayerUpdate(newPos);
	}
	if (res > 2) {
		MovementPlayerUpdate( newPos); 
		MovementEnemyUpdate(); 
		//std::cout << " 1er perso " << std::endl;

	}


}

bool Game::IsEnemyAttacking(Position& newPos , Entity& e) {
	if (player->get<Position>() == newPos) {
		//on lance deux D20  un pour l'attaquant l'autre pour le defenseur 
		int attaquant = RoleDice(20);
		int defenseur = RoleDice(20);
		
		std::string touche = e.get<Enemy>().name;
		touche.append(" rolls the dice :");
		touche.append(std::to_string(attaquant));
		touche.append(" - ");
		touche.append("Player rolls the dice :");
		touche.append(std::to_string(defenseur));
		mConsoleLog->AddLog(touche);

		if ((e.get<Skill>().hability + attaquant) > (player->get<Skill>().hability + defenseur)) {
			int numDegat = (e.get<Skill>().force / 3) + 1;
			player->get<Skill>().Endurance -= numDegat;

			std::string touche = "Enemy touch Player";
			touche.append(" - ");
			touche.append(std::to_string(numDegat));
			touche.append(" Dmg");
			mConsoleLog->AddLog(touche);

			//infection par la peste 

			if (e.has_component<Plague>() && !player->has_component<Plague>()) {
				player->add_component<Plague>(); 
				player->get<Skill>().force -= 4; 
				player->get<Skill>().hability -= 4; 


			}

			//mort du personnage
			if (player->get<Skill>().Endurance <= 0) {
				mCurrentState = GameState::DEAD; 	
			}
		}
		else {

			std::string touche = "Enemy Miss";
			mConsoleLog->AddLog(touche);


		}

		return true;
	}

	return false;
}


void Game::MovementEnemyUpdate() {

	for (auto& it = sGameObject.begin(); it != sGameObject.end(); ++it)
	{
		if ((*it)->has_component<Enemy>()) {
			//est ce que le joueur est en ligne de vue 
			Position& pos = (*it)->get<Position>(); 
			int distance{ 0 }; 
			int dx = pos.x - player->get<Position>().x; 
			int dy = pos.y - player->get<Position>().y; 
			int adx = std::abs(dx); 
			int ady = std::abs(dy); 
			distance = (adx + ady) / mSizeTile; 
			//std::cout << distance << " la distance " << std::endl; 
			Position changePos = pos; 
			Entity* t = (*it);
			//si égal a 5 alors le joueur est en vue 
			if (distance <= 5) {

				if (adx > ady) {
					if (dx < 0) {
						//bouge droite 
						changePos.x += mSizeTile;
						//Entity* t = (*it);
						//MakeDead(*t);
						if (!IsEnemyAttacking(changePos, *t))
						{
							if (CanMove(changePos)) {
								//std::cout << changePos.x << "  dx < 0 " << std::endl;
								//std::cout << player->get<Position>().x << "  player x " << std::endl;
								(*it)->get<Position>().x = changePos.x;
							}
						}
					}
					else {
						//bouge gauche
						changePos.x -= mSizeTile;
						if (!IsEnemyAttacking(changePos, *t))
						{
							if (CanMove(changePos)) {
								//std::cout << changePos.x << "  dx > 0 " << std::endl;
								//std::cout << player->get<Position>().x << "  player x " << std::endl;
								(*it)->get<Position>().x = changePos.x;
							}
						}
					}
				}
				else {
					if (dy < 0) {
						//monte
						changePos.y += mSizeTile;
						if (!IsEnemyAttacking(changePos, *t))
						{
							if (CanMove(changePos)) {

								//std::cout << changePos.y << "  dy < 0 " << std::endl;
								//std::cout << player->get<Position>().y << "  player y " << std::endl;
								(*it)->get<Position>().y = changePos.y;
							}
						}
					}
					else {
						changePos.y -= mSizeTile;
						if (!IsEnemyAttacking(changePos, *t))
						{
							if (CanMove(changePos)) {
								//std::cout << changePos.y << "  dy > 0 " << std::endl;
								//std::cout << player->get<Position>().y << "  player y " << std::endl;
								(*it)->get<Position>().y = changePos.y;
							}
						}
						//descend
					}

				}
			}






		}
	}


}

bool Game::IsGoal(Position& newPos) {

	for (auto& it = sGameObject.begin(); it != sGameObject.end(); ++it)
	{
		Position& p = (*it)->get<Position>();
		if (p == newPos && (*it)->has_component<Goal>()) {
			return true; 
		}
	}
	return false; 

}

void Game::MovementPlayerUpdate(Position& newPos) {

	//gestion des comportements des entités 

	if (IsGoal(newPos)) {
		mCurrentState = GameState::END; 
	}

	//gestion attack 
	if (IsAttacking(newPos)) {

	}


	if (CanMove(newPos))
	{
		UpdateFov(); 
		//deplacement caméra Y

		if (player->get<Position>().y > newPos.y) {
			if (player->get<Position>().y > (mScreenHeight / 2))
			{
			//	std::cout << player->get<Position>().y << " player y" << std::endl; 
				if((mWorldPosition.y - mSizeTile) >= 0)
				mWorldPosition.y -= mSizeTile;

				//std::cout << mWorldPosition.y << " world position y" << std::endl;
			}
		}
		else if (player->get<Position>().y < newPos.y) {
			if (player->get<Position>().y >(mScreenHeight / 2))
			{
			//	std::cout << player->get<Position>().y << " player y" << std::endl;
				mWorldPosition.y += mSizeTile;
				//std::cout << mWorldPosition.y << " world position y" << std::endl;
			}
		}
		//deplacement caméra X 
		if (player->get<Position>().x > newPos.x) {
			if (player->get<Position>().x >(mGameScreen.w / 2))
			{
			//	std::cout << player->get<Position>().x << " player x" << std::endl;
				if ((mWorldPosition.x - mSizeTile) >= 0)
					mWorldPosition.x -= mSizeTile;
				//std::cout << mWorldPosition.x << std::endl;
			}
		}
		else if (player->get<Position>().x < newPos.x) {
			if (player->get<Position>().x >(mGameScreen.w / 2))
			{
			//	std::cout << player->get<Position>().x << " player x" << std::endl;
				mWorldPosition.x += mSizeTile;
				//std::cout << mWorldPosition.x << std::endl;
			}
		}
		player->get<Position>().y = newPos.y;
		player->get<Position>().x = newPos.x;	
	}

}


void Game::UpdateFov()  {

Position& playerPos = player->get<Position>(); 

//pour tous ce qui n'est pas joueur on set la visibilté a false'
for (auto& it = sGameObject.begin(); it != sGameObject.end(); ++it)
{
	if (!(*it)->has_component<Player>())
	{
		(*it)->get<Visibility>().areVisible = false; 
	}

}


for (auto& it = sGameObject.begin(); it != sGameObject.end(); ++it)
	{
		Position& target = (*it)->get<Position>();

		if (mFov->fovCalculate(playerPos, target, 4* mSizeTile, mSizeTile)) {
			(*it)->get<Visibility>().areVisible = true; 
			(*it)->get<Visibility>().wasVisible = true;
		}
	}

}


//drawing
void Game::Render() 
{
	Clear(olc::BLACK);
	//DrawRect(mGameScreen.x, mGameScreen.y, mGameScreen.w, mGameScreen.h);

	if (mCurrentState == GameState::INTRO) {
		DrawSprite((mScreenWidth / 4), 0, pGameIntro);
		DrawString((mScreenWidth / 3) , mScreenHeight / 2, "PRESS ENTER TO START");
		/*cum equite putas? vos autem anno MCCC et uxor tua est: perdidi in silva*/
		DrawString((mScreenWidth / 4), mScreenHeight / 2 + 50, "CUM EQUITE PUTAS ? ", olc::DARK_GREEN);
		DrawString((mScreenWidth / 4), mScreenHeight / 2 + 62, "VOS AUTEM ANNO MCCC ET UXOR TUA EST:", olc::DARK_GREEN);
		DrawString((mScreenWidth / 4), mScreenHeight / 2 + 74, "PERDIDI IN SILVA", olc::DARK_GREEN);

	}

	if (mCurrentState == GameState::GAME)
	{
		DrawLine(mGameScreen.w, 0, mGameScreen.w, mScreenHeight);

		//MENU DROITE
		mMenuHero->Render(*this);
Position& p = player->get<Position>(); 

		

		//changeColorSprite({ 0xff,0xff, 0xff }, { 0xff,0x00, 0x00 }, pGameAtlasTexture);
		
	
		FillCircle((p.x + 8) - mWorldPosition.x, (p.y + 8) - mWorldPosition.y, 64, olc::BLACKTEST2);
		FillCircle((p.x + 8) - mWorldPosition.x, (p.y + 8) - mWorldPosition.y, 48, olc::BLACKTEST);
		//std::cout << (*itdeb)->get<Position>().x << " premier element x" << std::endl; 
		//std::cout << (*itdeb)->get<Position>().y << " premier element y" << std::endl;
	
		for (auto& const it = sGameObject.begin() ; it != sGameObject.end(); ++it)
		{

			if ((*it)->has_component<Position>()) {
				if ((*it)->get<Visibility>().areVisible)
				{
					const Physical& phy = (*it)->get<Physical>();
					const Position& p = (*it)->get<Position>();
					if ((p.x + mSizeTile) < (mGameScreen.w + mWorldPosition.x))
						DrawPartialSprite((p.x - mWorldPosition.x), (p.y - mWorldPosition.y), pGameAtlasTexture, 0 + (phy.glyph * mSizeTile), 0, 16, 16, 1);
				}
				/*else if ((*it)->get<Visibility>().wasVisible) {
					Physical& phy = (*it)->get<Physical>();
					Position& p = (*it)->get<Position>();
					//FillRect((p.x + 8), (p.y + 8), 16, 16, olc::BLACKTEST2); 
					//changeBritnessColorSprite(pGameAtlasTexture); 
					if ((p.x + mSizeTile) < (mGameScreen.w + mWorldPosition.x))
						DrawPartialSprite((p.x - mWorldPosition.x) - mWorldPosition.x, (p.y - mWorldPosition.y) - mWorldPosition.y, pGameAtlasTexture, 0 + (phy.glyph * mSizeTile), 0, 16, 16, 1);

				}*/
			}

		}
		olc::Pixel::ALPHA;
		
		

		mConsoleLog->Render(*this); 
	}
	if (mCurrentState == GameState::DEAD) {
		DrawString((mScreenWidth / 3) , mScreenHeight / 2 - 30, "YOURE DEAD");
		DrawString((mScreenWidth / 4) , mScreenHeight / 2 , "PRESS ENTER TO RESTART");
	}
	if (mCurrentState == GameState::END) {
		DrawSprite((mScreenWidth / 4), 0, pGameEnding);
		DrawString((mScreenWidth / 3) , mScreenHeight / 2, "VICTORIA? NOBILIS PAYSANT");
		
	}
	olc::Pixel::NORMAL; 
}



bool Game::OnUserUpdate(float fElapsedTime)
{
	//mMenuHero->Update(); 
	Update(); 
	Render(); 
	return true;
}


void Game::changeColorSprite(olc::Pixel originalColor, olc::Pixel targetColor, olc::Sprite* targetSprite)
{
	for (int y = 0; y < targetSprite->height; y++)
	{
		for (int x = 0; x < targetSprite->width; x++)
		{
			if ((targetSprite->GetPixel(x, y).b == originalColor.b) && (targetSprite->GetPixel(x, y).g == originalColor.g) && (targetSprite->GetPixel(x, y).r == originalColor.r))
			{
				targetSprite->SetPixel(x, y, targetColor);
			}
		}
	}
}



Game::~Game()
{
	delete pGameAtlasTexture;
	delete pGameEnding; 
	delete pGameIntro; 
	pGameAtlasTexture = NULL;
	//fin du jeux on suprime 
	for (std::vector<Entity*>::iterator it = sGameObject.begin(); it != sGameObject.end(); ++it) {
		delete(*it);

	}
	sGameObject.clear();
	delete mBlrd;
	mBlrd = nullptr; 
	delete mMenuHero;
	mMenuHero = nullptr; 
	delete mFov; 
	mFov = nullptr; 
	delete mConsoleLog; 
	mConsoleLog = nullptr; 

}

int main()
{
	Game rogue;
	if (rogue.Construct(512, 256, 2, 2))
		rogue.Start();
	return 0;
}