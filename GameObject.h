#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <memory>
#include <stdint.h>
#include <map>
#include <string>
#include <vector>
#include <iostream>
#include <assert.h>
typedef unsigned int UniqueId; 

class GameObject; 

static GameObject *player = nullptr;
static std::vector<GameObject> gGameObject; 


enum GameComponent {
	POSITION = 0,
	VISIBILITY,
	PHYSICAL,

};

struct Component  {
	std::string name; 
	//virtual Component *clone(void) const = 0;
	virtual ~Component() {} // And so on for base classes.
	
};

struct Position : public Component {
	unsigned short x; 
	unsigned short y;
	Position() {
	name = "Position";
	}
};


struct Visibility : public Component {
	unsigned int fgColor;
	unsigned int bgColor;
	bool hasBeenSeen;
	Visibility() {
		name = "Visibility";
	}
};

struct Physical : public Component {
	std::string name = "Physical";
	bool blocksMovement;
	bool blocksSight;
	Physical() {
		name = "Physical";
	}

};



class GameObject
{
public:
	UniqueId id;
	//void *pComponents; 
	GameObject* Create(); 
	void UpdateComponent(); 
	Position* mPos = nullptr; 
	Visibility* mVis = nullptr; 
	Physical* mPhy = nullptr; 



	 void addComponent(Component* comp) {
		 if (comp->name == "Position") {

			 mPos = (Position* )comp; 
		 }
		
	};


	Component* getComponent(std::string nameSearch) {

		Component* res = nullptr;

		if (nameSearch == "Position") {
			//std::cout << mPos->name << " " << mPos->x << " " << mPos->y; 
		}
		
		return res; 

	}

	GameObject();
	~GameObject();
};

#endif // !GAMEOBJECT_H

