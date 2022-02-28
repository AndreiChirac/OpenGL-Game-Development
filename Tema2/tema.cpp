#include "lab_m1/Tema2/tema.h"

#include <iostream>

using namespace std;
using namespace m1;


/*
 *  To find out more about `FrameStart`, `Update`, `FrameEnd`
 *  and the order in which they are called, see `world.cpp`.
 */


Tema2::Tema2()
{
}


Tema2::~Tema2()
{
}


void Tema2::Init()
{
    floor_length = 15 * 2  + 1;
    floor_width = 15 * 2 + 1;

    player = new Player(meshes);
    floor = new Floor(floor_length, floor_width, meshes);
    maze = new Maze(meshes);
    colision = new Colision();
    enemy_gen = new Enemy();
    maze->Create_Maze(floor->maze_floor, floor_length, floor_width, rand() % floor_length, rand() % floor_width);
    
    spawn = maze->Find_Best_Spawn(floor->maze_floor, floor_length, floor_width);
    floor->maze_floor[spawn.x][spawn.z].status = 3;
    spawn.x += 0.5;
    spawn.z += 0.5;

    enemys = enemy_gen->Create_Enemy(floor->maze_floor, floor_length, floor_width);

    x_reper = spawn.x;
    y_reper = spawn.z;

    right = 5;
    left = 0;
    bottom = 0;
    top = 10;

    fov = 60;
    Z_FAR = 200;
    Z_NEAR = 0.01;

    scale_time = 60 * 2;
    time = 60 * 2;
    time_factor = 5;
    scale_health = 4.94;
    prev_time = 0;

    rotation_angle = 0;

    {
        Mesh* mesh = new Mesh("projectile");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "sphere.obj");
        meshes[mesh->GetMeshID()] = mesh;

        mesh = new Mesh("x");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "box.obj");
        meshes[mesh->GetMeshID()] = mesh;
       
    }

    camera_view = true;
    camera = new implemented::Camera_Tema();
    camera_aux = new implemented::Camera_Tema();
    camera_aux->Set(glm::vec3(0 - 0.2, 0, 0 - 0.2),
        glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));

    x_offset = camera->distanceToTarget * sin(rotation_angle + 0);
    z_offset = camera->distanceToTarget * cos(rotation_angle + 0);

    camera->Set(glm::vec3(spawn.x - x_offset, 2, spawn.z - z_offset),
        glm::vec3(spawn.x, 2, spawn.z), glm::vec3(0, 1, 0));

    projectionMatrix = glm::perspective(RADIANS(fov), window->props.aspectRatio, Z_NEAR, Z_FAR);

    {
        Shader* shader = new Shader("TemaShader");
        shader->AddShader(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "Tema2", "shaders", "VertexShader.glsl"), GL_VERTEX_SHADER);
        shader->AddShader(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "Tema2", "shaders", "FragmentShader.glsl"), GL_FRAGMENT_SHADER);
        shader->CreateAndLink();
        shaders[shader->GetName()] = shader;

        shader = new Shader("Boom_Shader");
        shader->AddShader(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "Tema2", "shaders", "VertexShader_Enemy.glsl"), GL_VERTEX_SHADER);
        shader->AddShader(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "Tema2", "shaders", "FragmentShader_Enemy.glsl"), GL_FRAGMENT_SHADER);
        shader->CreateAndLink();
        shaders[shader->GetName()] = shader;
    }
    
    start = std::chrono::system_clock::now();
    end = std::chrono::system_clock::now();

}

void Tema2::FrameStart()
{
    // Clears the color buffer (using the previously set color) and depth buffer
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::ivec2 resolution = window->GetResolution();
    // Sets the screen area where to draw
    glViewport(0, 0, resolution.x, resolution.y);
}

void Tema2::SetViewportArea(const ViewportSpace& viewSpace, glm::vec3 colorColor, bool clear)
{

    glViewport(viewSpace.x, viewSpace.y, viewSpace.width, viewSpace.height);

    glEnable(GL_SCISSOR_TEST);
    glScissor(viewSpace.x, viewSpace.y, viewSpace.width, viewSpace.height);

    // Clears the color buffer (using the previously set color) and depth buffer
    glClearColor(colorColor.r, colorColor.g, colorColor.b, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glDisable(GL_SCISSOR_TEST);

    projectionMatrix = glm::ortho(left, right, bottom, top, Z_NEAR, Z_FAR);
    camera_mode = 1;
}



void Tema2::Update(float deltaTimeSeconds)
{
    if (spawn.x > 0 && spawn.x < floor_length && spawn.z > 0 && spawn.z < floor_length) {
        if (scale_time > 0 && scale_health > 0) {
            projectionMatrix = glm::perspective(RADIANS(fov), window->props.aspectRatio, Z_NEAR, Z_FAR);
            camera_mode = 0;
            glm::mat4 modelMatrix;

            end = std::chrono::system_clock::now();
            cout <<"Au trecut " << (std::chrono::duration_cast<std::chrono::seconds>(end - start).count()) << " secunde" << endl;
            if ((std::chrono::duration_cast<std::chrono::seconds>(end - start).count()) <= time) {
                if (prev_time != (std::chrono::duration_cast<std::chrono::seconds>(end - start).count())) {
                    scale_time--;
                    prev_time = (std::chrono::duration_cast<std::chrono::seconds>(end - start).count());
                }
            }

            for (int i = 0; i < floor_length; i++) {
                for (int j = 0; j < floor_width; j++) {
                    modelMatrix = glm::mat4(1);

                    if (floor->maze_floor[i][j].status == 0 ||
                        floor->maze_floor[i][j].status == 2 ||
                        floor->maze_floor[i][j].status == 3) {
                        modelMatrix = glm::translate(modelMatrix, glm::vec3(0.5 + floor->maze_floor[i][j].x, floor->maze_floor[i][j].y, 0.5 + floor->maze_floor[i][j].z));
                        modelMatrix = glm::scale(modelMatrix, glm::vec3(0.5, 1, 0.5));
                        RenderMesh(meshes[floor->floor_type.c_str()], shaders["VertexNormal"], modelMatrix);
                    }
                    else {
                        modelMatrix = glm::translate(modelMatrix, glm::vec3(0.5 + floor->maze_floor[i][j].x, 1 + floor->maze_floor[i][j].y, 0.5 + floor->maze_floor[i][j].z));
                        modelMatrix = glm::scale(modelMatrix, glm::vec3(0.5, 1, 0.5));
                        RenderMesh(meshes[maze->maze_wall.c_str()], shaders["VertexNormal"], modelMatrix);
                    }

                }
            }
            if (projectiles.size() != 0)
                colision->Find_Projectile_Wall_Ground_Colision(projectiles);

            for (int i = 0; i < projectiles.size(); i++) {

                projectiles[i]->curr_pos.x += projectiles[i]->speed * deltaTimeSeconds * projectiles[i]->forward[0];
                projectiles[i]->curr_pos.y += projectiles[i]->speed * deltaTimeSeconds * projectiles[i]->forward[1];
                projectiles[i]->curr_pos.z += projectiles[i]->speed * deltaTimeSeconds * projectiles[i]->forward[2];

                if (distance(projectiles[i]->curr_pos.x, projectiles[i]->curr_pos.y, projectiles[i]->curr_pos.z,
                    projectiles[i]->spawn.x, projectiles[i]->spawn.y, projectiles[i]->spawn.z) >= projectiles[i]->ttl) {

                    projectiles.erase(projectiles.begin() + i);
                    --i;
                }
            }

            for (int i = 0; i < projectiles.size(); i++) {
                modelMatrix = glm::mat4(1);
                modelMatrix = glm::translate(modelMatrix, glm::vec3(projectiles[i]->curr_pos.x, projectiles[i]->curr_pos.y, projectiles[i]->curr_pos.z));
                modelMatrix = glm::scale(modelMatrix, glm::vec3(0.1));
                RenderMeshColor(meshes["projectile"], shaders["TemaShader"], modelMatrix, glm::vec3(1, 0, 0));

            }

            enemy_gen->Move_Enemy(enemys, deltaTimeSeconds, 0.6);
            for (int i = 0; i < enemys.size(); i++) {

                if (enemys.size() != 0 && projectiles.size() != 0 && !enemys[i]->status) {
                    enemys[i]->status = colision->Find_Enemy_Projectile_Colision_One(enemys[i], projectiles);
                    if (enemys[i]->status)
                        enemys[i]->animation_start = std::chrono::system_clock::now();
                    enemys[i]->animation_end = std::chrono::system_clock::now();
                }

                modelMatrix = glm::mat4(1);
                modelMatrix = glm::translate(modelMatrix, glm::vec3(enemys[i]->spawn.x, 0.3, enemys[i]->spawn.z));
                modelMatrix = glm::scale(modelMatrix, glm::vec3(0.6));
                if (!enemys[i]->status) {
                    RenderMeshColor(meshes["projectile"], shaders["TemaShader"], modelMatrix, glm::vec3(1, 0.55, 0.55));
                }
                enemys[i]->map_object["sphere_1"] = make_tuple(0, 0.6, 0.3);


                modelMatrix = glm::mat4(1);
                modelMatrix = glm::translate(modelMatrix, glm::vec3(enemys[i]->spawn.x, 0.6 + 0.3, enemys[i]->spawn.z));
                modelMatrix = glm::scale(modelMatrix, glm::vec3(0.6));
                if (!enemys[i]->status) {
                    RenderMeshColor(meshes["x"], shaders["TemaShader"], modelMatrix, glm::vec3(0, 0.55, 0.55));
                }
                enemys[i]->map_object["box"] = make_tuple(0.6, 1.2, 0.3);

                modelMatrix = glm::mat4(1);
                modelMatrix = glm::translate(modelMatrix, glm::vec3(enemys[i]->spawn.x, 0.6 + 0.6 + 0.3, enemys[i]->spawn.z));
                modelMatrix = glm::scale(modelMatrix, glm::vec3(0.6));
                if (!enemys[i]->status) {
                    RenderMeshColor(meshes["projectile"], shaders["TemaShader"], modelMatrix, glm::vec3(1, 0.55, 0.55));
                }
                enemys[i]->map_object["sphere_2"] = make_tuple(1.2, 1.8, 0.3);

                if (enemys[i]->status) {
                    modelMatrix = glm::mat4(1);
                    modelMatrix = glm::translate(modelMatrix, glm::vec3(enemys[i]->spawn.x, 0.6 + 0.3, enemys[i]->spawn.z));
                    modelMatrix = glm::scale(modelMatrix, glm::vec3(1));
                    RenderMeshColor(meshes["projectile"], shaders["Boom_Shader"], modelMatrix, glm::vec3(0, 0, 0));
                }
                enemys[i]->animation_end = std::chrono::system_clock::now();

                if (enemys[i]->status && (std::chrono::duration_cast<std::chrono::milliseconds>(enemys[i]->animation_end - enemys[i]->animation_start).count()) > 500) {
                    enemys.erase(enemys.begin() + i);
                    --i;
                }
            }

            if (colision->Find_Enemy_Player_Colision()) {
                scale_health = scale_health - 0.005;
            }

            if (camera_view) {
                Render_Player(player);
            }
            glm::ivec2 resolution = window->GetResolution();
            SetViewportArea(ViewportSpace(0, 0, resolution.x / 5, resolution.y / 16 - 10), glm::vec3(0), true);
            modelMatrix = camera_aux->GetViewMatrix();
            modelMatrix = glm::translate(modelMatrix, glm::vec3(0, 5, -2.7));
            modelMatrix = glm::scale(modelMatrix, glm::vec3(0, 8.885, scale_health));
            meshes["x"]->SetDrawMode(GL_TRIANGLES);
            RenderMeshColor(meshes["x"], shaders["TemaShader"], modelMatrix, glm::vec3(0, 0.7568, 0.596));

            modelMatrix = camera_aux->GetViewMatrix();
            modelMatrix = glm::translate(modelMatrix, glm::vec3(0, 5, -2.7));
            modelMatrix = glm::scale(modelMatrix, glm::vec3(0, 8.885, 4.94));
            meshes["x"]->SetDrawMode(GL_TRIANGLES);
            RenderMeshColor(meshes["x"], shaders["TemaShader"], modelMatrix, glm::vec3(0.811, 0.949, 0.922));

            modelMatrix = camera_aux->GetViewMatrix();
            modelMatrix = glm::translate(modelMatrix, glm::vec3(0, 5, -2.7));
            modelMatrix = glm::scale(modelMatrix, glm::vec3(0, 8.885, 4.94));
            meshes["x"]->SetDrawMode(GL_LINES);
            RenderMeshColor(meshes["x"], shaders["TemaShader"], modelMatrix, glm::vec3(0.003, 0.0745, 0.0588));


            meshes["x"]->SetDrawMode(GL_TRIANGLES);

            SetViewportArea(ViewportSpace(resolution.x - resolution.x / 5, 0, resolution.x / 5, resolution.y / 16 - 10), glm::vec3(0), true);
            cout << "Au mai ramas " << scale_time << " secunde" << endl;
            modelMatrix = camera_aux->GetViewMatrix();
            modelMatrix = glm::translate(modelMatrix, glm::vec3(0, 5, -2.7));
            modelMatrix = glm::scale(modelMatrix, glm::vec3(0, 8.885, (time_factor * scale_time) / time));
            meshes["x"]->SetDrawMode(GL_TRIANGLES);
            RenderMeshColor(meshes["x"], shaders["TemaShader"], modelMatrix, glm::vec3(0.25, 0.082, 0.1137));

            modelMatrix = camera_aux->GetViewMatrix();
            modelMatrix = glm::translate(modelMatrix, glm::vec3(0, 5, -2.7));
            modelMatrix = glm::scale(modelMatrix, glm::vec3(0, 8.885, 4.94));
            meshes["x"]->SetDrawMode(GL_TRIANGLES);
            RenderMeshColor(meshes["x"], shaders["TemaShader"], modelMatrix, glm::vec3(0.9686, 0.8549, 0.8745));

            modelMatrix = camera_aux->GetViewMatrix();
            modelMatrix = glm::translate(modelMatrix, glm::vec3(0, 5, -2.7));
            modelMatrix = glm::scale(modelMatrix, glm::vec3(0, 8.885, 4.94));
            meshes["x"]->SetDrawMode(GL_LINES);
            RenderMeshColor(meshes["x"], shaders["TemaShader"], modelMatrix, glm::vec3(0.847, 0.2862, 0.388));

            meshes["x"]->SetDrawMode(GL_TRIANGLES);
        }
        else {
            cout << "GAME OVER \n";
        }
    } else {
        cout << "YOU WON \n";
    }
}


void Tema2::FrameEnd()
{
    //DrawCoordinateSystem(camera->GetViewMatrix(), projectionMatrix);
}

void Tema2::RenderMesh(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix)
{
    if (!mesh || !shader || !shader->program)
        return;

    // Render an object using the specified shader and the specified position
    shader->Use();
    glUniformMatrix4fv(shader->loc_view_matrix, 1, GL_FALSE, glm::value_ptr(camera->GetViewMatrix()));
    glUniformMatrix4fv(shader->loc_projection_matrix, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
    glUniformMatrix4fv(shader->loc_model_matrix, 1, GL_FALSE, glm::value_ptr(modelMatrix));

    mesh->Render();
}

void Tema2::RenderMeshColor(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix, glm::vec3& color)
{
    if (!mesh || !shader || !shader->GetProgramID())
        return;
    // Render an object using the specified shader and the specified position
    glUseProgram(shader->program);

    int loc_object_color = glGetUniformLocation(shader->program, "object_color");
    glUniform3fv(loc_object_color, 1, glm::value_ptr(color));

    // TODO(student): Get shader location for uniform mat4 "Model"
    int model = glGetUniformLocation(shader->program, "Model");

    // TODO(student): Set shader uniform "Model" to modelMatrix
    glUniformMatrix4fv(model, 1, GL_FALSE, glm::value_ptr(modelMatrix));

    // TODO(student): Get shader location for uniform mat4 "View"
    int view_location = glGetUniformLocation(shader->program, "View");

    // TODO(student): Set shader uniform "View" to viewMatrix
    glm::mat4 viewMatrix;
    if (camera_mode == 0) {
        viewMatrix = camera->GetViewMatrix();
    }  else {
        viewMatrix = camera_aux->GetViewMatrix();
    }
    glUniformMatrix4fv(view_location, 1, GL_FALSE, glm::value_ptr(viewMatrix));

    // TODO(student): Get shader location for uniform mat4 "Projection"
    int projection_location = glGetUniformLocation(shader->program, "Projection");

    // TODO(student): Set shader uniform "Projection" to projectionMatrix
    glUniformMatrix4fv(projection_location, 1, GL_FALSE, glm::value_ptr(projectionMatrix));

    // Draw the object
    glBindVertexArray(mesh->GetBuffers()->m_VAO);
    glDrawElements(mesh->GetDrawMode(), static_cast<int>(mesh->indices.size()), GL_UNSIGNED_INT, 0);
}

/*
 *  These are callback functions. To find more about callbacks and
 *  how they behave, see `input_controller.h`.
 */


void Tema2::OnInputUpdate(float deltaTime, int mods)
{

    float cameraSpeed = 2.0f;

    // move the Camera_Tema only if MOUSE_RIGHT button is pressed
    

    if (window->KeyHold(GLFW_KEY_W)) {
        // TODO(student): Translate the camera forward
        camera->MoveForward(cameraSpeed * deltaTime);
        colision->Set_Colision(floor->maze_floor, enemys, camera->GetTargetPosition().x, camera->GetTargetPosition().z, floor_width, floor_length);
        if (colision->Find_Wall_Player_Colision() || colision->Find_Enemy_Player_Colision()) {
            camera->MoveForward(-cameraSpeed * deltaTime);
        }
    }

    if (window->KeyHold(GLFW_KEY_A)) {
        // TODO(student): Translate the camera to the leftd
        camera->TranslateRight(cameraSpeed * (-deltaTime));
        colision->Set_Colision(floor->maze_floor, enemys, camera->GetTargetPosition().x, camera->GetTargetPosition().z, floor_width, floor_length);
        if (colision->Find_Wall_Player_Colision() || colision->Find_Enemy_Player_Colision()) {
            camera->TranslateRight(cameraSpeed * (+deltaTime));
        }
    }

    if (window->KeyHold(GLFW_KEY_S)) {
        // TODO(student): Translate the camera backward
        camera->MoveForward(cameraSpeed * (-deltaTime));
        colision->Set_Colision(floor->maze_floor, enemys, camera->GetTargetPosition().x, camera->GetTargetPosition().z, floor_width, floor_length);
        if (colision->Find_Wall_Player_Colision() || colision->Find_Enemy_Player_Colision()) {
            camera->MoveForward(cameraSpeed * (+deltaTime));
        }
    }

    if (window->KeyHold(GLFW_KEY_D)) {
        // TODO(student): Translate the camera to the right
        camera->TranslateRight(cameraSpeed * deltaTime);
        colision->Set_Colision(floor->maze_floor, enemys, camera->GetTargetPosition().x, camera->GetTargetPosition().z, floor_width, floor_length);
        if (colision->Find_Wall_Player_Colision() || colision->Find_Enemy_Player_Colision()) {
            camera->TranslateRight(cameraSpeed * (-deltaTime));
        }
    }

    spawn.x = camera->GetTargetPosition().x;
    spawn.z = camera->GetTargetPosition().z;
}


void Tema2::OnKeyPress(int key, int mods)
{
    

}


void Tema2::OnKeyRelease(int key, int mods)
{
    if (key == GLFW_KEY_LEFT_CONTROL)
    {
        if (!camera_view) {
            // conver to third person
            camera_view = true;
            camera->distanceToTarget = 2.5;
            x_offset = camera->distanceToTarget * sin(rotation_angle + 0);
            z_offset = camera->distanceToTarget * cos(rotation_angle + 0);
            camera->Set(glm::vec3(spawn.x - x_offset, 2, spawn.z - z_offset),
                glm::vec3(spawn.x, 2, spawn.z), glm::vec3(0, 1, 0));

        } else {
            // convert to first person
            camera->distanceToTarget = 0.01;
            x_offset = camera->distanceToTarget * sin(rotation_angle + 0);
            z_offset = camera->distanceToTarget * cos(rotation_angle + 0);
            camera_view = false;
            camera->Set(glm::vec3(spawn.x - x_offset, 0.9, spawn.z - z_offset),
                glm::vec3(spawn.x, 0.9, spawn.z), glm::vec3(0, 1, 0));
        }
    }
}


void Tema2::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{

    if (window->MouseHold(GLFW_MOUSE_BUTTON_RIGHT))
    {
        float sensivityOX = 0.001f;
        float sensivityOY = 0.001f;

        rotation_angle -= sensivityOY * deltaX;

        if (!camera_view) {

            camera->RotateFirstPerson_OX(-sensivityOX * deltaY);
            camera->RotateFirstPerson_OY(-sensivityOY * deltaX);

        }

        if (camera_view) {

            camera->RotateThirdPerson_OX(-sensivityOX * deltaY);
            camera->RotateThirdPerson_OY(-sensivityOY * deltaX);
        }
    }
}


void Tema2::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
 
    if (IS_BIT_SET(button, GLFW_MOUSE_BUTTON_LEFT) && !camera_view) {
        projectiles.push_back(new Projectile(camera->GetTargetPosition().x, camera->GetTargetPosition().y, camera->GetTargetPosition().z, 4, camera->forward));
    }

}


void Tema2::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button release event
}


void Tema2::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}


void Tema2::OnWindowResize(int width, int height)
{
}

void Tema2::Render_Player(Player *player) {
   
    glm::mat4 modelMatrix = glm::mat4(1);
    modelMatrix = glm::translate(modelMatrix, glm::vec3(camera->GetTargetPosition().x, 0.95, camera->GetTargetPosition().z));
    modelMatrix = glm::rotate(modelMatrix, rotation_angle, glm::vec3(0, 1, 0));
    modelMatrix = glm::scale(modelMatrix, glm::vec3(0.1, 0.1, 0.1f));
    RenderMesh(meshes[player->head.c_str()], shaders["VertexNormal"], modelMatrix);
   
    modelMatrix = glm::mat4(1);
    modelMatrix = glm::translate(modelMatrix, glm::vec3(camera->GetTargetPosition().x, 0.45, camera->GetTargetPosition().z));
    modelMatrix = glm::rotate(modelMatrix, rotation_angle, glm::vec3(0, 1, 0));
    modelMatrix = glm::translate(modelMatrix, glm::vec3(-0.2, 0, 0));
    modelMatrix = glm::scale(modelMatrix, glm::vec3(0.05f, 0.05, 0.1f));
    RenderMesh(meshes[player->left_arm.c_str()], shaders["VertexNormal"], modelMatrix);

    modelMatrix = glm::mat4(1);
    modelMatrix = glm::translate(modelMatrix, glm::vec3(camera->GetTargetPosition().x, 0.45, camera->GetTargetPosition().z));
    modelMatrix = glm::rotate(modelMatrix, rotation_angle, glm::vec3(0, 1, 0));
    modelMatrix = glm::translate(modelMatrix, glm::vec3(0.2, 0, 0));
    modelMatrix = glm::scale(modelMatrix, glm::vec3(0.05f, 0.05, 0.1f));
    RenderMesh(meshes[player->right_arm.c_str()], shaders["VertexNormal"], modelMatrix);

    modelMatrix = glm::mat4(1);
    modelMatrix = glm::translate(modelMatrix, glm::vec3(camera->GetTargetPosition().x, 0.65, camera->GetTargetPosition().z));
    modelMatrix = glm::rotate(modelMatrix, rotation_angle, glm::vec3(0, 1, 0));
    modelMatrix = glm::translate(modelMatrix, glm::vec3(-0.2, 0, 0));
    modelMatrix = glm::scale(modelMatrix, glm::vec3(0.05f, 0.15, 0.1f));
    RenderMesh(meshes[player->left_upper_arm.c_str()], shaders["VertexNormal"], modelMatrix);

    modelMatrix = glm::mat4(1);
    modelMatrix = glm::translate(modelMatrix, glm::vec3(camera->GetTargetPosition().x, 0.65, camera->GetTargetPosition().z));
    modelMatrix = glm::rotate(modelMatrix, rotation_angle, glm::vec3(0, 1, 0));
    modelMatrix = glm::translate(modelMatrix, glm::vec3(+0.2, 0, 0));
    modelMatrix = glm::scale(modelMatrix, glm::vec3(0.05f, 0.15, 0.1f));
    RenderMesh(meshes[player->right_upper_arm.c_str()], shaders["VertexNormal"], modelMatrix);

    modelMatrix = glm::mat4(1);
    modelMatrix = glm::translate(modelMatrix, glm::vec3(camera->GetTargetPosition().x, 0.55, camera->GetTargetPosition().z));
    modelMatrix = glm::rotate(modelMatrix, rotation_angle, glm::vec3(0, 1, 0));
    modelMatrix = glm::scale(modelMatrix, glm::vec3(0.15f, 0.25, 0.1f));
    RenderMesh(meshes[player->body.c_str()], shaders["VertexNormal"], modelMatrix);

    modelMatrix = glm::mat4(1);
    modelMatrix = glm::translate(modelMatrix, glm::vec3(camera->GetTargetPosition().x, 0.15, camera->GetTargetPosition().z));
    modelMatrix = glm::rotate(modelMatrix, rotation_angle, glm::vec3(0, 1, 0));
    modelMatrix = glm::translate(modelMatrix, glm::vec3(-0.07, 0, 0));
    modelMatrix = glm::scale(modelMatrix, glm::vec3(0.05f, 0.15, 0.1f));
    RenderMesh(meshes[player->left_leg.c_str()], shaders["VertexNormal"], modelMatrix);


    modelMatrix = glm::mat4(1);
    modelMatrix = glm::translate(modelMatrix, glm::vec3(camera->GetTargetPosition().x , 0.15, camera->GetTargetPosition().z));
    modelMatrix = glm::rotate(modelMatrix, rotation_angle, glm::vec3(0, 1, 0));
    modelMatrix = glm::translate(modelMatrix, glm::vec3(0.07, 0, 0));
    modelMatrix = glm::scale(modelMatrix, glm::vec3(0.05f, 0.15, 0.1f));
    RenderMesh(meshes[player->right_leg.c_str()], shaders["VertexNormal"], modelMatrix);
}