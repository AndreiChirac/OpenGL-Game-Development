#pragma once

#include <string>
#include <unordered_map>

#include "core/gpu/mesh.h"
#include "utils/glm_utils.h"
#include <lab_m1/Tema1/Tema1.h>


namespace Obstacle
{

    void CreateObstacles(
        std::vector< m1::Tema1::Obstacle_Struct >& obstacles,
        int nr_obstacles,
        int map_x,
        int map_y);

    bool check_overlap_obstacle(
        float  obstacle_spawn_x,
        float obstacle_spawn_y,
        float length_scale,
        float height_scale,
        std::vector< m1::Tema1::Obstacle_Struct >obstacles);
}
