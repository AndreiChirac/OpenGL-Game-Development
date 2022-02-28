#include "Tema1_object2D.h"

#include <vector>

#include "core/engine.h"
#include "utils/gl_utils.h"

std::vector<VertexFormat> Tema1_object2D::BuildCircleVertices(float radius, glm::vec3 color)
{
    float x;
    float y;
    std::vector<VertexFormat> vertices;

    vertices.push_back(VertexFormat(glm::vec3(0, 0, 0), color));

    for (float i = 0; i <= 2 * M_PI; i += 0.1) {

        x = radius * cos(i);
        y = radius * sin(i);
        vertices.push_back(VertexFormat(glm::vec3(x, y, 0), color));
    }

    return vertices;
}

std::vector<unsigned int> Tema1_object2D::BuildCircleIndices(int nr_of_points)
{
    std::vector<unsigned int> indices;

    for (int i = 0; i <= nr_of_points; i++) {
        indices.push_back(0);
        indices.push_back(i);
        indices.push_back(i + 1);
    }

    indices.push_back(0);
    indices.push_back(nr_of_points);
    indices.push_back(1);

    return indices;
}

Mesh* Tema1_object2D::CreateCircle(
    const std::string& name,
    float radius,
    glm::vec3 color,
    bool fill)
{
    Mesh* body = new Mesh(name);
    std::vector<VertexFormat> vertices_body = BuildCircleVertices(radius, color);
    std::vector<unsigned int> indices = BuildCircleIndices(vertices_body.size() - 1);
    
    if (!fill) {
        body->SetDrawMode(GL_TRIANGLE_FAN);
    } else {
        // Draw 2 triangles. Add the remaining 2 indices
        indices.push_back(0);
        indices.push_back(2);
    }

    body->InitFromData(vertices_body, indices);
    return body;
}

Mesh* Tema1_object2D::CreateMouth(
    const std::string& name,
    float length,
    glm::vec3 color,
    bool fill)
{
    Mesh* body = new Mesh(name);
    std::vector<VertexFormat> vertices_body;
    std::vector<unsigned int> indices;

    vertices_body.push_back(VertexFormat(glm::vec3(0, 0, 0), color));
    vertices_body.push_back(VertexFormat(glm::vec3(length, 0, 0), color));
    vertices_body.push_back(VertexFormat(glm::vec3(0, length/2, 0), color));

    indices.push_back(0);
    indices.push_back(1);
    indices.push_back(2);

    if (!fill) {
        body->SetDrawMode(GL_TRIANGLE_FAN);
    }
    else {
        // Draw 2 triangles. Add the remaining 2 indices
        indices.push_back(0);
        indices.push_back(2);
    }

    body->InitFromData(vertices_body, indices);
    return body;
}


Mesh* Tema1_object2D::CreateRectangle(
    const std::string& name,
    glm::vec3 leftBottomCorner,
    float length, 
    float height,
    glm::vec3 color,
    bool fill)
{
    glm::vec3 corner = leftBottomCorner;

    Mesh* body = new Mesh(name);
    std::vector<VertexFormat> vertices_body;
    std::vector<unsigned int> indices = { 0, 1, 2, 3 };

    vertices_body.push_back(VertexFormat(corner, color));
    vertices_body.push_back(VertexFormat(corner + glm::vec3(length, 0, 0), color));
    vertices_body.push_back(VertexFormat(corner + glm::vec3(length, height, 0), color));
    vertices_body.push_back(VertexFormat(corner + glm::vec3(0, height, 0), color));


    if (!fill) {
        body->SetDrawMode(GL_TRIANGLE_FAN);
    }
    else {
        // Draw 2 triangles. Add the remaining 2 indices
        indices.push_back(0);
        indices.push_back(2);
    }

    body->InitFromData(vertices_body, indices);
    return body;
}

Mesh* Tema1_object2D::CreateRectangleContur(
    const std::string& name,
    glm::vec3 leftBottomCorner,
    float length,
    float height,
    glm::vec3 color,
    bool fill)
{
    glm::vec3 corner = leftBottomCorner;

    Mesh* body = new Mesh(name);
    std::vector<VertexFormat> vertices_body;
    std::vector<unsigned int> indices = { 0, 1, 2, 3 };

    vertices_body.push_back(VertexFormat(corner, color));
    vertices_body.push_back(VertexFormat(corner + glm::vec3(length, 0, 0), color));
    vertices_body.push_back(VertexFormat(corner + glm::vec3(length, height, 0), color));
    vertices_body.push_back(VertexFormat(corner + glm::vec3(0, height, 0), color));


    if (!fill) {
        body->SetDrawMode(GL_LINE_LOOP);
    }
    else {
        // Draw 2 triangles. Add the remaining 2 indices
        indices.push_back(0);
        indices.push_back(2);
    }

    body->InitFromData(vertices_body, indices);
    return body;
}

Mesh* Tema1_object2D::CreateMap(
    const std::string& name,
    float length,
    float height,
    glm::vec3 color,
    bool fill)
{
    Mesh* body = new Mesh(name);
    std::vector<VertexFormat> vertices_body;
    std::vector<unsigned int> indices = { 0, 1, 2, 3 };

    vertices_body.push_back(VertexFormat(glm::vec3(0, 0, 0), color));
    vertices_body.push_back(VertexFormat(glm::vec3(length, 0, 0), color));
    vertices_body.push_back(VertexFormat(glm::vec3(length, height, 0), color));
    vertices_body.push_back(VertexFormat(glm::vec3(0, height, 0), color));


    if (!fill) {
        body->SetDrawMode(GL_TRIANGLE_FAN);
    }
    else {
        // Draw 2 triangles. Add the remaining 2 indices
        indices.push_back(0);
        indices.push_back(2);
    }

    body->InitFromData(vertices_body, indices);
    return body;
}

Mesh* Tema1_object2D::CreateHat(
    const std::string& name,
    float radius,
    glm::vec3 color,
    bool fill)
{
    Mesh* body = new Mesh(name);
    std::vector<VertexFormat> vertices_body;
    std::vector<unsigned int> indices;

    float angleIncrement = 360.0f / 5;  // n is 5 in your case
    angleIncrement *= M_PI / 180.0f;    // convert degrees to radians
    float angle = 0.0f;
    
    for (int k = 0; k < 5; ++k) {

        vertices_body.push_back(
            VertexFormat(glm::vec3(radius * cos(angle), radius * sin(angle), 0), color));
        angle += angleIncrement;
        indices.push_back(k);
    }

    indices.push_back(5);

    if (!fill) {
        body->SetDrawMode(GL_TRIANGLE_FAN);
    }
    else {
        // Draw 2 triangles. Add the remaining 2 indices
        indices.push_back(0);
        indices.push_back(2);
    }

    body->InitFromData(vertices_body, indices);
    return body;
}