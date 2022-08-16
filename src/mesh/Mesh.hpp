#pragma once

#include <vector>
#include "glm/glm.hpp"
#include "AABB.hpp"

namespace Levek {

struct Vertex {
    glm::vec3 position;
    glm::vec2 textureCoord;
    glm::vec3 normal;
    Vertex (glm::vec3& position, glm::vec2& textureCoord, glm::vec3& normal): position(position), textureCoord(textureCoord), normal(normal) {}
};

class Mesh {

private:

    AABB aabb;
    glm::vec3 com;

    std::vector<glm::vec3> mPositions;
    std::vector<glm::vec2> mTexturesCoords;
    std::vector<glm::vec3> mNormals;

    std::vector<Vertex> mVertices;

    std::vector<unsigned int> mIndices;

public:

    /**
     * @brief Builds the vertex buffer, compute the AABB and the location of the COM
     * 
     */
    void buildVertexBuffer() {
        mVertices.clear();
        mVertices.reserve(mPositions.size());

        //aabb.min = { std::numeric_limits<float>::max(), std::numeric_limits<float>::max(), std::numeric_limits<float>::max() };
        //aabb.max = { std::numeric_limits<float>::min(), std::numeric_limits<float>::min(), std::numeric_limits<float>::min() };

        com = {0, 0, 0};

        for (size_t i = 0; i < mPositions.size(); i++) {
            Vertex v(this->mPositions[i], this->mTexturesCoords[i], this->mNormals[i]);
            mVertices.push_back(v);

            /*aabb.min.x = std::min(aabb.min.x, mPositions[i].x);
            aabb.min.y = std::min(aabb.min.y, mPositions[i].y);
            aabb.min.z = std::min(aabb.min.z, mPositions[i].z);

            aabb.max.x = std::max(aabb.max.x, mPositions[i].x);
            aabb.max.y = std::max(aabb.max.y, mPositions[i].y);
            aabb.max.z = std::max(aabb.max.z, mPositions[i].z);
            */
            com += mPositions[i];
        }

        aabb = AABB(mPositions);
        com /= mPositions.size();

    }

    Mesh(
        const std::vector<glm::vec3>& positions,
        const std::vector<glm::vec2>& textureCoords,
        const std::vector<glm::vec3>& normals,
        const std::vector<unsigned int>& indices
    ):
    mPositions(positions),
    mTexturesCoords(textureCoords),
    mNormals(normals),
    mIndices(indices) {
        buildVertexBuffer();
    }
    
    //getters and setters here

    const std::vector<glm::vec3>& getPositions() const { return mPositions; }
    const std::vector<glm::vec2>& getTexturesCoords() const { return mTexturesCoords; }
    const std::vector<glm::vec3>& getNormals() const  { return mNormals; }
    const std::vector<Vertex>& getVertices() const { return mVertices; }
    const std::vector<unsigned int>& getIndices() const { return mIndices; }

    AABB getAABB() const {
        return aabb;
    }

    glm::vec3 getCOM() const {
        return com;
    }

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

    /**
     * @brief Rotates (or shear) the positions and normals of the model.
     * 
     * @param m 
     */
    void transform(const glm::mat3& m) {
        for (int i = 0; i < mPositions.size(); i++) {
            mPositions[i] = mPositions[i] * m;
        }
        for (int i = 0; i < mNormals.size(); i++) {
            mNormals[i] = mNormals[i] * m;
        }
        buildVertexBuffer();
    }

    void translate(const glm::vec3& offset) {
        for (int i = 0; i < mPositions.size(); i++) {
            mPositions[i] += offset;
        }
        buildVertexBuffer();
    }

    void scale(float factor) {
        for (int i = 0; i < mPositions.size(); i++) {
            mPositions[i] *= factor;
        }
        buildVertexBuffer();
    }

    /**
     * @brief Center the object over its AABB center
     * and rescale the object so that it fits in a unit box
     * 
     */
    void makeUnit() {
        glm::vec3 offset = -aabb.getCenter(); //-getHalfDimensions(); //aabb.getCenter();
        for (int i = 0; i < mPositions.size(); i++) {
            mPositions[i] += offset;
        }
        aabb = AABB(mPositions);
        float factor = 1.0f / aabb.getMaxSide();
        for (int i = 0; i < mPositions.size(); i++) {
            mPositions[i] *= factor;
        }
        buildVertexBuffer();
    }

    glm::vec3 getDimensions() {
        return aabb.max - aabb.min;
    }

    glm::vec3 getHalfDimensions() {
        return getDimensions() * 0.5f;
    }

    Mesh* copy() {
        Mesh* newMesh = new Mesh(mPositions, mTexturesCoords, mNormals, mIndices);
        return newMesh;
    }

};
}