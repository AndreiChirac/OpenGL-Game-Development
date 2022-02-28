#include "lab_m1/Tema2/enemy.h"

Enemy::Enemy()
{
}

Enemy::Enemy(Point spawn, Point initial_pos, float speed)
{
    this->spawn = spawn;
    this->initial_pos = initial_pos;
    this->speed = speed;
}


std::vector<Enemy*> Enemy::Create_Enemy(std::vector<std::vector<struct floor_struct>> &maze_floor, int floor_width, int floor_length)
{
    int empty_space = 0;
    std::vector<Enemy*> enemys;

    for (int i = 0; i < floor_length; i++) {
        for (int j = 0; j < floor_width; j++) {
            if (maze_floor[i][j].status == 0) {
                empty_space++;
            }
        }
    }

    int enemy_nr = rand() % (empty_space - 15 + 1) + 15;
    std::cout << enemy_nr << "enemy nr \n";

    for (int i = 0; i < enemy_nr; i++) {
        int x_pos = rand() % (floor_length);
	    int z_pos = rand() % (floor_width);

        if (maze_floor[x_pos][z_pos].status == 0 && x_pos != 0 && z_pos != 0 && x_pos != floor_length - 1 && z_pos != floor_width - 1) {
            Point spawn;
            Point initial_pos;
            spawn.x = x_pos + 0.3;
            spawn.z = z_pos + 0.3;
            initial_pos.x = x_pos + 0.3;
            initial_pos.z = z_pos + 0.3;
            maze_floor[x_pos][z_pos].status = 2;
            
            enemys.push_back(new Enemy(spawn, initial_pos,  ((double)rand() / (RAND_MAX)) + 1));
        }
    }
    return enemys;
}

void Enemy::Move_Enemy(std::vector<Enemy*>& enemys, float delta_time, float offsetof)
{
    for (int i = 0; i < enemys.size(); i++) {
        if (!enemys[i]->status) {
            if (enemys[i]->state == 0) {
                enemys[i]->spawn.x += enemys[i]->speed * delta_time;
                if (enemys[i]->spawn.x > enemys[i]->initial_pos.x + 1 - offsetof) {
                    enemys[i]->spawn.x = enemys[i]->initial_pos.x + 1 - offsetof;
                    enemys[i]->state++;
                }
            }
            else if (enemys[i]->state == 1) {
                enemys[i]->spawn.z += enemys[i]->speed * delta_time;
                if (enemys[i]->spawn.z > enemys[i]->initial_pos.z + 1 - offsetof) {
                    enemys[i]->spawn.z = enemys[i]->initial_pos.z + 1 - offsetof;
                    enemys[i]->state++;
                }
            }
            else if (enemys[i]->state == 2) {
                enemys[i]->spawn.x -= enemys[i]->speed * delta_time;
                if (enemys[i]->spawn.x < enemys[i]->initial_pos.x) {
                    enemys[i]->spawn.x = enemys[i]->initial_pos.x;
                    enemys[i]->state++;
                }
            }
            else if (enemys[i]->state == 3) {
                enemys[i]->spawn.z -= enemys[i]->speed * delta_time;
                if (enemys[i]->spawn.z < enemys[i]->initial_pos.z) {
                    enemys[i]->spawn.z = enemys[i]->initial_pos.z;
                    enemys[i]->state = 0;
                }
            }
        }
    }
}

Enemy::~Enemy()
{
}