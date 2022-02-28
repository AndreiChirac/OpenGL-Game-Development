#include "lab_m1/Tema2/player.h"
#include <core/gpu/vertex_format.h>
#include <vector>
using namespace std;

Player::Player()
{
}

Player::Player(std::unordered_map<std::string, Mesh*> &meshes)
{
	x_position = 0;
	y_position = 0;
	z_position = 0;

	head = "head";
	body = "body";
	left_leg = "left_leg";
	right_leg = "right_leg";
	left_upper_arm = "left_upper_arm";
	right_upper_arm = "right_upper_arm";
	left_arm = "left_arm";
	right_arm = "right_arm";

	Create_Player_Head(meshes);
	Create_Player_Body(meshes);
	Create_Player_Left_Arm(meshes);
	Create_Player_Right_Arm(meshes);
	Create_Player_Left_Upper_Arm(meshes);
	Create_Player_Right_Upper_Arm(meshes);
	Create_Player_Left_Leg(meshes);
	Create_Player_Right_Leg(meshes);
}

Player::Player(std::unordered_map<std::string, Mesh*> &meshes, float x_position, float y_position, float z_position)
{
	x_position = x_position;
	y_position = y_position;
	z_position = z_position;

	head = "head";
	body = "body";
	left_leg = "left_leg";
	right_leg = "right_leg";
	left_upper_arm = "left_upper_arm";
	right_upper_arm = "right_upper_arm";
	left_arm = "left_arm";
	right_arm = "right_arm";

	Create_Player_Head(meshes);
	Create_Player_Body(meshes);
	Create_Player_Left_Arm(meshes);
	Create_Player_Right_Arm(meshes);
	Create_Player_Left_Upper_Arm(meshes);
	Create_Player_Right_Upper_Arm(meshes);
	Create_Player_Left_Leg(meshes);
	Create_Player_Right_Leg(meshes);
}

Player::Player(std::unordered_map<std::string, Mesh*> &meshes,
	float x_position, float y_position, float z_position, std::string head,
	std::string body, std::string leg, std::string upper_arm, std::string arm)
{
	x_position = x_position;
	y_position = y_position;
	z_position = z_position;

	head = "head";
	body = "body";
	left_leg = "left_leg";
	right_leg = "right_leg";
	left_upper_arm = "left_upper_arm";
	right_upper_arm = "right_upper_arm";
	left_arm = "left_arm";
	right_arm = "right_arm";

	Create_Player_Head(meshes);
	Create_Player_Body(meshes);
	Create_Player_Left_Arm(meshes);
	Create_Player_Right_Arm(meshes);
	Create_Player_Left_Upper_Arm(meshes);
	Create_Player_Right_Upper_Arm(meshes);
	Create_Player_Left_Leg(meshes);
	Create_Player_Right_Leg(meshes);
}

Player::~Player()
{

}

void Player::Create_Player_Head(std::unordered_map<std::string, Mesh*>& meshes)
{
	vector<VertexFormat> vertices
	{
		VertexFormat(glm::vec3(-1, -1,  1), glm::vec3(0, 1, 1), glm::vec3(0.87, 0.81, 0.71)),
		VertexFormat(glm::vec3(1, -1,  1), glm::vec3(1, 0, 1), glm::vec3(0.87, 0.81, 0.71)),
		VertexFormat(glm::vec3(-1,  1,  1), glm::vec3(1, 0, 0), glm::vec3(0.87, 0.81, 0.71)),
		VertexFormat(glm::vec3(1,  1,  1), glm::vec3(0, 1, 0), glm::vec3(0.87, 0.81, 0.71)),
		VertexFormat(glm::vec3(-1, -1, -1), glm::vec3(1, 1, 1), glm::vec3(0.87, 0.81, 0.71)),
		VertexFormat(glm::vec3(1, -1, -1), glm::vec3(0, 1, 1), glm::vec3(0.87, 0.81, 0.71)),
		VertexFormat(glm::vec3(-1,  1, -1), glm::vec3(1, 1, 0), glm::vec3(0.87, 0.81, 0.71)),
		VertexFormat(glm::vec3(1,  1, -1), glm::vec3(0, 0, 1), glm::vec3(0.87, 0.81, 0.71)),
	};

	vector<unsigned int> indices =
	{
		0, 1, 2,        1, 3, 2,
		2, 3, 7,        2, 7, 6,
		1, 7, 3,        1, 5, 7,
		6, 7, 4,        7, 5, 4,
		0, 4, 1,        1, 4, 5,
		2, 6, 4,        0, 2, 4,
	};

	CreateMesh_Tema2(meshes, head.c_str(), vertices, indices);

}

void Player::Create_Player_Body(std::unordered_map<std::string, Mesh*> &meshes)
{
	vector<VertexFormat> vertices
	{
		VertexFormat(glm::vec3(-1, -1,  1), glm::vec3(0, 1, 1), glm::vec3(0.28, 0.47, 0.47)),
		VertexFormat(glm::vec3(1, -1,  1), glm::vec3(1, 0, 1), glm::vec3(0.28, 0.47, 0.47)),
		VertexFormat(glm::vec3(-1,  1,  1), glm::vec3(1, 0, 0), glm::vec3(0.28, 0.47, 0.47)),
		VertexFormat(glm::vec3(1,  1,  1), glm::vec3(0, 1, 0), glm::vec3(0.28, 0.47, 0.47)),
		VertexFormat(glm::vec3(-1, -1, -1), glm::vec3(1, 1, 1), glm::vec3(0.28, 0.47, 0.47)),
		VertexFormat(glm::vec3(1, -1, -1), glm::vec3(0, 1, 1), glm::vec3(0.28, 0.47, 0.47)),
		VertexFormat(glm::vec3(-1,  1, -1), glm::vec3(1, 1, 0), glm::vec3(0.28, 0.47, 0.47)),
		VertexFormat(glm::vec3(1,  1, -1), glm::vec3(0, 0, 1), glm::vec3(0.28, 0.47, 0.47)),
	};

	vector<unsigned int> indices =
	{
		0, 1, 2,        1, 3, 2,
		2, 3, 7,        2, 7, 6,
		1, 7, 3,        1, 5, 7,
		6, 7, 4,        7, 5, 4,
		0, 4, 1,        1, 4, 5,
		2, 6, 4,        0, 2, 4,
	};

	CreateMesh_Tema2(meshes, body.c_str(), vertices, indices);

}

void Player::Create_Player_Left_Arm(std::unordered_map<std::string, Mesh*> &meshes)
{
	vector<VertexFormat> vertices
	{
		VertexFormat(glm::vec3(-1, -1,  1), glm::vec3(0, 1, 1), glm::vec3(0.87, 0.81, 0.71)),
		VertexFormat(glm::vec3(1, -1,  1), glm::vec3(1, 0, 1), glm::vec3(0.87, 0.81, 0.71)),
		VertexFormat(glm::vec3(-1,  1,  1), glm::vec3(1, 0, 0), glm::vec3(0.87, 0.81, 0.71)),
		VertexFormat(glm::vec3(1,  1,  1), glm::vec3(0, 1, 0), glm::vec3(0.87, 0.81, 0.71)),
		VertexFormat(glm::vec3(-1, -1, -1), glm::vec3(1, 1, 1), glm::vec3(0.87, 0.81, 0.71)),
		VertexFormat(glm::vec3(1, -1, -1), glm::vec3(0, 1, 1), glm::vec3(0.87, 0.81, 0.71)),
		VertexFormat(glm::vec3(-1,  1, -1), glm::vec3(1, 1, 0), glm::vec3(0.87, 0.81, 0.71)),
		VertexFormat(glm::vec3(1,  1, -1), glm::vec3(0, 0, 1), glm::vec3(0.87, 0.81, 0.71)),
	};

	vector<unsigned int> indices =
	{
		0, 1, 2,        1, 3, 2,
		2, 3, 7,        2, 7, 6,
		1, 7, 3,        1, 5, 7,
		6, 7, 4,        7, 5, 4,
		0, 4, 1,        1, 4, 5,
		2, 6, 4,        0, 2, 4,
	};

	CreateMesh_Tema2(meshes, left_arm.c_str(), vertices, indices);

}

void Player::Create_Player_Right_Arm(std::unordered_map<std::string, Mesh*> &meshes)
{
	vector<VertexFormat> vertices
	{
		VertexFormat(glm::vec3(-1, -1,  1), glm::vec3(0, 1, 1), glm::vec3(0.87, 0.81, 0.71)),
		VertexFormat(glm::vec3(1, -1,  1), glm::vec3(1, 0, 1), glm::vec3(0.87, 0.81, 0.71)),
		VertexFormat(glm::vec3(-1,  1,  1), glm::vec3(1, 0, 0), glm::vec3(0.87, 0.81, 0.71)),
		VertexFormat(glm::vec3(1,  1,  1), glm::vec3(0, 1, 0), glm::vec3(0.87, 0.81, 0.71)),
		VertexFormat(glm::vec3(-1, -1, -1), glm::vec3(1, 1, 1), glm::vec3(0.87, 0.81, 0.71)),
		VertexFormat(glm::vec3(1, -1, -1), glm::vec3(0, 1, 1), glm::vec3(0.87, 0.81, 0.71)),
		VertexFormat(glm::vec3(-1,  1, -1), glm::vec3(1, 1, 0), glm::vec3(0.87, 0.81, 0.71)),
		VertexFormat(glm::vec3(1,  1, -1), glm::vec3(0, 0, 1), glm::vec3(0.87, 0.81, 0.71)),
	};

	vector<unsigned int> indices =
	{
		0, 1, 2,        1, 3, 2,
		2, 3, 7,        2, 7, 6,
		1, 7, 3,        1, 5, 7,
		6, 7, 4,        7, 5, 4,
		0, 4, 1,        1, 4, 5,
		2, 6, 4,        0, 2, 4,
	};

	CreateMesh_Tema2(meshes, right_arm.c_str(), vertices, indices);

}

void Player::Create_Player_Left_Upper_Arm(std::unordered_map<std::string, Mesh*> &meshes)
{
	vector<VertexFormat> vertices
	{
		VertexFormat(glm::vec3(-1, -1,  1), glm::vec3(0, 1, 1), glm::vec3(0.28, 0.47, 0.47)),
		VertexFormat(glm::vec3(1, -1,  1), glm::vec3(1, 0, 1), glm::vec3(0.28, 0.47, 0.47)),
		VertexFormat(glm::vec3(-1,  1,  1), glm::vec3(1, 0, 0), glm::vec3(0.28, 0.47, 0.47)),
		VertexFormat(glm::vec3(1,  1,  1), glm::vec3(0, 1, 0), glm::vec3(0.28, 0.47, 0.47)),
		VertexFormat(glm::vec3(-1, -1, -1), glm::vec3(1, 1, 1), glm::vec3(0.28, 0.47, 0.47)),
		VertexFormat(glm::vec3(1, -1, -1), glm::vec3(0, 1, 1), glm::vec3(0.28, 0.47, 0.47)),
		VertexFormat(glm::vec3(-1,  1, -1), glm::vec3(1, 1, 0), glm::vec3(0.28, 0.47, 0.47)),
		VertexFormat(glm::vec3(1,  1, -1), glm::vec3(0, 0, 1), glm::vec3(0.28, 0.47, 0.47)),
	};

	vector<unsigned int> indices =
	{
		0, 1, 2,        1, 3, 2,
		2, 3, 7,        2, 7, 6,
		1, 7, 3,        1, 5, 7,
		6, 7, 4,        7, 5, 4,
		0, 4, 1,        1, 4, 5,
		2, 6, 4,        0, 2, 4,
	};

	CreateMesh_Tema2(meshes, left_upper_arm.c_str(), vertices, indices);

}

void Player::Create_Player_Right_Upper_Arm(std::unordered_map<std::string, Mesh*> &meshes)
{
	vector<VertexFormat> vertices
	{
		VertexFormat(glm::vec3(-1, -1,  1), glm::vec3(0, 1, 1), glm::vec3(0.28, 0.47, 0.47)),
		VertexFormat(glm::vec3(1, -1,  1), glm::vec3(1, 0, 1), glm::vec3(0.28, 0.47, 0.47)),
		VertexFormat(glm::vec3(-1,  1,  1), glm::vec3(1, 0, 0), glm::vec3(0.28, 0.47, 0.47)),
		VertexFormat(glm::vec3(1,  1,  1), glm::vec3(0, 1, 0), glm::vec3(0.28, 0.47, 0.47)),
		VertexFormat(glm::vec3(-1, -1, -1), glm::vec3(1, 1, 1), glm::vec3(0.28, 0.47, 0.47)),
		VertexFormat(glm::vec3(1, -1, -1), glm::vec3(0, 1, 1), glm::vec3(0.28, 0.47, 0.47)),
		VertexFormat(glm::vec3(-1,  1, -1), glm::vec3(1, 1, 0), glm::vec3(0.28, 0.47, 0.47)),
		VertexFormat(glm::vec3(1,  1, -1), glm::vec3(0, 0, 1), glm::vec3(0.28, 0.47, 0.47)),
	};

	vector<unsigned int> indices =
	{
		0, 1, 2,        1, 3, 2,
		2, 3, 7,        2, 7, 6,
		1, 7, 3,        1, 5, 7,
		6, 7, 4,        7, 5, 4,
		0, 4, 1,        1, 4, 5,
		2, 6, 4,        0, 2, 4,
	};

	CreateMesh_Tema2(meshes, right_upper_arm.c_str(), vertices, indices);

}

void Player::Create_Player_Left_Leg(std::unordered_map<std::string, Mesh*> &meshes)
{
	vector<VertexFormat> vertices
	{
		VertexFormat(glm::vec3(-1, -1,  1), glm::vec3(0, 1, 1), glm::vec3(0.22, 0.25, 0.58)),
		VertexFormat(glm::vec3(1, -1,  1), glm::vec3(1, 0, 1), glm::vec3(0.22, 0.25, 0.58)),
		VertexFormat(glm::vec3(-1,  1,  1), glm::vec3(1, 0, 0), glm::vec3(0.22, 0.25, 0.58)),
		VertexFormat(glm::vec3(1,  1,  1), glm::vec3(0, 1, 0), glm::vec3(0.22, 0.25, 0.58)),
		VertexFormat(glm::vec3(-1, -1, -1), glm::vec3(1, 1, 1), glm::vec3(0.22, 0.25, 0.58)),
		VertexFormat(glm::vec3(1, -1, -1), glm::vec3(0, 1, 1), glm::vec3(0.22, 0.25, 0.58)),
		VertexFormat(glm::vec3(-1,  1, -1), glm::vec3(1, 1, 0), glm::vec3(0.22, 0.25, 0.58)),
		VertexFormat(glm::vec3(1,  1, -1), glm::vec3(0, 0, 1), glm::vec3(0.22, 0.25, 0.58)),
	};

	vector<unsigned int> indices =
	{
		0, 1, 2,        1, 3, 2,
		2, 3, 7,        2, 7, 6,
		1, 7, 3,        1, 5, 7,
		6, 7, 4,        7, 5, 4,
		0, 4, 1,        1, 4, 5,
		2, 6, 4,        0, 2, 4,
	};

	CreateMesh_Tema2(meshes, left_leg.c_str(), vertices, indices);

}

void Player::Create_Player_Right_Leg(std::unordered_map<std::string, Mesh*> &meshes)
{
	vector<VertexFormat> vertices
	{
		VertexFormat(glm::vec3(-1, -1,  1), glm::vec3(0, 1, 1), glm::vec3(0.22, 0.25, 0.58)),
		VertexFormat(glm::vec3(1, -1,  1), glm::vec3(1, 0, 1), glm::vec3(0.22, 0.25, 0.58)),
		VertexFormat(glm::vec3(-1,  1,  1), glm::vec3(1, 0, 0), glm::vec3(0.22, 0.25, 0.58)),
		VertexFormat(glm::vec3(1,  1,  1), glm::vec3(0, 1, 0), glm::vec3(0.22, 0.25, 0.58)),
		VertexFormat(glm::vec3(-1, -1, -1), glm::vec3(1, 1, 1), glm::vec3(0.22, 0.25, 0.58)),
		VertexFormat(glm::vec3(1, -1, -1), glm::vec3(0, 1, 1), glm::vec3(0.22, 0.25, 0.58)),
		VertexFormat(glm::vec3(-1,  1, -1), glm::vec3(1, 1, 0), glm::vec3(0.22, 0.25, 0.58)),
		VertexFormat(glm::vec3(1,  1, -1), glm::vec3(0, 0, 1), glm::vec3(0.22, 0.25, 0.58)),
	};

	vector<unsigned int> indices =
	{
		0, 1, 2,        1, 3, 2,
		2, 3, 7,        2, 7, 6,
		1, 7, 3,        1, 5, 7,
		6, 7, 4,        7, 5, 4,
		0, 4, 1,        1, 4, 5,
		2, 6, 4,        0, 2, 4,
	};

	CreateMesh_Tema2(meshes, right_leg.c_str(), vertices, indices);

}