#include "lab_m1/Tema2/floor.h"

Floor::Floor()
{
}

Floor::Floor(int length, int width, std::unordered_map<std::string, Mesh*>& meshes)
{	
	maze_floor = std::vector<std::vector<struct floor_struct>>(length, std::vector<struct floor_struct>(width));

	for (int i = 0; i < length; i++)
	{
		for (int j = 0; j < width; j++)
		{
			struct floor_struct help;
			help.status = 0;
			help.x = i;
			help.y = 0;
			help.z = j;

			maze_floor[i][j] = help;
		}
	}
	Create_Floor(meshes);
}

Floor::~Floor()
{
}

void Floor::Create_Floor(std::unordered_map<std::string, Mesh*>& meshes)
{
	std::vector<VertexFormat> vertices
	{
		VertexFormat(glm::vec3(-1, 0,  1), glm::vec3(0, 1, 1), glm::vec3(0.01, 0.35, 0.65)),
		VertexFormat(glm::vec3(1, 0,  1), glm::vec3(1, 0, 1), glm::vec3(0.01, 0.35, 0.65)),
		VertexFormat(glm::vec3(-1,  0,  1), glm::vec3(1, 0, 0), glm::vec3(0.01, 0.35, 0.65)),
		VertexFormat(glm::vec3(1,  0,  1), glm::vec3(0, 1, 0), glm::vec3(0.01, 0.35, 0.65)),
		VertexFormat(glm::vec3(-1, 0, -1), glm::vec3(1, 1, 1), glm::vec3(0.01, 0.35, 0.65)),
		VertexFormat(glm::vec3(1, 0, -1), glm::vec3(0, 1, 1), glm::vec3(0.01, 0.35, 0.65)),
		VertexFormat(glm::vec3(-1,  0, -1), glm::vec3(1, 1, 0), glm::vec3(0.01, 0.35, 0.65)),
		VertexFormat(glm::vec3(1,  0, -1), glm::vec3(0, 0, 1), glm::vec3(0.01, 0.35, 0.65)),
	};

	std::vector<unsigned int> indices =
	{
		0, 1, 2,        1, 3, 2,
		2, 3, 7,        2, 7, 6,
		1, 7, 3,        1, 5, 7,
		6, 7, 4,        7, 5, 4,
		0, 4, 1,        1, 4, 5,
		2, 6, 4,        0, 2, 4,
	};
	
	CreateMesh_Tema2(meshes, floor_type.c_str(), vertices, indices);

}