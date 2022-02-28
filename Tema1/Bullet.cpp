#include "Bullet.h"
#include <lab_m1/Tema1/Colision.h>
#include <iostream>

float  Bullet::distance(float x1, float y1, float x2, float y2) {
    return sqrt(pow(x2 - x1, 2) +
        pow(y2 - y1, 2) * 1.0);
}

void Bullet::Move_Bullet(
	std::vector< m1::Tema1::Bullet_Struct > &bullets,
    std::vector< m1::Tema1::Obstacle_Struct > obstacles,
    float bullet_speed,
    float deltaTimeSeconds,
    float max_distance,
    float x_player,
    float y_player,
    float bullet_width,
    float bullet_height) {
    bool status = false;
    if (bullets.size() != 0) {
        for (int i = 0; i < bullets.size(); i++) {
            status = false;

            float delta_x = abs(bullets[i].x_click_pos - bullets[i].initial_x_pos);
            float delta_y = abs(bullets[i].y_click_pos - bullets[i].initial_y_pos);

            if (strcmp(bullets[i].dial.c_str(), "first") == 0) {
                if (Colision::CheckBulletHitObject(
                    bullets[i].x_pos + bullet_speed * delta_x * deltaTimeSeconds,
                    bullets[i].y_pos + bullet_speed * delta_y * deltaTimeSeconds,
                    bullet_width, bullet_height, obstacles) ||
                    Colision::CheckBulletInsideGame(
                    bullets[i].x_pos + bullet_speed * delta_x * deltaTimeSeconds,
                    bullets[i].y_pos + bullet_speed * delta_y * deltaTimeSeconds,
                    bullet_width, bullet_height) ) {
                    status = true;
                } else {
                    bullets[i].x_pos += bullet_speed * delta_x * deltaTimeSeconds;
                    bullets[i].y_pos += bullet_speed * delta_y * deltaTimeSeconds;
                }
            }
            if (strcmp(bullets[i].dial.c_str(), "second") == 0) {
                if (Colision::CheckBulletHitObject(
                    bullets[i].x_pos + bullet_speed * delta_x * deltaTimeSeconds,
                    bullets[i].y_pos - bullet_speed * delta_y * deltaTimeSeconds,
                    bullet_width, bullet_height, obstacles) ||
                    Colision::CheckBulletInsideGame(
                    bullets[i].x_pos + bullet_speed * delta_x * deltaTimeSeconds,
                    bullets[i].y_pos - bullet_speed * delta_y * deltaTimeSeconds,
                    bullet_width, bullet_height)) {
                    status = true;
                }
                else {
                    bullets[i].x_pos += bullet_speed * delta_x * deltaTimeSeconds;
                    bullets[i].y_pos -= bullet_speed * delta_y * deltaTimeSeconds;
                }
            }
            if (strcmp(bullets[i].dial.c_str(), "third") == 0) {
                if (Colision::CheckBulletHitObject(
                    bullets[i].x_pos - bullet_speed * delta_x * deltaTimeSeconds,
                    bullets[i].y_pos + bullet_speed * delta_y * deltaTimeSeconds,
                    bullet_width, bullet_height, obstacles) ||
                    Colision::CheckBulletInsideGame(
                    bullets[i].x_pos - bullet_speed * delta_x * deltaTimeSeconds,
                    bullets[i].y_pos + bullet_speed * delta_y * deltaTimeSeconds,
                    bullet_width, bullet_height)) {
                    status = true;
                }
                else {
                    bullets[i].x_pos -= bullet_speed * delta_x * deltaTimeSeconds;
                    bullets[i].y_pos += bullet_speed * delta_y * deltaTimeSeconds;
                }
            }
            if (strcmp(bullets[i].dial.c_str(), "forth") == 0) {
                if (Colision::CheckBulletHitObject(
                    bullets[i].x_pos - bullet_speed * delta_x * deltaTimeSeconds,
                    bullets[i].y_pos - bullet_speed * delta_y * deltaTimeSeconds,
                    bullet_width, bullet_height, obstacles) ||
                    Colision::CheckBulletInsideGame(
                    bullets[i].x_pos - bullet_speed * delta_x * deltaTimeSeconds,
                    bullets[i].y_pos - bullet_speed * delta_y * deltaTimeSeconds,
                    bullet_width, bullet_height)) {
                    status = true;
                }
                else {
                    bullets[i].x_pos -= bullet_speed * delta_x * deltaTimeSeconds;
                    bullets[i].y_pos -= bullet_speed * delta_y * deltaTimeSeconds;
                }
            }
            if (distance(bullets[i].x_pos, bullets[i].y_pos,
                bullets[i].initial_x_pos, bullets[i].initial_y_pos) >= max_distance || status) {
                bullets.erase(bullets.begin() + i);
                --i;
            }
        }
    }
}

m1::Tema1::Bullet_Struct Bullet::Create_Bullet(
    WindowObject* window,
    m1::Tema1::ViewportSpace viewSpace,
    m1::Tema1::LogicSpace logicSpace,
    int mouseX,
    int mouseY, 
    float translate_x,
    float translate_y) {

    glm::ivec2 resolution = window->GetResolution();

    float sx, sy, tx, ty, smin;
    sx = viewSpace.width / logicSpace.width;
    sy = viewSpace.height / logicSpace.height;
    if (sx < sy)
        smin = sx;
    else
        smin = sy;
    tx = viewSpace.x - smin * logicSpace.x + (viewSpace.width - smin * logicSpace.width) / 2;
    ty = viewSpace.y - smin * logicSpace.y + (viewSpace.height - smin * logicSpace.height) / 2;

    float xf = (mouseX - tx) / smin;
    float yf = ((resolution.y - mouseY) - ty) / smin;


    m1::Tema1::Bullet_Struct bullet;
    bullet.x_click_pos = xf;
    bullet.y_click_pos = yf;
    bullet.x_pos = 2 + translate_x;
    bullet.y_pos = 2 + translate_y;
    bullet.initial_x_pos = 2 + translate_x;
    bullet.initial_y_pos = 2 + translate_y;
    bullet.radians_shooting_moment = -atan2(viewSpace.width / 2 - mouseX,
                                            viewSpace.height / 2 - (resolution.y - mouseY)) - M_PI;

    if (bullet.x_pos < bullet.x_click_pos && bullet.y_pos < bullet.y_click_pos) {
        bullet.dial = "first";
    }
    if (bullet.x_pos < bullet.x_click_pos && bullet.y_pos > bullet.y_click_pos) {
        bullet.dial = "second";
    }
    if (bullet.x_pos > bullet.x_click_pos && bullet.y_pos < bullet.y_click_pos) {
        bullet.dial = "third";
    }
    if (bullet.x_pos > bullet.x_click_pos && bullet.y_pos > bullet.y_click_pos) {
        bullet.dial = "forth";
    }

    return bullet;
}