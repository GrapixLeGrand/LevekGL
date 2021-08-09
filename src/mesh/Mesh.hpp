#pragma once

#include <vector>
#include "glm/glm.hpp"

namespace Levek {
class Mesh {
private:
    std::vector<glm::vec3> mVertices;
    std::vector<glm::vec2> mTexturesCoords;
    std::vector<glm::vec3> mNormals;
    std::vector<int> mFaces;
public:

    Mesh(
        const std::vector<glm::vec3>& vertices,
        const std::vector<glm::vec2>& textureCoords,
        const std::vector<glm::vec3>& normals,
        const std::vector<int>& faces
    ):
    mVertices(vertices),
    mTexturesCoords(textureCoords),
    mNormals(normals),
    mFaces(faces) {}
    //getters and setters here

};
}