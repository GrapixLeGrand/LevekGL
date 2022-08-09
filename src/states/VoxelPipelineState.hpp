#pragma once

#include "LevekGL.hpp"

namespace Levek {

class VoxelPipelineState {
    
    const static int PALETTE_MAX_SIZE = 1024;
    const static int PALETTE_EMPTY_INDEX = std::numeric_limits<uint16_t>::max();

    VertexBuffer* cubeVb = nullptr;
    IndexBuffer* cubeIb = nullptr;
    VertexBufferLayout cubeLayout;

    VertexArray* va = nullptr;
    
    VertexBuffer* instancesVb;
    VertexBufferLayout instancesLayout;

    int num_voxels = 0;
    float scale = static_cast<float>(1.0);
    glm::vec3 position = {0, 0, 0};
    int X = 0, Y = 0, Z = 0;

    std::vector<glm::vec3> positions;//size = voxel num
    std::vector<uint16_t> colors;//size = voxel num
    std::vector<glm::vec4> palette;//size = 1024

public:

    /**
     * @brief Construct a new Voxel Pipeline State object
     * 
     * @param grid a 16 bit integer 3D grid representing the voxels
     * @param palette a RBGA array containing the colors of the voxels (max 1024)
     * @param X 
     * @param Y 
     * @param Z 
     * @param position min position of the AABB (or vec3(0) in object referential)
     * @param scale length side of each voxel
     */
    VoxelPipelineState(std::vector<uint16_t>& grid, std::vector<glm::vec4>& palette_arg, int X, int Y, int Z, glm::vec3 position, float scale);
    void Update(std::vector<uint16_t>& grid);

};

}