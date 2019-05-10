#ifndef ENTITY_H
#define ENTITY_H
//SIMPLE ECS ENTITY AND COMPONENT WAS HERE ALL LOGICAL STUFF HAPPEN IN GAME
//all ENTITY was STORE IN --> static vector<Entity*> sGameObject;
#include <iostream>
#include <vector>
#include <map>
#include <memory>
#include <string>
#include "Global.h"

using namespace std;

enum listWeapon {
	sword,
	axe,
	spear
};

enum listEnemy {
	snake, 
	rat,
	wolf,
};

struct Counter {
	static int c;

};

enum listImage {
	herosImage, 
	solImage, 
	arbreImage, 
	orcImage, 
	ratImage, 
	mortImage,
	snakeImage,
	wolfImage,
	princessImage,
	peasantImage,

};




template <typename T>
struct ClassID : Counter {
	static int id() {
		static int c = Counter::c++;
		return c;
	}

};

template<typename T>
int ClassID_v = ClassID < std::decay_t<T>>::id();

struct Component {};

struct Entity {
	map<int, unique_ptr<Component>> components;
	template<typename Component>
	Component& get() {
		return static_cast<Component&>(*components[ClassID_v<Component>]);
	}

	template <typename Component>
	bool has_component() { return components.count(ClassID_v<Component>); }

	template<typename Component, typename... Args>
	Entity& add_component(Args&&... args) { //parameter pack
											//map::emplace insert element if its key is unique 
		components.emplace(ClassID_v<Component>, std::make_unique<Component>(std::forward<Args>(args)...));

		return *this;
	}

	template<typename Component>
	void remove_component() { 
		components.erase(ClassID_v<Component>);
	}


};

struct Health :Component {
	Health() = default;
	Health(int current, int max) : current_health(current), max_health(max) {};
	int current_health = 100, max_health = 100;

};

struct Name : Component {
	string name = "no name";
	Name() = default;
	Name(std::string n) :name(n) {};
};

struct Corpse : Component {
	Corpse() = default; 
};


struct Attack : Component {
	int attack = 0;
	Attack() = default;
	Attack(int a) : attack(a) {};
	

};

struct Goal : Component {
	Goal() = default; 
};

struct Player : Component {
	string name = "";
	Player() = default;
	Player(string n) : name(n) {};
	
};


struct Enemy : Component {
	string name = "";
	Enemy() = default;
	Enemy(string n) : name(n) {};
	

};

struct Position :Component {
	short x;
	short y;
	Position() = default; 
	Position(short _x, short _y) :x(_x), y(_y) {}; 

	friend bool operator== (const Position& lhs, const Position& rhs)
	{
		return (lhs.x == rhs.x) && (rhs.y == lhs.y);
	}
	
};



struct Weapon : Component {
	listWeapon weapon; 
	int dmg; 
	Weapon() = default; 
	Weapon(listWeapon w, int d) : weapon(w), dmg(d) {}; 


};

enum listArmor {
	leather, 
	chainshirt, 
	mudarmor, 

};

struct Armor : Component {
	listArmor armor;
	int protection; 
	Armor() = default; 
	Armor(listArmor a, int p) : armor(a), protection(p) {};

};

struct Skill : Component {
	int force; 
	int hability; 
	int Endurance; 
	Skill() = default; 
	Skill(int f, int h, int e) : force(f), hability(h), Endurance(e) {}; 

};


struct Physical : Component {
	bool blocksMovement;
	bool blocksSight;
	char glyph; 
	Physical() = default; 
	Physical(bool _blocksMovement, bool _blocksSight, char _glyph) : blocksMovement(_blocksMovement), blocksSight(_blocksSight), glyph(_glyph) {  };
	
};

struct Visibility : Component {
	bool areVisible; 
	bool wasVisible; 
	Visibility() = default;
	Visibility(bool are, bool was):areVisible(are = false), wasVisible(was = false){};

} ;

struct Plague : Component {

}; 


static vector<Entity*> sGameObject;

#endif
