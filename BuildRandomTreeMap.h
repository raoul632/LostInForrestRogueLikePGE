#ifndef BUILDRANDOM_MAP_H
#define BUILDRANDOM_MAP_H


#include <iostream>
#include <vector>
#include <random> //
#include <chrono>
#include <functional> //std::bind
#include <stack>          // std::stack
#include <exception>




enum WalkDirection {
	North = 0,
	South,
	East,
	West
};

class BuildRandomTreeMap {

public:
	BuildRandomTreeMap(int heightOfDMap, int widthOfDMap, float percentComplete); 
	//walk in a direction and file case
	bool WalkInDirection(int index); 
	void Walk(); 
	void ShowMap() const; 
	int GetWidth(); 
	int GetHeight(); 

	std::vector<int> GetMap() const; 


private:
	int mHeightOfDMap;
	int mWidthOfMap;
	int mCaseFill;
	float mPercentComplete;
	int mWalkerPosition;
	std::vector<int> vMap;
	WalkDirection Direction;
	int mNumberOfMoveByTurn;
	bool isMapOK; //if the contract is filled
	std::stack<int> sPreviousWalk;//keep track of the walk 



};


#endif // !BUILDRANDOM8MAP_H