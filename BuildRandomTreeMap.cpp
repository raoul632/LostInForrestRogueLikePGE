#include "BuildRandomTreeMap.h"



BuildRandomTreeMap::BuildRandomTreeMap(int heightOfDMap, int widthOfDMap, float percentComplete) : mHeightOfDMap(heightOfDMap), mWidthOfMap(widthOfDMap), mPercentComplete(percentComplete) {
	std::vector<int> vMapCopy(mHeightOfDMap * mWidthOfMap, 1);
	vMap = vMapCopy;
	vMap.at(mWalkerPosition) = 0;
	mCaseFill = 0;
	mWalkerPosition = 0; //rand() % (mHeightOfDMap * mWidthOfMap); //on place un point aléatoire
	isMapOK = false; 
}

//WRITE 9 FOR THE END OF THE PATH 
bool BuildRandomTreeMap::WalkInDirection(int index)
{
	bool isExit = false;

	if (index >= 0 && index <= ((mHeightOfDMap * mWidthOfMap) - 1)) {
		if (vMap.at(index) == 1)
		{
			vMap.at(index) = 0;
			sPreviousWalk.push(mWalkerPosition);
			mWalkerPosition = index;
			//std::cout << mWalkerPosition << std::endl;
			mCaseFill++;
			mNumberOfMoveByTurn = 0;
			if (mCaseFill >= ((mHeightOfDMap * mWidthOfMap) * mPercentComplete))
			{
				vMap.at(index) = 9; 
				isMapOK = true; 
				isExit = true;
			}
		}
		else
		{
			mNumberOfMoveByTurn++;

			if (mNumberOfMoveByTurn > 4) //arbitrary number 
			{
				if (sPreviousWalk.size() > 0)
				{
					mWalkerPosition = sPreviousWalk.top();
					sPreviousWalk.pop();
				}
				else
				{
					isExit = true;

				}
			}
		}
	}
	return isExit;
}

void BuildRandomTreeMap::Walk()
{
	/*
	2D -> 1D
	i = x + width*y;
	and the reverse operation is
	x = i % width;    // % is the "modulo operator", the remainder of i / width;
	y = i / width;    // where "/" is an integer division

	1D -> 2D
	x = i % width;
	y = (i / width)%height;
	z = i / (width*height);
	*/
	//move random direction and reverse the track when there is no option 

	int caseComplete{ 0 };
	int numberOfMoveByTurn{ 0 };
	bool isExit = false;
	//it <= numIteration &&
	while (!isExit)
	{
		bool asWalk = false;
		auto seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
		std::mt19937 mt_rand(seed);
		auto dice_rand = std::bind(std::uniform_int_distribution<int>(0, 4),
			std::mt19937(mt_rand));
		Direction = static_cast<WalkDirection>(dice_rand()); //n s e w
		int x = mWalkerPosition %  mWidthOfMap;
		int y = mWalkerPosition / mHeightOfDMap;

		int index{ 0 };
		auto calculIndex = [=](int x, int y) {return x + y * mWidthOfMap; };

		if (Direction == North) {
			if ((y - 1) >= 0)
			{
				y -= 1;
				index = calculIndex(x, y);
				isExit = WalkInDirection(index);
			}
		}
		else if (Direction == South) {
			if ((y + 1) <= mHeightOfDMap)
			{
				y += 1;
				index = calculIndex(x, y);
				isExit = WalkInDirection(index);
			}
		}
		else if (Direction == West) {
			if (x - 1 >= 0)
			{
				x -= 1;
				index = calculIndex(x, y);
				isExit = WalkInDirection(index);
			}
		}
		else if (Direction == East) {
			if (x + 1 <= mWidthOfMap)
			{
				x += 1;
				index = calculIndex(x, y);
				isExit = WalkInDirection(index);
			}
		}
	}
	//std::cout << "iteration number to know if the result wanted is good" << mCaseFill << std::endl;
}

void BuildRandomTreeMap::ShowMap() const
{
	for (int y = 0; y < mHeightOfDMap; y++)
	{
		for (int x = 0; x < mWidthOfMap; x++)
		{
			std::cout << vMap.at(x + y * mWidthOfMap);

		}
		std::cout << '\n';
	}
}

int BuildRandomTreeMap::GetWidth()
{
	return mWidthOfMap;
}

int BuildRandomTreeMap::GetHeight()
{
	return mHeightOfDMap;
}

std::vector<int> BuildRandomTreeMap::GetMap() const
{
	return vMap;
}