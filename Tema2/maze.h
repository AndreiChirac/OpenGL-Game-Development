#include <time.h>
#include <stdlib.h>
#include <vector>
#include <algorithm>
#include "lab_m1/Tema2/util.h"

class Maze
{
public:
	Maze();
	Maze(std::unordered_map<std::string, Mesh*>& meshes);
	~Maze();

	void Create_Maze(std::vector<std::vector<struct floor_struct>>& maze_floor, int length, int width, int x, int y);
	void Create_Wall(std::unordered_map<std::string, Mesh*>& meshes);
	bool Is_Wall(std::vector<std::vector<struct floor_struct>>& maze_floor, int length, int width, int x, int y);
	
	bool isValid(int row, int col, int ROW, int COL);
	int BFS(std::vector<std::vector<struct floor_struct>>& maze_floor, int length, int width, Point src);

	Point Find_Best_Spawn(std::vector<std::vector<struct floor_struct>>& maze_floor, int length, int width);


	std::string maze_wall = "wall";
	int rowNum[4] = {-1, 0, 0, 1};
	int colNum[4] = {0, -1, 1, 0};

private:
};