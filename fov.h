#ifndef FOV_H
#define FOV_H
#include"Entity.h"

const float DEG2RAD = 3.14159f / 100.0f;

class fov
{
public:
	fov();
	~fov();
	bool fovCalculate(Position & playerPos, Position & targetPos, int dist , int tileSize);

private: 
	float max(float a, float b); 
	int diag_dist(int x0, int y0, int x1, int y1); 
	float lerp(float start, float end, float t); 
	


};

#endif // !FOV_H
