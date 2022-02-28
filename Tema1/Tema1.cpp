#include "lab_m1/Tema1/Tema1.h"

#include <vector>
#include <iostream>
#include <stdlib.h>
#include <chrono>
#include <time.h>
#include "lab_m1/Tema1/transform2D.h"
#include "lab_m1/Tema1/Tema1_object2D.h"
#include "lab_m1/Tema1/Obstacle.h"
#include "lab_m1/Tema1/Enemy.h"
#include <lab_m1/Tema1/Colision.h>
#include <lab_m1/Tema1/Bullet.h>

using namespace std;
using namespace m1;

Tema1::Tema1()
{
}


Tema1::~Tema1()
{
}

void Tema1::Init()
{
    auto camera = GetSceneCamera();
    camera->SetPosition(glm::vec3(0, 0, 50));
    camera->SetRotation(glm::vec3(0, 0, 0));
    camera->Update();
    GetCameraInput()->SetActive(false);
    srand(time(NULL));

    logicSpace.x = 1;       // logic x
    logicSpace.y = 1;       // logic y
    logicSpace.width = 2;   // logic width
    logicSpace.height = 2;  // logic height

    translate_x = 0;
    translate_y = 0;

    scale_x = 1;
    scale_y = 1;

    map_x = 4.0;
    map_y = 4.0;

    bullet_speed = 1;
    max_distance = 3;

    bullet_width = 0.1;
    bullet_height = 0.1;

    body_radius = 0.2;
    arm_radius = 0.07;
    backpack_radius = 0.2;

    x_eye_bulb_left_displacement = 0.06;
    y_eye_bulb_left_displacement = -0.02;
    x_eye_bulb_right_displacement = -0.06;
    y_eye_bulb_right_displacement = -0.02;

    x_eye_left_displacement = 0.06;
    y_eye_left_displacement = -0.05;
    x_eye_right_displacement = -0.06;
    y_eye_right_displacement = -0.05;

    x_left_arm_displacement = 0.125;
    y_left_arm_displacement = 0.15;
    x_right_arm_displacement = -0.125;
    y_right_arm_displacement = 0.15;

    enemy_width = 0.4;
    enemy_height = 0.4;
    enemy_arm_width = 0.2;
    enemy_arm_height = 0.2;

    health_bar_width = 1.2;
    health_bar_height = 0.2;
    health_bar_scale_width = 1;

    x_player = 2;
    y_player = 2;
    x_left_arm = 2 + x_left_arm_displacement;
    y_left_arm = 2 + y_left_arm_displacement;
    x_right_arm = 2 + x_right_arm_displacement;
    y_right_arm = 2 + y_right_arm_displacement;
    x_backpack = 2;
    y_backpack = 2 - body_radius;

    score = 0;
    game_over = 0;

    Mesh* body = 
        Tema1_object2D::CreateCircle("body", body_radius, glm::vec3(0.996, 0.843, 0.717));
    Mesh* eye_left = 
        Tema1_object2D::CreateCircle("eye_left", 0.06f, glm::vec3(1, 1, 1));
    Mesh* eye_bulb_left = 
        Tema1_object2D::CreateCircle("eye_bulb_left", 0.03f, glm::vec3(0, 0, 0));
    Mesh* eye_right =
        Tema1_object2D::CreateCircle("eye_right", 0.06f, glm::vec3(1, 1, 1));
    Mesh* eye_bulb_right = 
        Tema1_object2D::CreateCircle("eye_bulb_right", 0.03f, glm::vec3(0, 0, 0));
    Mesh* mouth = 
        Tema1_object2D::CreateMouth("mouth", 0.085f, glm::vec3(1, 1, 1));
    Mesh* arm_left = 
        Tema1_object2D::CreateCircle("arm_left", arm_radius, glm::vec3(1, 1, 1));
    Mesh* arm_right = 
        Tema1_object2D::CreateCircle("arm_right", arm_radius, glm::vec3(1, 1, 1));
    Mesh* backpack = 
        Tema1_object2D::CreateCircle("backpack", backpack_radius, glm::vec3(0.517, 0.4549, 0.6078));
    Mesh* map = 
        Tema1_object2D::CreateMap("map", map_x, map_y, glm::vec3(0.574, 0.88, 0.888));
    
    Mesh* bullet = Tema1_object2D::CreateRectangle(
        "bullet", glm::vec3(0, 0, 0), bullet_width, bullet_height, glm::vec3(0, 0, 0));
    
    Mesh* health_bar_contur 
        = Tema1_object2D::CreateRectangleContur(
        "health_bar_contur", glm::vec3(0, 0, 0), health_bar_width - 0.0025,
        health_bar_height - 0.0025, glm::vec3(0.003, 0.0745, 0.0588));
    Mesh* health_bar_inside 
        = Tema1_object2D::CreateRectangle("health_bar_inside",
        glm::vec3(0, 0, 0), health_bar_width , health_bar_height, glm::vec3(0.811, 0.949, 0.922));
    Mesh* health_bar 
        = Tema1_object2D::CreateRectangle("health_bar",
        glm::vec3(0, 0, 0), health_bar_width, health_bar_height, glm::vec3(0, 0.7568, 0.596));

    Mesh* score_bar_contur =
        Tema1_object2D::CreateRectangleContur("score_bar_contur",
            glm::vec3(0, 0, 0), health_bar_width - 0.0025,
            health_bar_height - 0.0025, glm::vec3(0.25, 0.082, 0.1137));
    Mesh* score_bar_inside =
        Tema1_object2D::CreateRectangle("score_bar_inside",
            glm::vec3(0, 0, 0), health_bar_width, health_bar_height,
            glm::vec3(0.9686, 0.8549, 0.8745));
    Mesh* score_bar =
        Tema1_object2D::CreateRectangle("score_bar", glm::vec3(0, 0, 0),
            health_bar_width, health_bar_height, glm::vec3(0.847, 0.2862, 0.388));

    nr_obstacles = rand() % 5 + 5;

    obstacle_meshes["obstacle"] =
        Tema1_object2D::CreateRectangle("obstacle",
            glm::vec3(0, 0, 0), 1, 1, glm::vec3(0.95, 0.462, 0.419));
    Obstacle::CreateObstacles(obstacles, nr_obstacles, map_x, map_y);

    Mesh* enemy_left_arm =
        Tema1_object2D::CreateRectangle("1", glm::vec3(-0.1f, -0.05, 0),
            0.2, 0.2, glm::vec3(0.1137, 0.2235, 0.2705));
    enemy_meshes_render[enemy_left_arm->GetMeshID()] = enemy_left_arm;
    Mesh* enemy_right_arm =
        Tema1_object2D::CreateRectangle("2", glm::vec3(+0.3f, -0.05, 0),
            0.2, 0.2, glm::vec3(0.1137, 0.2235, 0.2705));
    enemy_meshes_render[enemy_right_arm->GetMeshID()] = enemy_right_arm;
    Mesh* enemy_body = 
        Tema1_object2D::CreateRectangle("3", glm::vec3(0, 0, 0),
            0.4, 0.4, glm::vec3(0.207, 0.447, 0.521));
    enemy_meshes_render[enemy_body->GetMeshID()] = enemy_body;

    nr_of_enemies = (rand() % 4) + 1;
    spawn_time = (float(rand()) / float((RAND_MAX)) * nr_of_enemies);
    fire_rate = (float(rand()) / float((RAND_MAX)));

    curr_time = std::chrono::steady_clock::now();
    curr_time_bullet = std::chrono::steady_clock::now();

    AddMeshToList(body);
    AddMeshToList(eye_left);
    AddMeshToList(eye_bulb_left);
    AddMeshToList(eye_right);
    AddMeshToList(eye_bulb_right);
    AddMeshToList(mouth);
    AddMeshToList(arm_left);
    AddMeshToList(arm_right);
    AddMeshToList(backpack);
    AddMeshToList(bullet);
    AddMeshToList(map);
    AddMeshToList(health_bar_contur);
    AddMeshToList(health_bar_inside);
    AddMeshToList(health_bar);
    AddMeshToList(score_bar_contur);
    AddMeshToList(score_bar_inside);
    AddMeshToList(score_bar);
}


// 2D visualization matrix
glm::mat3 Tema1::VisualizationTransf2D(const LogicSpace & logicSpace,
    const ViewportSpace & viewSpace)
{
    float sx, sy, tx, ty;
    sx = viewSpace.width / logicSpace.width;
    sy = viewSpace.height / logicSpace.height;
    tx = viewSpace.x - sx * logicSpace.x;
    ty = viewSpace.y - sy * logicSpace.y;

    return glm::transpose(glm::mat3(
        sx, 0.0f, tx,
        0.0f, sy, ty,
        0.0f, 0.0f, 1.0f));
}


// Uniform 2D visualization matrix (same scale factor on x and y axes)
glm::mat3 Tema1::VisualizationTransf2DUnif(const LogicSpace & logicSpace,
    const ViewportSpace & viewSpace)
{
    float sx, sy, tx, ty, smin;
    sx = viewSpace.width / logicSpace.width;
    sy = viewSpace.height / logicSpace.height;
    if (sx < sy)
        smin = sx;
    else
        smin = sy;
    tx = viewSpace.x - smin * logicSpace.x + (viewSpace.width - smin * logicSpace.width) / 2;
    ty = viewSpace.y - smin * logicSpace.y + (viewSpace.height - smin * logicSpace.height) / 2;

    return glm::transpose(glm::mat3(
        smin, 0.0f, tx,
        0.0f, smin, ty,
        0.0f, 0.0f, 1.0f));
}


void Tema1::SetViewportArea(const ViewportSpace & viewSpace, glm::vec3 colorColor, bool clear)
{

    glViewport(viewSpace.x, viewSpace.y, viewSpace.width, viewSpace.height);

    glEnable(GL_SCISSOR_TEST);
    glScissor(viewSpace.x, viewSpace.y, viewSpace.width, viewSpace.height);

    // Clears the color buffer (using the previously set color) and depth buffer
    glClearColor(colorColor.r, colorColor.g, colorColor.b, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glDisable(GL_SCISSOR_TEST);

    GetSceneCamera()->SetOrthographic((float)viewSpace.x, (float)(viewSpace.x + viewSpace.width),
        (float)viewSpace.y, (float)(viewSpace.y + viewSpace.height), 0.1f, 400);
    GetSceneCamera()->Update();
}


void Tema1::FrameStart()
{
    // Clears the color buffer (using the previously set color) and depth buffer
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}


void Tema1::Update(float deltaTimeSeconds)
{
    glm::ivec2 resolution = window->GetResolution();

    viewSpace = ViewportSpace(0, 0, resolution.x, resolution.y);
    SetViewportArea(viewSpace, glm::vec3(0), true);

    visMatrix = glm::mat3(1);
    visMatrix *= VisualizationTransf2DUnif(logicSpace, viewSpace);
    if (game_over == 0) {
        Enemy::Move_Enemy(enemys, bullets, x_player, y_player, x_left_arm,
            y_left_arm, x_right_arm, y_right_arm, x_backpack, y_backpack,
            body_radius, arm_radius, backpack_radius, radians, enemy_width,
            enemy_height, bullet_width, bullet_height, score, health_bar_scale_width,
            deltaTimeSeconds, game_over);
        Bullet::Move_Bullet(bullets, obstacles, bullet_speed, deltaTimeSeconds,
            max_distance, x_player, y_player, bullet_width, bullet_height);


        DrawScene(visMatrix);

        visMatrix = glm::mat3(1);
        LogicSpace logic_space = LogicSpace(0, 0, health_bar_width, health_bar_height);
        ViewportSpace view_space = ViewportSpace(resolution.x - 380,
            resolution.y - 70, 310 * health_bar_width, 310 * health_bar_height);
        SetViewportArea(view_space, glm::vec3(0), true);
        visMatrix *= VisualizationTransf2DUnif(logic_space, view_space);

        modelMatrix = visMatrix;
        modelMatrix *= transform2D::Translate(0.0025, 0.0025);
        RenderMesh2D(meshes["health_bar_contur"], shaders["VertexColor"], modelMatrix);

        modelMatrix = visMatrix;
        modelMatrix *= transform2D::Scale(health_bar_scale_width, 1);
        RenderMesh2D(meshes["health_bar"], shaders["VertexColor"], modelMatrix);

        modelMatrix = visMatrix;
        RenderMesh2D(meshes["health_bar_inside"], shaders["VertexColor"], modelMatrix);

        visMatrix = glm::mat3(1);

        LogicSpace logic_space_2 = LogicSpace(0, 0, health_bar_width, health_bar_height);
        ViewportSpace view_space_2 = ViewportSpace(25, resolution.y - 70,
            310 * health_bar_width, 310 * health_bar_height);
        SetViewportArea(view_space_2, glm::vec3(0), true);
        visMatrix *= VisualizationTransf2DUnif(logic_space_2, view_space_2);

        modelMatrix = visMatrix;
        modelMatrix *= transform2D::Translate(0.0025, 0.0025);
        RenderMesh2D(meshes["score_bar_contur"], shaders["VertexColor"], modelMatrix);

        modelMatrix = visMatrix;
        modelMatrix *= transform2D::Scale(score, 1);
        RenderMesh2D(meshes["score_bar"], shaders["VertexColor"], modelMatrix);

        modelMatrix = visMatrix;
        RenderMesh2D(meshes["score_bar_inside"], shaders["VertexColor"], modelMatrix);
    }
    else {
        std::cout << "Game Over!" << std::endl;
    }
}


void Tema1::FrameEnd()
{
}


void Tema1::DrawScene(glm::mat3 visMatrix)
{
   
    if (!Colision::CheckPlayerInsideGame(
        x_player,
        y_player,
        x_left_arm,
        y_left_arm,
        x_right_arm,
        y_right_arm,
        x_backpack,
        y_backpack,
        map_x,
        map_y,
        body_radius,
        arm_radius,
        backpack_radius,
        radians) &&
        (!Colision::CheckPlayerHitObject(
        x_player,
        y_player,
        x_left_arm,
        y_left_arm,
        x_right_arm,
        y_right_arm,
        x_backpack,
        y_backpack,
        map_x,
        map_y,
        body_radius,
        arm_radius,
        backpack_radius,
        radians,
        obstacles))) {

        modelMatrix = visMatrix * transform2D::Translate(2, 2);
        modelMatrix *= transform2D::Translate(translate_x, translate_y);
        modelMatrix *= transform2D::Rotate(radians);
        modelMatrix *= transform2D::Translate(x_eye_bulb_left_displacement, y_eye_bulb_left_displacement);
        RenderMesh2D(meshes["eye_bulb_left"], shaders["VertexColor"], modelMatrix);

        modelMatrix = visMatrix * transform2D::Translate(2, 2);
        modelMatrix *= transform2D::Translate(translate_x, translate_y);
        modelMatrix *= transform2D::Rotate(radians);
        modelMatrix *= transform2D::Translate(x_eye_bulb_right_displacement, y_eye_bulb_right_displacement);
        RenderMesh2D(meshes["eye_bulb_right"], shaders["VertexColor"], modelMatrix);

        modelMatrix = visMatrix * transform2D::Translate(2, 2);
        modelMatrix *= transform2D::Translate(translate_x, translate_y);
        modelMatrix *= transform2D::Rotate(radians);
        modelMatrix *= transform2D::Translate(x_eye_left_displacement, y_eye_left_displacement);
        RenderMesh2D(meshes["eye_left"], shaders["VertexColor"], modelMatrix);

        modelMatrix = visMatrix * transform2D::Translate(2, 2);
        modelMatrix *= transform2D::Translate(translate_x, translate_y);
        modelMatrix *= transform2D::Rotate(radians);
        modelMatrix *= transform2D::Translate(x_eye_right_displacement, y_eye_right_displacement);
        RenderMesh2D(meshes["eye_right"], shaders["VertexColor"], modelMatrix);

        modelMatrix = visMatrix * transform2D::Translate(2, 2);
        modelMatrix *= transform2D::Translate(translate_x, translate_y);
        modelMatrix *= transform2D::Rotate(radians);
        modelMatrix *= transform2D::Translate(-0.0425, 0.05);
        RenderMesh2D(meshes["mouth"], shaders["VertexColor"], modelMatrix);


        modelMatrix = visMatrix * transform2D::Translate(2, 2);
        modelMatrix *= transform2D::Translate(translate_x, translate_y);
        modelMatrix *= transform2D::Rotate(radians);
        modelMatrix *= transform2D::Translate(x_left_arm_displacement, y_left_arm_displacement);
        RenderMesh2D(meshes["arm_left"], shaders["VertexColor"], modelMatrix);


        modelMatrix = visMatrix * transform2D::Translate(2, 2);
        modelMatrix *= transform2D::Translate(translate_x, translate_y);
        modelMatrix *= transform2D::Rotate(radians);
        modelMatrix *= transform2D::Translate(x_right_arm_displacement, y_right_arm_displacement);
        RenderMesh2D(meshes["arm_right"], shaders["VertexColor"], modelMatrix);



        modelMatrix = visMatrix * transform2D::Translate(2, 2);
        modelMatrix *= transform2D::Translate(translate_x, translate_y);
        modelMatrix *= transform2D::Rotate(radians);
        RenderMesh2D(meshes["body"], shaders["VertexColor"], modelMatrix);

        modelMatrix = visMatrix * transform2D::Translate(2, 2);
        modelMatrix *= transform2D::Translate(translate_x, translate_y);
        modelMatrix *= transform2D::Rotate(radians);
        modelMatrix *= transform2D::Translate(0, -body_radius);
        RenderMesh2D(meshes["backpack"], shaders["VertexColor"], modelMatrix);
        prev_radians = radians;
    }
    else {
        modelMatrix = visMatrix * transform2D::Translate(2, 2);
        modelMatrix *= transform2D::Translate(translate_x, translate_y);
        modelMatrix *= transform2D::Rotate(prev_radians);
        modelMatrix *= transform2D::Translate(x_eye_bulb_left_displacement, y_eye_bulb_left_displacement);
        RenderMesh2D(meshes["eye_bulb_left"], shaders["VertexColor"], modelMatrix);

        modelMatrix = visMatrix * transform2D::Translate(2, 2);
        modelMatrix *= transform2D::Translate(translate_x, translate_y);
        modelMatrix *= transform2D::Rotate(prev_radians);
        modelMatrix *= transform2D::Translate(x_eye_bulb_right_displacement, y_eye_bulb_right_displacement);
        RenderMesh2D(meshes["eye_bulb_right"], shaders["VertexColor"], modelMatrix);

        modelMatrix = visMatrix * transform2D::Translate(2, 2);
        modelMatrix *= transform2D::Translate(translate_x, translate_y);
        modelMatrix *= transform2D::Rotate(prev_radians);
        modelMatrix *= transform2D::Translate(x_eye_left_displacement, y_eye_left_displacement);
        RenderMesh2D(meshes["eye_left"], shaders["VertexColor"], modelMatrix);

        modelMatrix = visMatrix * transform2D::Translate(2, 2);
        modelMatrix *= transform2D::Translate(translate_x, translate_y);
        modelMatrix *= transform2D::Rotate(prev_radians);
        modelMatrix *= transform2D::Translate(x_eye_right_displacement, y_eye_right_displacement);
        RenderMesh2D(meshes["eye_right"], shaders["VertexColor"], modelMatrix);

        modelMatrix = visMatrix * transform2D::Translate(2, 2);
        modelMatrix *= transform2D::Translate(translate_x, translate_y);
        modelMatrix *= transform2D::Rotate(prev_radians);
        modelMatrix *= transform2D::Translate(-0.0425, 0.05);
        RenderMesh2D(meshes["mouth"], shaders["VertexColor"], modelMatrix);


        modelMatrix = visMatrix * transform2D::Translate(2, 2);
        modelMatrix *= transform2D::Translate(translate_x, translate_y);
        modelMatrix *= transform2D::Rotate(prev_radians);
        modelMatrix *= transform2D::Translate(x_left_arm_displacement, y_left_arm_displacement);
        RenderMesh2D(meshes["arm_left"], shaders["VertexColor"], modelMatrix);


        modelMatrix = visMatrix * transform2D::Translate(2, 2);
        modelMatrix *= transform2D::Translate(translate_x, translate_y);
        modelMatrix *= transform2D::Rotate(prev_radians);
        modelMatrix *= transform2D::Translate(x_right_arm_displacement, y_right_arm_displacement);
        RenderMesh2D(meshes["arm_right"], shaders["VertexColor"], modelMatrix);



        modelMatrix = visMatrix * transform2D::Translate(2, 2);
        modelMatrix *= transform2D::Translate(translate_x, translate_y);
        modelMatrix *= transform2D::Rotate(prev_radians);
        RenderMesh2D(meshes["body"], shaders["VertexColor"], modelMatrix);

        modelMatrix = visMatrix * transform2D::Translate(2, 2);
        modelMatrix *= transform2D::Translate(translate_x, translate_y);
        modelMatrix *= transform2D::Rotate(prev_radians);
        modelMatrix *= transform2D::Translate(0, -body_radius);
        RenderMesh2D(meshes["backpack"], shaders["VertexColor"], modelMatrix);
    }

    if (bullets.size() != 0) {
        for (int i = 0; i < bullets.size(); i++) {
            modelMatrix = visMatrix * transform2D::Translate(bullets[i].x_pos, bullets[i].y_pos);
            modelMatrix *= transform2D::Rotate(bullets[i].radians_shooting_moment);
            RenderMesh2D(meshes["bullet"], shaders["VertexColor"], modelMatrix);
        }
    }
    
    prev_time = std::chrono::steady_clock::now();

    if ((std::chrono::duration_cast<std::chrono::seconds>(prev_time - curr_time).count()) > spawn_time ) {
        Enemy::CreateEnemy(enemys, nr_of_enemies, map_x, map_y);
        if (nr_of_enemies == 1) {
            spawn_time = (float(rand()) / float((RAND_MAX))) + 1;
        }
        else {
            spawn_time = (float(rand()) / float((RAND_MAX))) + 4;
        }
        nr_of_enemies = (rand() % 4) + 1;
        curr_time = std::chrono::steady_clock::now();
    }

    for (int i = 0; i < enemys.size(); i++) {
        modelMatrix = visMatrix;
        modelMatrix *= transform2D::Translate(enemys[i].x_enemy, enemys[i].y_enemy);
        modelMatrix *= transform2D::Translate(enemy_width / 2, enemy_height / 2);
        modelMatrix *= transform2D::Rotate(Enemy::Look_Arm(enemys[i].x_enemy +
            (enemy_width / 2), enemys[i].y_enemy + (enemy_height / 2), x_player, y_player));
        modelMatrix *= transform2D::Translate(-enemy_width / 2, -enemy_height / 2);
        RenderMesh2D(enemy_meshes_render["1"], shaders["VertexColor"], modelMatrix);

        modelMatrix = visMatrix;
        modelMatrix *= transform2D::Translate(enemys[i].x_enemy, enemys[i].y_enemy);
        modelMatrix *= transform2D::Translate(enemy_width / 2, enemy_height / 2);
        modelMatrix *= transform2D::Rotate(Enemy::Look_Arm(enemys[i].x_enemy +
            (enemy_width / 2), enemys[i].y_enemy + (enemy_height / 2), x_player, y_player));
        modelMatrix *= transform2D::Translate(-enemy_width / 2, -enemy_height / 2);
        RenderMesh2D(enemy_meshes_render["2"], shaders["VertexColor"], modelMatrix);

        modelMatrix = visMatrix;
        modelMatrix *= transform2D::Translate(enemys[i].x_enemy, enemys[i].y_enemy);
        modelMatrix *= transform2D::Translate(enemy_width / 2, enemy_height / 2);
        modelMatrix *= transform2D::Rotate(Enemy::Look_Body(enemys[i].x_enemy +
            (enemy_width / 2), enemys[i].y_enemy + (enemy_height / 2), x_player, y_player));
        modelMatrix *= transform2D::Translate(-enemy_width / 2, -enemy_height / 2);
        RenderMesh2D(enemy_meshes_render["3"], shaders["VertexColor"], modelMatrix);
    }

    for (int i = 0; i < obstacles.size(); i++) {
        modelMatrix = visMatrix * transform2D::Translate(obstacles[i].x_obstacles, obstacles[i].y_obstacles);
        modelMatrix *= transform2D::Scale(obstacles[i].random_scale.first, obstacles[i].random_scale.second);
        RenderMesh2D(obstacle_meshes["obstacle"], shaders["VertexColor"], modelMatrix);
    }

    modelMatrix = visMatrix;
    RenderMesh2D(meshes["map"], shaders["VertexColor"], modelMatrix);
}

/*
 *  These are callback functions. To find more about callbacks and
 *  how they behave, see `input_controller.h`.
 */

void Tema1::OnInputUpdate(float deltaTime, int mods)
{
   

    if (!Colision::CheckPlayerInsideGame(
        x_player,
        y_player + 0.5 * deltaTime,
        x_left_arm,
        y_left_arm + 0.5 * deltaTime,
        x_right_arm,
        y_right_arm + 0.5 * deltaTime,
        x_backpack,
        y_backpack + 0.5 * deltaTime,
        map_x,
        map_y,
        body_radius,
        arm_radius,
        backpack_radius,
        radians) &&
        (!Colision::CheckPlayerHitObject(
        x_player,
        y_player + 0.5 * deltaTime,
        x_left_arm,
        y_left_arm + 0.5 * deltaTime,
        x_right_arm,
        y_right_arm + 0.5 * deltaTime,
        x_backpack,
        y_backpack + 0.5 * deltaTime,
        map_x,
        map_y,
        body_radius,
        arm_radius,
        backpack_radius,
        radians,
        obstacles)) ) {

        if (window->KeyHold(GLFW_KEY_W)) {

            logicSpace.y = logicSpace.y + 0.5 * deltaTime;
            translate_y += 0.5 * deltaTime;
            y_player += 0.5 * deltaTime;
            y_left_arm += 0.5 * deltaTime;
            y_right_arm += 0.5 * deltaTime;
            y_backpack += 0.5 * deltaTime;

        }
    }

    if (!Colision::CheckPlayerInsideGame(
        x_player - 0.5 * deltaTime,
        y_player,
        x_left_arm - 0.5 * deltaTime,
        y_left_arm,
        x_right_arm - 0.5 * deltaTime,
        y_right_arm,
        x_backpack - 0.5 * deltaTime,
        y_backpack,
        map_x,
        map_y,
        body_radius,
        arm_radius,
        backpack_radius,
        radians) &&
        (!Colision::CheckPlayerHitObject(
        x_player - 0.5 * deltaTime,
        y_player,
        x_left_arm - 0.5 * deltaTime,
        y_left_arm,
        x_right_arm - 0.5 * deltaTime,
        y_right_arm,
        x_backpack - 0.5 * deltaTime,
        y_backpack,
        map_x,
        map_y,
        body_radius,
        arm_radius,
        backpack_radius,
        radians,
        obstacles))) {
            if (window->KeyHold(GLFW_KEY_A)) {

                logicSpace.x = logicSpace.x - 0.5 * deltaTime;
                translate_x -= 0.5 * deltaTime;
                x_player -= 0.5 * deltaTime;
                x_left_arm -= 0.5 * deltaTime;
                x_right_arm -= 0.5 * deltaTime;
                x_backpack -= 0.5 * deltaTime;

            }
        }
    if (!Colision::CheckPlayerInsideGame(
        x_player,
        y_player - 0.5 * deltaTime,
        x_left_arm,
        y_left_arm - 0.5 * deltaTime,
        x_right_arm,
        y_right_arm - 0.5 * deltaTime,
        x_backpack,
        y_backpack - 0.5 * deltaTime,
        map_x,
        map_y,
        body_radius,
        arm_radius,
        backpack_radius,
        radians) &&
        (!Colision::CheckPlayerHitObject(
        x_player,
        y_player - 0.5 * deltaTime,
        x_left_arm,
        y_left_arm - 0.5 * deltaTime,
        x_right_arm,
        y_right_arm - 0.5 * deltaTime,
        x_backpack,
        y_backpack - 0.5 * deltaTime,
        map_x,
        map_y,
        body_radius,
        arm_radius,
        backpack_radius,
        radians,
        obstacles))) {
        if (window->KeyHold(GLFW_KEY_S)) {

            logicSpace.y = logicSpace.y - 0.5 * deltaTime;
            translate_y -= 0.5 * deltaTime;
            y_player -= 0.5 * deltaTime;
            y_left_arm -= 0.5 * deltaTime;
            y_right_arm -= 0.5 * deltaTime;
            y_backpack -= 0.5 * deltaTime;

        }
    }

    if (!Colision::CheckPlayerInsideGame(
        x_player + 0.5 * deltaTime,
        y_player,
        x_left_arm + 0.5 * deltaTime,
        y_left_arm,
        x_right_arm + 0.5 * deltaTime,
        y_right_arm,
        x_backpack + 0.5 * deltaTime,
        y_backpack,
        map_x,
        map_y,
        body_radius,
        arm_radius,
        backpack_radius,
        radians) &&
        (!Colision::CheckPlayerHitObject(
        x_player + 0.5 * deltaTime,
        y_player,
        x_left_arm + 0.5 * deltaTime,
        y_left_arm,
        x_right_arm + 0.5 * deltaTime,
        y_right_arm,
        x_backpack + 0.5 * deltaTime,
        y_backpack,
        map_x,
        map_y,
        body_radius,
        arm_radius,
        backpack_radius,
        radians,
        obstacles))) {
        if (window->KeyHold(GLFW_KEY_D)) {

            logicSpace.x = logicSpace.x + 0.5 * deltaTime;
            translate_x += 0.5 * deltaTime;
            x_player += 0.5 * deltaTime;
            x_left_arm += 0.5 * deltaTime;
            x_right_arm += 0.5 * deltaTime;
            x_backpack += 0.5 * deltaTime;
        }
    }
    

    if (window->KeyHold(GLFW_KEY_Z)) {
        
        logicSpace.x += logicSpace.width / 2;
        logicSpace.y += logicSpace.height / 2;
       
        logicSpace.height = logicSpace.height - 0.7 * deltaTime;
        logicSpace.width = logicSpace.width - 0.7 * deltaTime;
        
        logicSpace.x -= logicSpace.width / 2;
        logicSpace.y -= logicSpace.height / 2;
    }

    if (window->KeyHold(GLFW_KEY_X)) {

        logicSpace.x += logicSpace.width / 2;
        logicSpace.y += logicSpace.height / 2;

        logicSpace.height = logicSpace.height + 0.7 * deltaTime;
        logicSpace.width = logicSpace.width + 0.7 * deltaTime;

        logicSpace.x -= logicSpace.width / 2;
        logicSpace.y -= logicSpace.height / 2;
    }


}


void Tema1::OnKeyPress(int key, int mods)
{
}


void Tema1::OnKeyRelease(int key, int mods)
{
    // Add key release event
}


void Tema1::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{

    glm::ivec2 resolution = window->GetResolution();
    radians = -atan2(viewSpace.width / 2 - mouseX, viewSpace.height / 2 - (resolution.y - mouseY)) - M_PI;

}

void Tema1::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
    prev_time_bullet = std::chrono::steady_clock::now();

    if ((std::chrono::duration_cast<std::chrono::seconds>(prev_time_bullet - curr_time_bullet).count()) >= fire_rate) {
        
        if (IS_BIT_SET(button, GLFW_MOUSE_BUTTON_LEFT)) {

            bullets.push_back(Bullet::Create_Bullet(window, viewSpace, logicSpace, mouseX, mouseY, translate_x, translate_y));
        }
        curr_time_bullet = std::chrono::steady_clock::now();
    }
    // Add mouse button press event

}

void Tema1::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button release event
}

void Tema1::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}
