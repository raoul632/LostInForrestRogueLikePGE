#ifndef GAME_H
#define GAME_H
#include "Main.h"

enum GameState {
	INTRO,
	GAME, 
	DEAD,
	END

};

class fov; 
enum listEnemy; 
enum listImage; 
struct Entity;
struct Position; 
struct Visibility; 
class BuildRandomTreeMap; 
class MenuHero; 
class ConsoleLog; 


struct WorldPosition {
	WorldPosition(int x = 0, int y = 0) {}; 
	int x, y; 
};

struct GameScreen {
	GameScreen() = default; 
	GameScreen(int _x, int _y, int _w, int _h) :x(_x), y(_y), w(_w),h(_h) {};
	int x, y, w, h; 

};

class Game : public olc::PixelGameEngine
{
public:
	const short mSizeTile = 16; 
	Game();
	~Game();

	bool ClearEntity();

	bool LoadLevel();

	

private : 
	void CreateRandomEnemy(int x, int y);
	void Update();
	bool CanMove(Position& newPos);
	void Behavior();
	int RoleDice(int num);
	bool IsAttacking(Position& newPos);
	bool IsEnemyAttacking(Position & newPos, Entity & e);
	void MakeDead(Entity & corps);
	void MovementUpdate(Position & newPos);
	void MovementEnemyUpdate();
	bool IsGoal(Position & newPos);
	void MovementPlayerUpdate(Position & newPos);
	void UpdateFov();
	void Render();
	bool OnUserCreate() override;
	void CreatePlayer();
	void CreateGoal(int x, int y);
	void CreateEnemy(listEnemy le);
	void AddGroundToEntityList(short x, short y);
	void AddTreeToEntityList(short x, short y);
	bool OnUserUpdate(float fElapsedTime) override;

	void changeColorSprite(olc::Pixel originalColor, olc::Pixel targetColor, olc::Sprite * targetSprite);
	unsigned int mScreenWidth; 
	unsigned int mScreenHeight; 
	GameScreen mGameScreen; 
	WorldPosition mWorldPosition; 
	BuildRandomTreeMap* mBlrd; 
 	MenuHero* mMenuHero; 
	listImage eListImage; 
	GameState mCurrentState; 
	fov* mFov; 
	ConsoleLog* mConsoleLog; 
	
	olc::Sprite* pGameAtlasTexture; 
	olc::Sprite* pGameIntro; 
	olc::Sprite* pGameEnding; 
	Entity* player; 


};

#endif // !GAME_H

