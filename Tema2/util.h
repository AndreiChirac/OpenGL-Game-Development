#pragma once
#include <GL/glew.h>
#include <corecrt_math.h>
#include <core/window/window_object.h>
#include <unordered_map>
#include <core/gpu/mesh.h>
#include <iostream>

struct floor_struct {
	int x;
	int y;
	int z;
	int status;
};

struct Point
{
	float x;
	float z;
};

struct Point3D
{
	float x;
	float y;
	float z;
};

struct queueNode
{
	Point pt;
	int dist;
};

Mesh* CreateMesh_Tema2(std::unordered_map<std::string, Mesh*>& meshes,
	const char* name, const std::vector<VertexFormat>& vertices,
	const std::vector<unsigned int>& indices);

float distance(int x1, int y1, int z1, int x2, int y2, int z2);