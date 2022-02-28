#include "lab_m1/Tema2/maze.h"
#include <queue>


Maze::Maze()
{
}


Maze::Maze(std::unordered_map<std::string, Mesh*>& meshes)
{
	Create_Wall(meshes);
}

Maze::~Maze()
{
}

void Maze::Create_Maze(std::vector<std::vector<struct floor_struct>> &maze_floor, int length, int width, int x, int y) {
	maze_floor[x][y].status = 1;
	std::vector< std::pair <int, int> > directions;
	directions.push_back(std::make_pair(1, 0));
	directions.push_back(std::make_pair(-1, 0));
	directions.push_back(std::make_pair(0, 1));
	directions.push_back(std::make_pair(0, -1));
	std::random_shuffle(directions.begin(), directions.end());

	while (directions.size() > 0 ) {
		std::pair <int, int> direction_to_try = directions.back();
		directions.pop_back();

		int node_x = x + direction_to_try.first * 2;
		int node_y = y + direction_to_try.second * 2;

		if (Is_Wall(maze_floor, length, width, node_x, node_y)) {

			int link_cell_x = x + direction_to_try.first;
			int link_cell_y = y + direction_to_try.second;
			maze_floor[link_cell_x][link_cell_y].status = 1;

			Create_Maze(maze_floor, length, width, node_x, node_y);
		}
	}
}

bool Maze::Is_Wall(std::vector<std::vector<struct floor_struct>>& maze_floor, int length, int width, int x, int y) {
	
	if (0 <= x && x < width && 0 <= y && y < length) {
		if (maze_floor[x][y].status == 0) {
			return true;
		} else {
			return false;
		}
	} else {
		return false;
	}
}

void Maze::Create_Wall(std::unordered_map<std::string, Mesh*>& meshes)
{
	std::vector<VertexFormat> vertices
	{
		VertexFormat(glm::vec3(-1, -1,  1), glm::vec3(0, 1, 1), glm::vec3(0.95, 0.67, 0.16)),
		VertexFormat(glm::vec3(1, -1,  1), glm::vec3(1, 0, 1), glm::vec3(0.95, 0.67, 0.16)),
		VertexFormat(glm::vec3(-1,  1,  1), glm::vec3(1, 0, 0), glm::vec3(0.95, 0.67, 0.16)),
		VertexFormat(glm::vec3(1,  1,  1), glm::vec3(0, 1, 0), glm::vec3(0.95, 0.67, 0.16)),
		VertexFormat(glm::vec3(-1, -1, -1), glm::vec3(1, 1, 1), glm::vec3(0.95, 0.67, 0.16)),
		VertexFormat(glm::vec3(1, -1, -1), glm::vec3(0, 1, 1), glm::vec3(0.95, 0.67, 0.16)),
		VertexFormat(glm::vec3(-1,  1, -1), glm::vec3(1, 1, 0), glm::vec3(0.95, 0.67, 0.16)),
		VertexFormat(glm::vec3(1,  1, -1), glm::vec3(0, 0, 1), glm::vec3(0.95, 0.67, 0.16)),
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

	CreateMesh_Tema2(meshes, maze_wall.c_str(), vertices, indices);

}

bool Maze::isValid(int row, int col, int ROW, int COL)
{
	// return true if row number and column number
	// is in range
	return (row >= 0) && (row < ROW) &&
		(col >= 0) && (col < COL);
}

int Maze::BFS(std::vector<std::vector<struct floor_struct>>& maze_floor, int length, int width, Point src)
{

	bool** visited = new bool* [length];
	for (int i = 0; i < length; i++) {
		visited[i] = new bool[width];
	}

	for (size_t i = 0; i < length; i++) {
		for (size_t j = 0; j < width; j++) {
			visited[i][j] = false;
		}
	}
	// Mark the source cell as visited

	visited[(int)src.x][(int)src.z] = true;

	// Create a queue for BFS
	std::queue<queueNode> q;

	// Distance of source cell is 0
	queueNode s = { src, 0 };
	q.push(s);  // Enqueue source cell

	// Do a BFS starting from source cell
	while (!q.empty())
	{
		queueNode curr = q.front();
		Point pt = curr.pt;

		// If we have reached the destination cell,
		// we are done
		if (pt.x == 0 || pt.z == 0 || pt.x == length || pt.z == width)
			return curr.dist;

		// Otherwise dequeue the front
		// cell in the queue
		// and enqueue its adjacent cells
		q.pop();

		for (int i = 0; i < 4; i++)
		{
			int row = pt.x + rowNum[i];
			int col = pt.z + colNum[i];

			// if adjacent cell is valid, has path and
			// not visited yet, enqueue it.
			if (isValid(row, col, length, width) && maze_floor[row][col].status == 0 &&
				!visited[row][col])
			{
				// mark cell as visited and enqueue it
				visited[row][col] = true;
				queueNode Adjcell = { {row, col},
									  curr.dist + 1 };
				q.push(Adjcell);
			}
		}
	}

	// Return -1 if destination cannot be reached
	return -1;
}

Point Maze::Find_Best_Spawn(std::vector<std::vector<struct floor_struct>>& maze_floor, int length, int width) {
	int max = -1;
	Point max_coord;
	max_coord.x = -1;
	max_coord.z = -1;

	for (int i = 0; i < length; i++) {
		for (int j = 0; j < width; j++) {
			if (maze_floor[i][j].status == 0) {
				Point src;
				src.x = i;
				src.z = j;
				int help = Maze::BFS(maze_floor, length, width, src);
			
				if (help > max) {
					max = help;
					max_coord = src;
				}
			}
		}
	}
	return max_coord;
}