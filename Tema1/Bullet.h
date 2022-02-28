#pragma once

#include <string>
#include <unordered_map>

#include "core/gpu/mesh.h"
#include "utils/glm_utils.h"
#include <lab_m1/Tema1/Tema1.h>

namespace Bullet
{
	void Move_Bullet(
		std::vector< m1::Tema1::Bullet_Struct >& bullets,
		std::vector< m1::Tema1::Obstacle_Struct > obstacles,
		float bullet_speed,
		float deltaTimeSeconds,
		float max_distance,
		float x_player,
		float y_player,
		float bullet_width,
		float bullet_height);

	m1::Tema1::Bullet_Struct Create_Bullet(
		WindowObject* window,
		m1::Tema1::ViewportSpace viewSpace,
		m1::Tema1::LogicSpace logicSpace,
		int mouseX,
		int mouseY,
		float translate_x,
		float translate_y);

	float distance(
		float x1,
		float y1,
		float x2,
		float y2);
}