#pragma once

#include <chrono>
#include "components/simple_scene.h"


namespace m1
{
    class Tema1 : public gfxc::SimpleScene
    {
     public:
        struct ViewportSpace
        {
            ViewportSpace() : x(0), y(0), width(1), height(1) {}
            ViewportSpace(int x, int y, int width, int height)
                : x(x), y(y), width(width), height(height) {}
            int x;
            int y;
            int width;
            int height;
        };

        struct LogicSpace
        {
            LogicSpace() : x(0), y(0), width(1), height(1) {}
            LogicSpace(float x, float y, float width, float height)
                : x(x), y(y), width(width), height(height) {}
            float x;
            float y;
            float width;
            float height;
        };

        struct Enemy_Struct_Mesh
        {
            Mesh* left_arm;
            Mesh* right_arm;
            Mesh* body;
        };

        struct Enemy_Struct
        {
            float x_enemy;
            float y_enemy;
            float x_enemy_initial;
            float y_enemy_initial;
            float speed_enemy;
        };

        struct Bullet_Struct
        {
            float x_pos;
            float y_pos;
            float x_click_pos;
            float y_click_pos;
            float radians_shooting_moment;
            float initial_x_pos;
            float initial_y_pos;
            float distance_traveled;
            std::string dial;
        };

        struct Obstacle_Struct
        {
            float x_obstacles;
            float y_obstacles;
            std::pair <float, float> random_scale;
        };

     public:
         Tema1();
        ~Tema1();

        void Init() override;

     private:
        void FrameStart() override;
        void Update(float deltaTimeSeconds) override;
        void FrameEnd() override;

        void DrawScene(glm::mat3 visMatrix);

        void OnInputUpdate(float deltaTime, int mods) override;
        void OnKeyPress(int key, int mods) override;
        void OnKeyRelease(int key, int mods) override;
        void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
        void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;

        // Sets the logic space and view space
        // logicSpace: { x, y, width, height }
        // viewSpace: { x, y, width, height }
        glm::mat3 VisualizationTransf2D(const LogicSpace &logicSpace, const ViewportSpace &viewSpace);
        glm::mat3 VisualizationTransf2DUnif(const LogicSpace &logicSpace, const ViewportSpace &viewSpace);

        void SetViewportArea(const ViewportSpace &viewSpace, glm::vec3 colorColor = glm::vec3(0), bool clear = true);

     protected:
        float length;
        ViewportSpace viewSpace;
        LogicSpace logicSpace;
        glm::mat3 modelMatrix, visMatrix;

        float translate_x;
        float translate_y;
        float scale_x = 0;
        float scale_y = 0;
        float radians;
        float prev_radians;

        float map_x;
        float map_y;

        float x_player;
        float y_player;

        float bullet_speed;

        int nr_obstacles;
        std::unordered_map<std::string, Mesh*> obstacle_meshes;
        std::unordered_map<std::string, Mesh*> enemy_meshes_render;
        
        std::chrono::steady_clock::time_point curr_time;
        std::chrono::steady_clock::time_point prev_time;

        std::vector< float > x_random_pos_enemy;
        std::vector< float > y_random_pos_enemy;
        std::vector< float > random_speed_enemy;

        int nr_of_enemies;
        float enemy_spawn_x;
        float enemy_spawn_y;
        float spawn_time;

        std::vector< Enemy_Struct_Mesh> enemy_meshes;
        std::vector< Enemy_Struct> enemys;
        std::vector< Bullet_Struct > bullets;
        std::vector< Obstacle_Struct > obstacles;


        std::chrono::steady_clock::time_point curr_time_bullet;
        std::chrono::steady_clock::time_point prev_time_bullet;
        float fire_rate;
        float max_distance;

        float bullet_width;
        float bullet_height;

        float body_radius;
        float arm_radius;
        float backpack_radius;


        float x_left_arm;
        float y_left_arm;

        float x_right_arm;
        float y_right_arm;

        float x_backpack;
        float y_backpack;


        float x_eye_bulb_left_displacement;
        float y_eye_bulb_left_displacement;
        float x_eye_bulb_right_displacement;
        float y_eye_bulb_right_displacement;

        float x_eye_left_displacement;
        float y_eye_left_displacement;
        float x_eye_right_displacement;
        float y_eye_right_displacement;

        float x_left_arm_displacement;
        float y_left_arm_displacement;
        float x_right_arm_displacement;
        float y_right_arm_displacement;

        float enemy_width;
        float enemy_height;
        float enemy_arm_width;
        float enemy_arm_height;

        float health_bar_width;
        float health_bar_height;

        float health_bar_scale_width;
        float health_bar_scale_height;
        
        float score;

        int game_over;
    };
}   // namespace m1
