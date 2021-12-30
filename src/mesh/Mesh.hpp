#pragma once

#include <vector>
#include "glm/glm.hpp"

namespace Levek {

struct Vertex {
    glm::vec3 position;
    glm::vec2 textureCoord;
    glm::vec3 normal;
    Vertex (glm::vec3& position, glm::vec2& textureCoord, glm::vec3& normal): position(position), textureCoord(textureCoord), normal(normal) {}
};

class Mesh {

private:

    std::vector<glm::vec3> mPositions;
    std::vector<glm::vec2> mTexturesCoords;
    std::vector<glm::vec3> mNormals;

    std::vector<Vertex> mVertices;

    std::vector<unsigned int> mIndices;

public:

    Mesh(
        const std::vector<glm::vec3>& mPositions,
        const std::vector<glm::vec2>& textureCoords,
        const std::vector<glm::vec3>& normals,
        const std::vector<unsigned int>& indices
    ):
    mPositions(mPositions),
    mTexturesCoords(textureCoords),
    mNormals(normals),
    mIndices(indices) {
        mVertices.reserve(mPositions.size());

        for (size_t i = 0; i < mPositions.size(); i++) {
            Vertex v(this->mPositions[i], this->mTexturesCoords[i], this->mNormals[i]);
            mVertices.push_back(v);
        }

    }
    
    //getters and setters here

    const std::vector<glm::vec3>& getPositions() const { return mPositions; }
    const std::vector<glm::vec2>& getTexturesCoords() const { return mTexturesCoords; }
    const std::vector<glm::vec3>& getNormals() const  { return mNormals; }
    const std::vector<Vertex>& getVertices() const { return mVertices; }
    const std::vector<unsigned int>& getIndices() const { return mIndices; }

    size_t getVerticesBytes() const {
        return mVertices.size() * sizeof(Vertex);
    }

    size_t getPositionsBytes() const {
        return mPositions.size() * sizeof(glm::vec3);
    }

    size_t getTexturesCoordsBytes() const {
        return mTexturesCoords.size() * sizeof(glm::vec2);
    }

    size_t getNormalsBytes() const {
        return mNormals.size() * sizeof(glm::vec3);
    }

    size_t getIndicesBytes() const {
        return mIndices.size() * sizeof(unsigned int);
    }

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