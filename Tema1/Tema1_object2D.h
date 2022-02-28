#pragma once

#include <string>

#include "core/gpu/mesh.h"
#include "utils/glm_utils.h"


namespace Tema1_object2D
{
    // Create square with given bottom left corner, length and color
    Mesh* CreateCircle(const std::string& name, float radius, glm::vec3 color, bool fill = false);
    Mesh* CreateMouth(const std::string& name, float length, glm::vec3 color, bool fill = false);
    Mesh* CreateRectangle(const std::string& name, glm::vec3 leftBottomCorner, float length, float height, glm::vec3 color, bool fill = false);
    Mesh* CreateRectangleContur(const std::string& name, glm::vec3 leftBottomCorner, float length, float height, glm::vec3 color, bool fill = false);
    Mesh* CreateMap(const std::string& name, float length, float height, glm::vec3 color, bool fill = false);
    Mesh* CreateHat(const std::string& name, float radius, glm::vec3 color, bool fill = false);

    std::vector<VertexFormat> BuildCircleVertices(float radius, glm::vec3 color);
    std::vector<unsigned int> BuildCircleIndices(int nr_of_points);
}
