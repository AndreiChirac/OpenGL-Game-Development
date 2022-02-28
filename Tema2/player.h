#include <string>
#include <unordered_map>
#include "core/gpu/mesh.h"
#include "lab_m1/Tema2/util.h"

class Player
{
public:
	Player();
	Player(std::unordered_map<std::string, Mesh*> &meshes);
	Player(std::unordered_map<std::string, Mesh*> &meshes, float x_position, float y_position, float z_position);
	Player(std::unordered_map<std::string, Mesh*> &meshes, float x_position, float y_position, float z_position, std::string head,
		std::string body, std::string leg, std::string upper_arm, std::string arm);
	~Player();

	void Create_Player_Head(std::unordered_map<std::string, Mesh*>& meshes);
	void Create_Player_Body(std::unordered_map<std::string, Mesh*> &meshes);
	void Create_Player_Left_Arm(std::unordered_map<std::string, Mesh*> &meshes);
	void Create_Player_Right_Arm(std::unordered_map<std::string, Mesh*> &meshes);
	void Create_Player_Left_Upper_Arm(std::unordered_map<std::string, Mesh*> &meshes);
	void Create_Player_Right_Upper_Arm(std::unordered_map<std::string, Mesh*> &meshes);
	void Create_Player_Left_Leg(std::unordered_map<std::string, Mesh*> &meshes);
	void Create_Player_Right_Leg(std::unordered_map<std::string, Mesh*> &meshes);


	float x_position;
	float y_position;
	float z_position;

	std::string head;
	std::string body;
	std::string left_leg;
	std::string right_leg;
	std::string left_upper_arm;
	std::string right_upper_arm;
	std::string left_arm;
	std::string right_arm;

private:
};