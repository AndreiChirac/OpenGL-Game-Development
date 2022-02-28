#include <core/gpu/mesh.h>
#include <unordered_map>
#include <lab_m1/Tema2/util.h>
#include <vector>
#include <string>

class Floor
{
public:
	Floor();
	Floor(int length, int width, std::unordered_map<std::string, Mesh*>& meshes);
	~Floor();
	void Create_Floor(std::unordered_map<std::string, Mesh*>& meshes);
	std::vector<std::vector<struct floor_struct>> maze_floor;
	std::string floor_type = "floor";

private:

};