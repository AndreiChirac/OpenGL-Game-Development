#include <lab_m1/Tema2/colisions.h>


Colision::Colision()
{
}

void Colision::Set_Colision(std::vector<std::vector<struct floor_struct>> maze_floor, std::vector<Enemy*> enemys, float player_position_x, float player_position_z, int floor_width, int floor_length)
{
	this->maze_floor = maze_floor;
	this->enemys = enemys;
	this->player_position_x = player_position_x;
	this->player_position_z = player_position_z;
	this->floor_width = floor_width;
	this->floor_length = floor_length;
}

bool Colision::Find_Wall_Player_Colision()
{
	bool status = false;
	for (int i = 0; i < floor_length; i++) {
		for (int j = 0; j < floor_width; j++) {

			if (maze_floor[i][j].status == 1) {
				if ((player_position_x - 0.25 < maze_floor[i][j].x + 1 && player_position_x + 0.25 > maze_floor[i][j].x) &&
					(player_position_z - 0.25 < maze_floor[i][j].z + 1 && player_position_z + 0.25 > maze_floor[i][j].z)) {
					status = true;
				 }
			}
		}
	}
	return status;
}

bool Colision::Find_Enemy_Player_Colision()
{
	bool status = false;
	
	for (int i = 0; i < enemys.size(); i++) {

		if ((player_position_x - 0.25 < enemys[i]->spawn.x + std::get<2>(enemys[i]->map_object["box"]) && player_position_x + 0.25 > enemys[i]->spawn.x - std::get<2>(enemys[i]->map_object["box"])) &&
			(player_position_z - 0.15 < enemys[i]->spawn.z + std::get<2>(enemys[i]->map_object["box"])  && player_position_z + 0.15 > enemys[i]->spawn.z - std::get<2>(enemys[i]->map_object["box"]))) {
			status = true;
			
		}
	}
	return status;
}

void Colision::Find_Projectile_Wall_Ground_Colision(std::vector<Projectile*>& projectiles)
{

	bool status = false;

	for (int i = 0; i < projectiles.size(); i++) {
		std::cout << projectiles[i]->curr_pos.y << " \n";
		if (projectiles[i]->curr_pos.y - projectiles[i]->radius <= 0) {
			projectiles.erase(projectiles.begin() + i);
			--i;
		} else {
			for (int j = 0; j < floor_length; j++) {
				for (int k = 0; k < floor_width; k++) {
					if (maze_floor[j][k].status == 1) {

						float x = MAX(maze_floor[j][k].x, MIN(projectiles[i]->curr_pos.x, maze_floor[j][k].x + 1));
						float y = MAX(0, MIN(projectiles[i]->curr_pos.y, 2));
						float z = MAX(maze_floor[j][k].z, MIN(projectiles[i]->curr_pos.z, maze_floor[j][k].z + 1));

						float distance = sqrt((x - projectiles[i]->curr_pos.x) * (x - projectiles[i]->curr_pos.x) +
							(y - projectiles[i]->curr_pos.y) * (y - projectiles[i]->curr_pos.y) +
							(z - projectiles[i]->curr_pos.z) * (z - projectiles[i]->curr_pos.z));

						if (distance < projectiles[i]->radius) {
							status = true;
						}
					}
				}
			}
			if (status) {
				projectiles.erase(projectiles.begin() + i);
				--i;
			}
		}
	}
}

bool Colision::Find_Enemy_Projectile_Colision_One(Enemy* enemys, std::vector<Projectile*>& projectiles)
{
	bool status = false;
	std::map<std::string, std::tuple<float, float, float>>::iterator it;

	for (int j = 0; j < projectiles.size(); j++) {

		for (it = enemys->map_object.begin(); it != enemys->map_object.end(); it++) {
			if (strcmp(it->first.c_str(), "box") == 0) {

				float x = MAX(enemys->spawn.x - std::get<2>(it->second), MIN(projectiles[j]->curr_pos.x, enemys->spawn.x + std::get<2>(it->second)));
				float y = MAX(std::get<0>(it->second), MIN(projectiles[j]->curr_pos.y, std::get<1>(it->second)));
				float z = MAX(enemys->spawn.z - std::get<2>(it->second), MIN(projectiles[j]->curr_pos.z, enemys->spawn.z + std::get<2>(it->second)));

				float distance = sqrt((x - projectiles[j]->curr_pos.x) * (x - projectiles[j]->curr_pos.x) +
					(y - projectiles[j]->curr_pos.y) * (y - projectiles[j]->curr_pos.y) +
					(z - projectiles[j]->curr_pos.z) * (z - projectiles[j]->curr_pos.z));

				if (distance < projectiles[j]->radius) {
					status = true;
				}


			}
			else {
				float distance = sqrt((projectiles[j]->curr_pos.x - enemys->spawn.x) * (projectiles[j]->curr_pos.x - enemys->spawn.x) +
					(projectiles[j]->curr_pos.y - std::get<0>(it->second)) * (projectiles[j]->curr_pos.y - std::get<1>(it->second)) +
					(projectiles[j]->curr_pos.z - enemys->spawn.z) * (projectiles[j]->curr_pos.z - enemys->spawn.z));

				if (distance < (projectiles[j]->radius + std::get<2>(it->second))) {
					status = true;
				}
			}
		}
		if (status) {
			projectiles.erase(projectiles.begin() + j);
			--j;
		}

	}
	

	return status;
}


Colision::~Colision()
{
}
