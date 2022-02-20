#include "Primitives.hpp"

#include <vector>

namespace Levek {
float planeVertices[] = {
    -0.5f, 0.0f, 0.5,
    0.5f, 0.0f, 0.5,
    -0.5f, 0.0f, -0.5,
    0.5f, 0.0f, -0.5
};

float planeTex[] {
    0.0f, 0.0f,
    1.0f, 0.0f,
    1.0f, 1.0f,
    0.0f, 1.0f
};

float planeNormal[] = {
    0.0f, 1.0f, 0.0f,
    0.0f, 1.0f, 0.0f
};

unsigned int planeIndices[] = {
    0, 2, 1,
    0, 3, 2
};

Mesh makePlane(float width, float height, int divisions) {
    
    int n = divisions + 1;
    std::vector<glm::vec3> vertices (n * n, {0, 0, 0});
    std::vector<glm::vec2> tex (n * n, {0, 0});
    std::vector<glm::vec3> normals (n * n, {0, 1.0, 0});
    std::vector<unsigned int> indices (3 * 2 * n * n, 0);

    for (int i = 0; i < divisions; i++) {
        for (int j = 0; j < divisions; j++) {
            //make up triangle
            //vertices[i * n + j].x = ; 
            vertices[i * n + j].y = 0.0; 
            //vertices[i * n + j].z = ;

            //make down triangle
        }
    }

    return Mesh(vertices, tex, normals, indices);
}

};