#include "lab_m1/Tema2/util.h"
#include <map>
#include <chrono>

class Enemy
{
public:
	Enemy();
	Enemy(Point spawn, Point initial_pos, float speed);
	std::vector<Enemy*> Create_Enemy(std::vector<std::vector<struct floor_struct>>& maze_floor, int floor_width, int floor_length);
	void Move_Enemy(std::vector<Enemy*>& enemys, float delta_time, float offsetof);
	//void Add_Map_Entry();
	~Enemy();

	Point spawn;
	Point initial_pos;
	int state = 0;
	float speed;
	std::map<std::string, std::tuple<float, float, float>> map_object;
	std::chrono::time_point<std::chrono::system_clock> animation_start;
	std::chrono::time_point<std::chrono::system_clock> animation_end;
	bool status = false;

private:

};