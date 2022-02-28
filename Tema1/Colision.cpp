#include "Colision.h"
#include <iostream>

bool Colision::CircleRectColisionOutside(float cx, float cy, float radius, float rx, float ry, float rw, float rh) {

	// temporary variables to set edges for testing
	float testX = cx;
	float testY = cy;

	// which edge is closest?
	if (cx < rx)         testX = rx;      // test left edge
	else if (cx > rx + rw) testX = rx + rw;   // right edge
	if (cy < ry)         testY = ry;      // top edge
	else if (cy > ry + rh) testY = ry + rh;   // bottom edge

	// get distance from closest edges
	float distX = cx - testX;
	float distY = cy - testY;
	float distance = sqrt((distX * distX) + (distY * distY));

	// if the distance is less than the radius, collision!
	if (distance <= radius) {
		return true;
	}
	return false;
}

bool Colision::CheckPlayerInsideGame(
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
	float radians) {
	 
	bool return_status = false;
	
	std::pair<float, float> new_left_arm = GetPointsAfterRotaion(
		x_player, y_player, x_left_arm, y_left_arm, radians);
	std::pair<float, float> new_right_arm = GetPointsAfterRotaion(
		x_player, y_player, x_right_arm, y_right_arm, radians);
	std::pair<float, float> new_backpack = GetPointsAfterRotaion(
		x_player, y_player, x_backpack, y_backpack, radians);

	if ( x_player - body_radius < 0 ||
		y_player - body_radius < 0 || 
		x_player + body_radius > map_width ||
		y_player + body_radius > map_height||
		new_backpack.first - body_radius < 0 ||
		new_backpack.second - body_radius < 0 ||
		new_backpack.first + body_radius > map_width ||
		new_backpack.second + body_radius > map_height ||
		new_left_arm.first - arm_radius < 0 ||
		new_left_arm.second - arm_radius < 0 ||
		new_left_arm.first + arm_radius > map_width ||
		new_left_arm.second + arm_radius > map_height ||
		new_right_arm.first - arm_radius < 0 ||
		new_right_arm.second - arm_radius < 0 ||
		new_right_arm.first + arm_radius > map_width || 
		new_right_arm.second + arm_radius > map_height ) {
		return_status = true;
	}
	
	return return_status;
}

bool Colision::CheckBulletInsideGame(
	float x_bullet,
	float y_bullet,
	float bullet_width,
	float bullet_height) { 

	bool return_status = false;
	if (x_bullet - bullet_width  < 0 || y_bullet - bullet_height < 0 ||
		x_bullet + bullet_width > 4 || y_bullet + bullet_height > 4 ) {
		return_status = true;
	}

	return return_status;
}


std::pair<float, float> Colision::GetPointsAfterRotaion(
	float x_player,
	float y_player,
	float x_object,
	float y_object,
	float radians) {

	float x_object_prim;
	float y_object_prim;
	if (radians < 0) {
		x_object_prim = cos(radians) * (x_object - x_player) 
			- sin(radians) * (y_object - y_player) + x_player;
		y_object_prim = sin(radians) * (x_object - x_player) 
			+ cos(radians) * (y_object - y_player) + y_player;
	}
	else {
		x_object_prim = cos(radians) * (x_object - x_player) 
			+ sin(radians) * (y_object - y_player) + x_player;
		y_object_prim = sin(radians) * (x_object - x_player) 
			- cos(radians) * (y_object - y_player) + y_player;
	}

	return std::make_pair(x_object_prim, y_object_prim);
}


bool Colision::CheckPlayerHitObject(
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
	std::vector<m1::Tema1::Obstacle_Struct> obstacles){

	bool return_status = false;

	std::pair<float, float> new_left_arm = GetPointsAfterRotaion(x_player, y_player, x_left_arm, y_left_arm, radians);
	std::pair<float, float> new_right_arm = GetPointsAfterRotaion(x_player, y_player, x_right_arm, y_right_arm, radians);
	std::pair<float, float> new_backpack = GetPointsAfterRotaion(x_player, y_player, x_backpack, y_backpack, radians);
	for (int i = 0; i < obstacles.size(); i++)
	{
		if ((x_player - body_radius  < obstacles[i].x_obstacles + 1 * obstacles[i].random_scale.first &&
			x_player + body_radius > obstacles[i].x_obstacles) &&
			(y_player - body_radius < obstacles[i].y_obstacles + 1 * obstacles[i].random_scale.second &&
				y_player + body_radius > obstacles[i].y_obstacles) ||
			(new_left_arm.first - arm_radius  <
				obstacles[i].x_obstacles + 1 * obstacles[i].random_scale.first &&
				new_left_arm.first + arm_radius> obstacles[i].x_obstacles)&&
			(new_left_arm.second - arm_radius <
				obstacles[i].y_obstacles + 1 * obstacles[i].random_scale.second &&
				new_left_arm.second + arm_radius > obstacles[i].y_obstacles) ||
			(new_right_arm.first - arm_radius  <
				obstacles[i].x_obstacles + 1 * obstacles[i].random_scale.first &&
				new_right_arm.first + arm_radius> obstacles[i].x_obstacles) &&
			(new_right_arm.second - arm_radius <
				obstacles[i].y_obstacles + 1 * obstacles[i].random_scale.second &&
				new_right_arm.second + arm_radius > obstacles[i].y_obstacles) ||
			(new_backpack.first - backpack_radius  <
				obstacles[i].x_obstacles + 1 * obstacles[i].random_scale.first &&
				new_backpack.first + backpack_radius> obstacles[i].x_obstacles) &&
			(new_backpack.second - backpack_radius <
				obstacles[i].y_obstacles + 1 * obstacles[i].random_scale.second &&
				new_backpack.second + backpack_radius > obstacles[i].y_obstacles)) {
			return_status = true;
		}
	}
	

	return return_status;

}

bool Colision::CheckBulletHitObject(
	float x_bullet,
	float y_bullet,
	float bullet_width,
	float bullet_height,
	std::vector<m1::Tema1::Obstacle_Struct> obstacles) {

	bool return_status = false;
	

	for (int i = 0; i < obstacles.size(); i++) {
		if (x_bullet < obstacles[i].x_obstacles + 1 * (double)obstacles[i].random_scale.first &&
			x_bullet + bullet_width > obstacles[i].x_obstacles &&
			y_bullet < obstacles[i].y_obstacles + 1 * (double)obstacles[i].random_scale.second &&
			y_bullet + bullet_height > obstacles[i].y_obstacles) {

			return_status = true;
		}
	}
	
	return return_status;
}

bool Colision::CheckEnemyHitPlayer(
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
	float radians
	) {

	bool return_status = false;

	std::pair<float, float> new_left_arm = GetPointsAfterRotaion(x_player, y_player, x_left_arm, y_left_arm, radians);
	std::pair<float, float> new_right_arm = GetPointsAfterRotaion(x_player, y_player, x_right_arm, y_right_arm, radians);
	std::pair<float, float> new_backpack = GetPointsAfterRotaion(x_player, y_player, x_backpack, y_backpack, radians);

	if (Colision::CircleRectColisionOutside(x_player, y_player, body_radius,
			x_enemy, y_enemy, enemy_width, enemy_height) ||
		Colision::CircleRectColisionOutside(new_left_arm.first, new_left_arm.second, arm_radius,
			x_enemy, y_enemy, enemy_width, enemy_height) ||
		Colision::CircleRectColisionOutside(new_right_arm.first, new_right_arm.second, arm_radius,
			x_enemy, y_enemy, enemy_width, enemy_height) ||
		Colision::CircleRectColisionOutside(new_backpack.first, new_backpack.second, backpack_radius,
			x_enemy, y_enemy, enemy_width, enemy_height) ) {
		return_status = true;
	}

	return return_status;

}

bool Colision::CheckBulletHitEnemy(
	std::vector< m1::Tema1::Bullet_Struct > & bullets,
	float x_enemy,
	float y_enemy,
	float enemy_width,
	float enemy_height, 
	float bullet_width,
	float bullet_height) {

	if (bullets.size() > 0) {
		for (int i = 0; i < bullets.size(); i++) {
			if (x_enemy < bullets[i].x_pos + bullet_width &&
				x_enemy + enemy_width > bullets[i].x_pos &&
				y_enemy < bullets[i].y_pos + bullet_height &&
				y_enemy + enemy_height > bullets[i].y_pos) {
				bullets.erase(bullets.begin() + i);
				--i;
				return true;
			}
		}
	}

	return false;

}
bool Colision::CheckEnemyInside(
	float x_enemy,
	float y_enemy,
	float enemy_width,
	float enemy_height) {


	bool return_status = false;

	if (x_enemy < 0 || y_enemy > 4 || x_enemy + enemy_width > 4 || y_enemy + enemy_height > 4) {
		return_status = true;
	}

	return return_status;

}