#include "fov.h"



fov::fov()
{
}


fov::~fov()
{
}

float fov::max(float a, float b)
{
	return a > b ? a : b;
}

int fov::diag_dist(int x0, int y0, int x1, int y1)
{
	int dx = x1 - x0, dy = y1 - y0;
	return max(abs(dx), abs(dy));
}

float fov::lerp(float start, float end, float t)
{
	return start + t * (end - start);
}

bool fov::fovCalculate(Position & playerPos, Position & targetPos,  int dist, int tileSize)
{
	//360 degre de rotation 
	//for (int i = 0; i < 360; i++) {

		//float deg = i * DEG2RAD;

		//trouve la fin de la ligne 
	/*
	int nx = round(cos(deg) * dist) + playerPos.x;//c'est la position du joueur 
	int ny = round(sin(deg) * dist) + playerPos.y;*/
		int nx = round(cos(0) * dist) + playerPos.x; //c'est la position du joueur 
	    int ny = round(sin(0) * dist) + playerPos.y;

		//maintenant qu'on a le point final on trouve combien de tuile sont traversé
		//on calcul avec la distance diagonal
		int d = diag_dist(playerPos.x, playerPos.y, nx, ny);
		//maintenant on passe a travers toute les tuiles  grace a l'interpolation linéaire
		//on interpole par decrasing la distance du joueur au point final 
		//bougeant d'une tuile 

		//taille d'une tuile ??
			//le ratio courant est la distance courante / la distance total 
		//	int tx = lerp(playerPos.x, nx, j / ((float)d));
		//	int ty = lerp(playerPos.y, ny, j / ((float)d));
		if (((targetPos.x > (playerPos.x - d)) && (targetPos.x < (playerPos.x + d))) && ((targetPos.y >(playerPos.y - d)) && (targetPos.y < (playerPos.y + d)))) {
				//std::cout << targetPos.y << " target pos y "<<  std::endl;
				//std::cout << playerPos.y << " player pos y"<<std::endl;
				//std::cout << playerPos.y - d << " player - d " << d << std::endl;
				//std::cout << playerPos.y + d << " player + d " << d << std::endl;
				return true;
			
		}
			
		else {
				return false; 
			}

			//&& (abs(targetPos.y) < (abs(playerPos.y) + d)


			//on verifie que la tuile est bien dans la carte 
			//if (tx < 0 || tx > map->w) continue;
			//if (ty < 0 || ty > map->h) continue;

			//si c'est un murs on le marque comme vue mais on stop la ligne plus tot 
			/*if (map->map[tx + ty * map->w] == WALL) {
				//formule  pour trouvez un index 1d de cooronnée 2d 
				map->seen[tx + ty * map->w] = 1;
				break;
			}
			map->seen[tx + ty * map->w] = 1;
			map->glare[tx + ty * map->w] = 1;*/

		

	//}
	//return false; 
}
