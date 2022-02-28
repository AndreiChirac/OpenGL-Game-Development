#pragma once

#include <string>
#include <unordered_map>
#include "core/gpu/mesh.h"
#include "utils/glm_utils.h"
#include "core/engine.h"
#include "utils/gl_utils.h"
#include <lab_m1/Tema1/Obstacle.h>
#include <chrono>
#include <lab_m1/Tema1/Tema1_object2D.h>
#include <iostream>
#include <lab_m1/Tema1/Colision.h>
#include <lab_m1/Tema1/Tema1.h>

namespace Enemy
{
    void CreateEnemy(
        std::vector<m1::Tema1::Enemy_Struct>& enemys,
        int nr_of_enemies,
        int map_x,
        int map_y);

    void Move_Enemy(
        std::vector<m1::Tema1::Enemy_Struct>& enemys,
        std::vector<m1::Tema1::Bullet_Struct>& bullets,
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
        float& score,
        float& health_bar_scale_width,
        float deltaTimeSeconds,
        int& game_over);

    float Look_Arm(
        float width,
        float height,
        float x_player,
        float y_player);

    float Look_Body(
        float width,
        float height,
        float x_player,
        float y_player);

    bool check_overlap_enemy(
        float enemy_spawn_x, 
        float enemy_spawn_y,
        std::vector<m1::Tema1::Enemy_Struct>& enemys);

}