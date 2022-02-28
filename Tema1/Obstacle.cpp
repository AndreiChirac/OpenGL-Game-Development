#include "Obstacle.h"

#include <vector>

#include "core/engine.h"
#include "utils/gl_utils.h"
#include <unordered_map>
#include <lab_m1/Tema1/Tema1_object2D.h>
#include <lab_m1/Tema1/transform2D.h>
#include <iostream>

void Obstacle::CreateObstacles(
    std::vector< m1::Tema1::Obstacle_Struct > &obstacles,
    int nr_obstacles,
    int map_x,
    int map_y) {

    double legth_scale;
    double height_scale;
    double x_rand_obstacle;
    double y_rand_obstacle;

    for (int i = 0; i < nr_obstacles; i++) {

        legth_scale = (double(rand()) / double((RAND_MAX)) * 1) + 0.2;

        x_rand_obstacle = (double(rand()) / double((RAND_MAX)) * map_x);
        y_rand_obstacle = (double(rand()) / double((RAND_MAX)) * map_y);

        height_scale = (double(rand()) / double(((double)RAND_MAX) * 2)) + 0.2;
            
        while (check_overlap_obstacle(
            x_rand_obstacle, y_rand_obstacle, legth_scale, height_scale, obstacles) ||
            (1.7 < x_rand_obstacle && x_rand_obstacle < 2.6) ||
            (1.7 < y_rand_obstacle && y_rand_obstacle < 2.6) ||
            (1.7 < x_rand_obstacle + 1 * legth_scale &&
                x_rand_obstacle + 1 * legth_scale < 2.6) ||
            (1.7 < y_rand_obstacle + 1 * height_scale &&
                y_rand_obstacle + 1 * height_scale < 2.6) ||
            (0.0 > x_rand_obstacle + 1 * legth_scale) ||
            (x_rand_obstacle + 1 * legth_scale > 4.0) ||
            (0.0 > y_rand_obstacle + 1 * height_scale) ||
            (y_rand_obstacle + 1 * height_scale > 4.0)) {

            x_rand_obstacle = (double(rand()) / float((RAND_MAX)) * map_x);
            y_rand_obstacle = (double(rand()) / float((RAND_MAX)) * map_y);
        }

        m1::Tema1::Obstacle_Struct obstacle;
        obstacle.x_obstacles = x_rand_obstacle;
        obstacle.y_obstacles = y_rand_obstacle;
        obstacle.random_scale = std::make_pair(legth_scale, height_scale);
        obstacles.push_back(obstacle);
    }
}

bool Obstacle::check_overlap_obstacle(
    float  obstacle_spawn_x,
    float obstacle_spawn_y,
    float length_scale, 
    float height_scale, 
    std::vector< m1::Tema1::Obstacle_Struct > obstacles) {

    bool return_status = false;
    if (obstacles.size() != 0) {
        for (int i = 0; i < obstacles.size(); i++) {
            if (obstacle_spawn_x <
                (double)obstacles[i].x_obstacles + 1 * (double)obstacles[i].random_scale.first + 0.2
                && (double)obstacle_spawn_x + 1 * (double)length_scale + 0.2 >
                (double)obstacles[i].x_obstacles
                && obstacle_spawn_y < 
                (double)obstacles[i].y_obstacles + 1 * (double)obstacles[i].random_scale.second + 0.2
                && (double)obstacle_spawn_y + 1 * (double)height_scale + 0.2 >
                (double)obstacles[i].y_obstacles) {
                return_status = true;
            }
        }
    }
    return return_status;
}
