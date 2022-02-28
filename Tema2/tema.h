#pragma once

#include "components/simple_scene.h"
#include "lab_m1/Tema2/tema_camera.h"
#include "lab_m1/Tema2/player.h"
#include "lab_m1/Tema2/floor.h"
#include "lab_m1/Tema2/maze.h"
#include "lab_m1/Tema2/colisions.h"
#include "lab_m1/Tema2/transform3D_tema.h"
#include <time.h>
#include <vector>
#include <string>
#include <chrono>

namespace m1
{
    class Tema2 : public gfxc::SimpleScene
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

        Tema2();
        ~Tema2();

        void Init() override;

     private:
        void FrameStart() override;
        void Update(float deltaTimeSeconds) override;
        void FrameEnd() override;

        void RenderMesh(Mesh *mesh, Shader *shader, const glm::mat4 &modelMatrix) override;
        void RenderMeshColor(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix, glm::vec3& color);

        void OnInputUpdate(float deltaTime, int mods) override;
        void OnKeyPress(int key, int mods) override;
        void OnKeyRelease(int key, int mods) override;
        void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
        void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
        void OnWindowResize(int width, int height) override;

        void Render_Player(Player * player);
        void SetViewportArea(const ViewportSpace& viewSpace, glm::vec3 colorColor = glm::vec3(0), bool clear = true);
     protected:
        implemented::Camera_Tema *camera;
        implemented::Camera_Tema *camera_aux;

        glm::mat4 projectionMatrix;
        
        bool camera_view;


        float right;
        float left;
        float bottom;
        float top;
        float fov;
        float Z_FAR;
        float Z_NEAR;

        // TODO(student): If you need any other class variables, define them here.

        Player *player;
        Floor *floor;
        Maze* maze;
        Point spawn;
        Colision* colision;
        Enemy* enemy_gen;
        std::vector<Projectile*> projectiles;
        std::vector<Enemy*> enemys;

        int floor_width;
        int floor_length;

        float x_reper;
        float y_reper;

        float rotation_angle;
        float x_offset;
        float z_offset;

        int empty_space;
        int enemy_nr;

        float health_bar_width;
        float health_bar_height;

        float health_bar_scale_width;
        float health_bar_scale_height;

        std::chrono::time_point<std::chrono::system_clock> start;
        std::chrono::time_point<std::chrono::system_clock> end;

        int camera_mode;
        float scale_time;
        float scale_health;

        int prev_time;
        int time;
        int time_factor;
    };
}   // namespace m1
