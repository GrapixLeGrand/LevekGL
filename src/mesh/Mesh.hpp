#pragma once

#include <vector>
#include "glm/glm.hpp"

namespace Levek {
class Mesh {

private:

    std::vector<glm::vec3> mVertices;
    std::vector<glm::vec2> mTexturesCoords;
    std::vector<glm::vec3> mNormals;
    std::vector<unsigned int> mIndices;

public:

    Mesh(
        const std::vector<glm::vec3>& vertices,
        const std::vector<glm::vec2>& textureCoords,
        const std::vector<glm::vec3>& normals,
        const std::vector<unsigned int>& indices
    ):
    mVertices(vertices),
    mTexturesCoords(textureCoords),
    mNormals(normals),
    mIndices(indices) {}
    
    //getters and setters here

    const std::vector<glm::vec3>& getVertices() { return mVertices; }
    const std::vector<glm::vec2>& getTexturesCoords() { return mTexturesCoords; }
    const std::vector<glm::vec3>& getNormals() { return mNormals; }
    const std::vector<unsigned int>& getIndices() { return mIndices; }

    bool hasVertices() const {
        return mVertices.size() != 0;
    }

    bool hasTexturesCoords() const {
        return mTexturesCoords.size() != 0;
    }

    bool hasNormals() const {
        return mNormals.size() != 0;
    }

};
}