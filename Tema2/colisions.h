#include <vector>
#include "lab_m1/Tema2/util.h"
#include "lab_m1/Tema2/enemy.h"
#include "lab_m1/Tema2/projectile.h"
#include <math.h>

class Colision
{
public:
	Colision();
	void Set_Colision(std::vector<std::vector<struct floor_struct>> maze_floor, std::vector<Enemy*> enemys, float player_position_x, float player_position_z, int floor_width, int floor_length);
	bool Find_Wall_Player_Colision();
	bool Find_Enemy_Player_Colision();
	void Find_Projectile_Wall_Ground_Colision(std::vector<Projectile*>& projectiles);
	//bool Find_Enemy_Projectile_Colision(std::vector<Enemy*>& enemys, std::vector<Projectile*>& projectiles);
	bool Find_Enemy_Projectile_Colision_One(Enemy* enemys, std::vector<Projectile*>& projectiles);
	~Colision();

private:
	std::vector<std::vector<struct floor_struct>> maze_floor;
	std::vector<Enemy*> enemys;
	std::vector<Projectile*> projectiles;
	float player_position_x;
	float player_position_z;
	int floor_width;
	int floor_length;
};