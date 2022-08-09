#include "VoxelPipelineState.hpp"
#include "../OpenGLError.hpp"

namespace Levek {

/***
void init_rendering_payload(Block* block) {
    assert(!block->payload);
    block->payload = new BlockRenderingPayload();
    block->payload->meshVertices = new Levek::VertexBuffer(block->mesh);
    block->payload->meshIndices = new Levek::IndexBuffer(block->mesh);
    block->payload->meshLayout.push<glm::vec3>(1);
    block->payload->meshLayout.push<glm::vec2>(1);
    block->payload->meshLayout.push<glm::vec3>(1);

    block->payload->transforms = new Levek::VertexBuffer(block->models.data(), block->models.size());
    block->payload->transformsLayout.push<glm::mat4>(1, 1);

    block->payload->vertexArray = new Levek::VertexArray();
    block->payload->vertexArray->addBuffer(block->payload->meshVertices, &block->payload->meshLayout);
    block->payload->vertexArray->addBuffer(block->payload->transforms, &block->payload->transformsLayout);
}
 */

VoxelPipelineState::VoxelPipelineState(std::vector<uint16_t>& grid, std::vector<glm::vec4>& palette_arg, int X, int Y, int Z, glm::vec3 position, float scale) {

    LEVEK_RENDERING_ASSERT(palette_arg.size() < PALETTE_MAX_SIZE, "palette size must be smaller or equal to 1024\n");

    this->X = X;
    this->Y = Y;
    this->Z = Z;
    this->position = position;
    this->scale = scale;
    this->palette = palette_arg;

    for (int y = 0; y < Y; y++) {
        for (int z = 0; z < Z; z++) {
            for (int x = 0; x < X; x++) {
                int index = y * X * Z + z * X + x;
                if (grid[index] != PALETTE_EMPTY_INDEX) {
                    glm::vec3 relative_pos = {x, y, z};
                    relative_pos *= this->scale;
                    relative_pos += this->position;
                    this->positions.push_back(relative_pos);
                    this->colors.push_back(grid[index]);
                    assert(grid[index] < palette_arg.size());
                    this->num_voxels++;
                }
            }
        }
    }

}

void VoxelPipelineState::Update(std::vector<uint16_t>& grid) {

}

}