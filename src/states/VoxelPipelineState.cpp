#include "VoxelPipelineState.hpp"
#include "../OpenGLError.hpp"

namespace Levek {


VoxelPipelineState::VoxelPipelineState(Levek::ModelLoader* modelLoader, std::vector<uint16_t>& grid, std::vector<glm::vec4>& palette_arg, int X, int Y, int Z, glm::vec3 position, float scale) 
: voxelShader(ShaderFactory::makeFromFile(LEVEKGL_RESOURCES_DIRECTORY"/shaders/voxel.vert", LEVEKGL_RESOURCES_DIRECTORY"/shaders/voxel.frag")) {

    LEVEK_RENDERING_ASSERT(palette_arg.size() < PALETTE_MAX_SIZE, "palette size must be smaller to 1024\n");

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
                    this->colors.push_back(grid[index] - 1);
                    //assert(grid[index] < palette_arg.size());
                    this->num_voxels++;
                }
            }
        }
    }

    Model* model = modelLoader->loadFromFile(LEVEKGL_RESOURCES_DIRECTORY"/models/cube.obj");
    this->cubeVb = new VertexBuffer(model->getMesh(0));
    this->cubeIb = new IndexBuffer(model->getMesh(0));
    this->cubeLayout.push<glm::vec3>(1);
    this->cubeLayout.push<glm::vec2>(1);
    this->cubeLayout.push<glm::vec3>(1);

    this->instancesPositionsVb = new VertexBuffer(this->positions);
    this->instancesPositionLayout.push<glm::vec3>(1, 1);
    this->instancesColorsIndicesVb = new VertexBuffer(this->colors);
    this->instancesColorLayout.push<uint16_t>(1, 1);

    this->va = new VertexArray();
    this->va->addBuffer(this->cubeVb, &this->cubeLayout);
    this->va->addBuffer(this->instancesPositionsVb, &this->instancesPositionLayout);
    this->va->addBuffer(this->instancesColorsIndicesVb, &this->instancesColorLayout);

}

void VoxelPipelineState::update(std::vector<uint16_t>& grid) {

}

void VoxelPipelineState::draw(Levek::Renderer* renderer, const glm::mat4& vp) {
    voxelShader.bind();
    voxelShader.setUniformMat4f("vp", vp);
    voxelShader.setUniform1f("scale", this->scale);
    voxelShader.setUniform4f("palette", this->palette.data(), this->palette.size());
    renderer->drawInstances(this->va, this->cubeIb, &this->voxelShader, this->num_voxels);
}

}