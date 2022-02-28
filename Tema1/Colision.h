#pragma once

#include <string>
#include <unordered_map>

#include "core/gpu/mesh.h"
#include "utils/glm_utils.h"
#include <lab_m1/Tema1/Tema1.h>


namespace Colision
{
	bool CircleRectColisionOutside(
		float cx,
		float cy,
		float radius,
		float rx,
		float ry,
		float rw, 
		float rh);

	bool CheckPlayerInsideGame(
		float x_player,
		float y_player,
		float x_left_arm,
		float y_left_arm,
		float x_right_arm,
		float y_right_arm,
		float x_backpack,
		float y_backpack,
		float map_width,
		float map_height,
		float body_radius,
		float arm_radius,
		float backpack_radius,
		float radians);

	bool CheckBulletInsideGame(
		float x_bullet,
		float y_bullet,
		float bullet_width,
		float bullet_height);

	std::pair<float, float> GetPointsAfterRotaion(
		float x_player,
		float y_player,
		float x_object, 
		float y_object,
		float radians);
	
	bool CheckPlayerHitObject(
		float x_player,
		float y_player,
		float x_left_arm,
		float y_left_arm,
		float x_right_arm,
		float y_right_arm,
		float x_backpack,
		float y_backpack,
		float map_width,
		float map_height,
		float body_radius,
		float arm_radius,
		float backpack_radius,
		float radians,
		std::vector<m1::Tema1::Obstacle_Struct> obstacles);

	bool CheckBulletHitObject(
		float x_bullet,
		float y_bullet,
		float bullet_width,
		float bullet_height,
		std::vector<m1::Tema1::Obstacle_Struct> obstacles);

	bool CheckEnemyHitPlayer(
		float x_player,
		float y_player,
		float x_left_arm,
		float y_left_arm,
		float x_right_arm,
		float y_right_arm,
		float x_backpack,
		float y_backpack,
		float x_enemy,
		float y_enemy,
		float enemy_width,
		float enemy_height,
		float body_radius,
		float arm_radius,
		float backpack_radius,
		float radians );

	bool CheckBulletHitEnemy(
		std::vector<m1::Tema1::Bullet_Struct>& bullets,
		float x_enemy,
		float y_enemy,
		float enemy_width,
		float enemy_height,
		float bullet_width,
		float bullet_height);

	bool CheckEnemyInside(
		float x_enemy, 
		float y_enemy, 
		float enemy_width,
		float enemy_height);
	
}