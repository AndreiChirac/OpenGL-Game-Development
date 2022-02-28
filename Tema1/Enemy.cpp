#include "Enemy.h"

#include <vector>


using namespace std;

void Enemy::CreateEnemy(
    std::vector< m1::Tema1::Enemy_Struct> &enemys,
    int nr_of_enemies,
    int map_x,
    int map_y) {


    float enemy_spawn_x;
    float enemy_spawn_y;

    for (int i = 0; i < nr_of_enemies; i++) {

        enemy_spawn_x = (float(rand()) / float((RAND_MAX)) * map_x);
        enemy_spawn_y = (float(rand()) / float((RAND_MAX)) * map_x);

        while (Enemy::check_overlap_enemy(enemy_spawn_x, enemy_spawn_y, enemys) ||
            1.7f < enemy_spawn_x && enemy_spawn_x < 2.3f ||
            1.7f < enemy_spawn_y && enemy_spawn_y < 2.3f ||
            1.7f < enemy_spawn_x + 0.4 && enemy_spawn_x + 0.4 < 2.3f ||
            1.7f < enemy_spawn_y + 0.4 && enemy_spawn_y + 0.4 < 2.3f ||
            0.0f > enemy_spawn_x + 0.6 || enemy_spawn_x + 0.6 > 4.0f ||
            0.0f > enemy_spawn_y + 0.6 || enemy_spawn_y + 0.6 > 4.0f ||
            0.0f > enemy_spawn_x - 0.15 || 0.0f > enemy_spawn_y - 0.15) {

            enemy_spawn_x = (float(rand()) / float((RAND_MAX)) * map_x);
            enemy_spawn_y = (float(rand()) / float((RAND_MAX)) * map_y);

        }
        m1::Tema1::Enemy_Struct enemy;
        enemy.x_enemy = enemy_spawn_x;
        enemy.y_enemy = enemy_spawn_y;
        enemy.x_enemy_initial = enemy_spawn_x;
        enemy.y_enemy_initial = enemy_spawn_y;
        enemy.speed_enemy = (float)rand() / (float)RAND_MAX;
        enemys.push_back(enemy);
    }
    
}


void Enemy::Move_Enemy(
    std::vector< m1::Tema1::Enemy_Struct>& enemys,
    std::vector< m1::Tema1::Bullet_Struct>& bullets,
    float x_player,
    float y_player,
    float x_left_arm,
    float y_left_arm,
    float x_right_arm,
    float y_right_arm,
    float x_backpack,
    float y_backpack,
    float body_radius,
    float arm_radius,
    float backpack_radius,
    float radians,
    float enemy_width,
    float enemy_height,
    float bullet_width,
    float bullet_height,
    float &score,
    float &health_bar_scale_width,
    float deltaTimeSeconds,
    int& game_over) {

    int status = 0;

    for (int i = 0; i < enemys.size(); i++) {
        status = false;

       float delta_x = abs(x_player - enemys[i].x_enemy_initial);
        float delta_y = abs(y_player - enemys[i].y_enemy_initial);

        if (enemys[i].x_enemy < x_player && enemys[i].y_enemy < y_player) {
            if (Colision::CheckEnemyHitPlayer(x_player, y_player, x_left_arm,
                y_left_arm, x_right_arm, y_right_arm, x_backpack, y_backpack,
                enemys[i].x_enemy + enemys[i].speed_enemy * delta_x * deltaTimeSeconds,
                enemys[i].y_enemy + enemys[i].speed_enemy * delta_y * deltaTimeSeconds,
                enemy_width, enemy_height, body_radius, arm_radius,
                backpack_radius, radians)) {
                status = 1;
            }
            else if (Colision::CheckBulletHitEnemy(bullets, 
                enemys[i].x_enemy + enemys[i].speed_enemy * delta_x * deltaTimeSeconds,
                enemys[i].y_enemy + enemys[i].speed_enemy * delta_y * deltaTimeSeconds,
                enemy_width, enemy_height, bullet_width, bullet_height)) {
                 status = 2;
            }
            else if (!Colision::CheckEnemyInside(
                enemys[i].x_enemy + enemys[i].speed_enemy * delta_x * deltaTimeSeconds,
                enemys[i].y_enemy + enemys[i].speed_enemy * delta_y * deltaTimeSeconds,
                enemy_width, enemy_height)) {
                enemys[i].x_enemy += enemys[i].speed_enemy * delta_x * deltaTimeSeconds;
                enemys[i].y_enemy += enemys[i].speed_enemy * delta_y * deltaTimeSeconds;
            }
            
        }
        if (enemys[i].x_enemy < x_player && enemys[i].y_enemy > y_player) {
            if (Colision::CheckEnemyHitPlayer(x_player, y_player, x_left_arm,
                y_left_arm, x_right_arm, y_right_arm, x_backpack, y_backpack,
                enemys[i].x_enemy + enemys[i].speed_enemy * delta_x * deltaTimeSeconds,
                enemys[i].y_enemy - enemys[i].speed_enemy * delta_y * deltaTimeSeconds,
                enemy_width, enemy_height, body_radius, arm_radius,
                backpack_radius, radians)) {
                 status = 1;
            }
            else if (Colision::CheckBulletHitEnemy(bullets,
                enemys[i].x_enemy + enemys[i].speed_enemy * delta_x * deltaTimeSeconds,
                enemys[i].y_enemy - enemys[i].speed_enemy * delta_y * deltaTimeSeconds,
                enemy_width, enemy_height, bullet_width, bullet_height)) {
                 status = 2;
            }
            else if (!Colision::CheckEnemyInside(
                enemys[i].x_enemy + enemys[i].speed_enemy * delta_x * deltaTimeSeconds,
                enemys[i].y_enemy - enemys[i].speed_enemy * delta_y * deltaTimeSeconds,
                enemy_width, enemy_height)) {
                enemys[i].x_enemy += enemys[i].speed_enemy * delta_x * deltaTimeSeconds;
                enemys[i].y_enemy -= enemys[i].speed_enemy * delta_y * deltaTimeSeconds;
                }
        }
        if (enemys[i].x_enemy > x_player && enemys[i].y_enemy < y_player) {
            if (Colision::CheckEnemyHitPlayer(x_player, y_player, x_left_arm,
                y_left_arm, x_right_arm, y_right_arm, x_backpack, y_backpack,
                enemys[i].x_enemy - enemys[i].speed_enemy * delta_x * deltaTimeSeconds,
                enemys[i].y_enemy + enemys[i].speed_enemy * delta_y * deltaTimeSeconds,
                enemy_width, enemy_height, body_radius, arm_radius,
                backpack_radius, radians)) {
                status = 1;
            }
            else if (Colision::CheckBulletHitEnemy(bullets,
                enemys[i].x_enemy - enemys[i].speed_enemy * delta_x * deltaTimeSeconds,
                enemys[i].y_enemy + enemys[i].speed_enemy * delta_y * deltaTimeSeconds,
                enemy_width, enemy_height, bullet_width, bullet_height)) {
                status = 2;
            }
            else if (!Colision::CheckEnemyInside(
                enemys[i].x_enemy - enemys[i].speed_enemy * delta_x * deltaTimeSeconds,
                enemys[i].y_enemy + enemys[i].speed_enemy * delta_y * deltaTimeSeconds,
                enemy_width, enemy_height)) {
                enemys[i].x_enemy -= enemys[i].speed_enemy * delta_x * deltaTimeSeconds;
                enemys[i].y_enemy += enemys[i].speed_enemy * delta_y * deltaTimeSeconds;
            }
        }
        if (enemys[i].x_enemy > x_player && enemys[i].y_enemy > y_player) {
            if (Colision::CheckEnemyHitPlayer(x_player, y_player, x_left_arm,
                y_left_arm, x_right_arm, y_right_arm, x_backpack, y_backpack,
                enemys[i].x_enemy - enemys[i].speed_enemy * delta_x * deltaTimeSeconds,
                enemys[i].y_enemy - enemys[i].speed_enemy * delta_y * deltaTimeSeconds,
                enemy_width, enemy_height, body_radius, arm_radius,
                backpack_radius, radians)) {
                status = 1;
            }
            else if (Colision::CheckBulletHitEnemy(bullets,
                enemys[i].x_enemy - enemys[i].speed_enemy * delta_x * deltaTimeSeconds,
                enemys[i].y_enemy - enemys[i].speed_enemy * delta_y * deltaTimeSeconds,
                enemy_width, enemy_height, bullet_width, bullet_height)) {
                status = 2;
            }
            else if (!Colision::CheckEnemyInside(
                enemys[i].x_enemy - enemys[i].speed_enemy * delta_x * deltaTimeSeconds,
                enemys[i].y_enemy - enemys[i].speed_enemy * delta_y * deltaTimeSeconds,
                enemy_width, enemy_height)) {
                enemys[i].x_enemy -= enemys[i].speed_enemy * delta_x * deltaTimeSeconds;
                enemys[i].y_enemy -= enemys[i].speed_enemy * delta_y * deltaTimeSeconds;
            }
        }
        if (enemys[i].x_enemy == x_player && enemys[i].y_enemy > y_player) {
            if (Colision::CheckEnemyHitPlayer(x_player, y_player, x_left_arm,
                y_left_arm, x_right_arm, y_right_arm, x_backpack, y_backpack,
                enemys[i].x_enemy,
                enemys[i].y_enemy - enemys[i].speed_enemy * deltaTimeSeconds,
                enemy_width, enemy_height, body_radius, arm_radius,
                backpack_radius, radians)) {
                status = 1;
            }
            else if (Colision::CheckBulletHitEnemy(bullets, enemys[i].x_enemy,
                enemys[i].y_enemy - enemys[i].speed_enemy * deltaTimeSeconds,
                enemy_width, enemy_height, bullet_width, bullet_height)) {
                status = 2;
            }
            else if (!Colision::CheckEnemyInside(enemys[i].x_enemy,
                enemys[i].y_enemy - enemys[i].speed_enemy * deltaTimeSeconds,
                enemy_width, enemy_height)) {
                enemys[i].y_enemy -= enemys[i].speed_enemy * deltaTimeSeconds;
            }
        }
        if (enemys[i].x_enemy == x_player && enemys[i].y_enemy < y_player) {
            if (Colision::CheckEnemyHitPlayer(x_player, y_player, x_left_arm,
                y_left_arm, x_right_arm, y_right_arm, x_backpack, y_backpack,
                enemys[i].x_enemy,
                enemys[i].y_enemy + enemys[i].speed_enemy * deltaTimeSeconds,
                enemy_width, enemy_height, body_radius, arm_radius,
                backpack_radius, radians)) {
                status = 1;
            }
            else if (Colision::CheckBulletHitEnemy(bullets, enemys[i].x_enemy,
                enemys[i].y_enemy + enemys[i].speed_enemy * deltaTimeSeconds,
                enemy_width, enemy_height, bullet_width, bullet_height)) {
                status = 2;
            }
            else if (!Colision::CheckEnemyInside(enemys[i].x_enemy,
                enemys[i].y_enemy + enemys[i].speed_enemy * deltaTimeSeconds,
                enemy_width, enemy_height)) {
                enemys[i].y_enemy += enemys[i].speed_enemy * deltaTimeSeconds;
            }
        }
        if (enemys[i].x_enemy > x_player && enemys[i].y_enemy == y_player) {
            if (Colision::CheckEnemyHitPlayer(x_player, y_player, x_left_arm,
                y_left_arm, x_right_arm, y_right_arm, x_backpack, y_backpack,
                enemys[i].x_enemy - enemys[i].speed_enemy * deltaTimeSeconds,
                enemys[i].y_enemy,
                enemy_width, enemy_height, body_radius, arm_radius,
                backpack_radius, radians)) {
                status = 1;
            }
            else if (Colision::CheckBulletHitEnemy(bullets,
                enemys[i].x_enemy - enemys[i].speed_enemy * deltaTimeSeconds,
                enemys[i].y_enemy, enemy_width, enemy_height, bullet_width,
                bullet_height)) {
                status = 2;
            }
            else if (!Colision::CheckEnemyInside(
                enemys[i].x_enemy - enemys[i].speed_enemy * deltaTimeSeconds,
                enemys[i].y_enemy, enemy_width, enemy_height)) {
                enemys[i].x_enemy -= enemys[i].speed_enemy * deltaTimeSeconds;
            }
        }
        if (enemys[i].x_enemy < x_player && enemys[i].y_enemy == y_player) {
            if (Colision::CheckEnemyHitPlayer(x_player, y_player, x_left_arm,
                y_left_arm, x_right_arm, y_right_arm, x_backpack, y_backpack,
                enemys[i].x_enemy + enemys[i].speed_enemy * deltaTimeSeconds,
                enemys[i].y_enemy,
                enemy_width, enemy_height, body_radius, arm_radius,
                backpack_radius, radians)) {
                status = 1;
            }
            else if (Colision::CheckBulletHitEnemy(bullets,
                enemys[i].x_enemy + enemys[i].speed_enemy * deltaTimeSeconds,
                enemys[i].y_enemy, enemy_width, enemy_height, bullet_width,
                bullet_height)) {
                status = 2;
            }
            else if (!Colision::CheckEnemyInside(
                enemys[i].x_enemy + enemys[i].speed_enemy * deltaTimeSeconds,
                enemys[i].y_enemy, enemy_width, enemy_height)) {
                enemys[i].x_enemy += enemys[i].speed_enemy * deltaTimeSeconds;
            }
        }

        if (status == 1) {
            if (health_bar_scale_width > 0) {
                health_bar_scale_width -= 0.01;
            }
            else {
                game_over = 1;
            }
            enemys.erase(enemys.begin() + i);
            --i;
        }
        else if (status == 2) {
            if (score < 1) {
                score += 0.01;
            }
            enemys.erase(enemys.begin() + i);
            --i;
        }
    }
}

float Enemy::Look_Arm( float x_enemy, float y_enemy, float x_player, float y_player)
{
    return -atan2(x_player - x_enemy, y_player - y_enemy) - M_PI;
}

float Enemy::Look_Body(float x_enemy, float y_enemy, float x_player, float y_player)
{
    return  -atan2(x_player - x_enemy, y_player - y_enemy) + M_PI;
}

bool Enemy::check_overlap_enemy(float  enemy_spawn_x,
    float enemy_spawn_y, std::vector< m1::Tema1::Enemy_Struct>& enemys) {

    bool return_status = false;
    if (enemys.size() != 0) {
        for (int i = 0; i < enemys.size(); i++) {
            if (enemy_spawn_x < enemys[i].x_enemy + 0.6
                && enemy_spawn_x + 0.6 > enemys[i].x_enemy
                && enemy_spawn_y < enemys[i].y_enemy + 0.6
                && enemy_spawn_y + 0.6 > enemys[i].y_enemy) {
                return_status = true;
            }
        }
    }

    return return_status;
}