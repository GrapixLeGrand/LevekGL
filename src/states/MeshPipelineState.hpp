#pragma once
#include <string>

#include "glm/gtc/quaternion.hpp"
#include "../renderer/Renderer.hpp"
#include "../buffer/VertexBuffer.hpp"
#include "../buffer/IndexBuffer.hpp"
#include "../buffer/VertexArray.hpp"
#include "../layout/VertexBufferLayout.hpp"
#include "../mesh/loader/ModelLoader.hpp"
#include "../mesh/Mesh.hpp"

namespace Levek {

class MeshPipelineState {
public:
    glm::vec3 position {0.0f, 0.0f, 0.0f};
    glm::vec3 scale {0.0f, 0.0f, 0.0f};
    glm::quat rotation {glm::vec3{0.0f, 0.0f, 0.0f}};
    
    Levek::VertexBuffer* vb = nullptr;
    Levek::IndexBuffer* ib = nullptr;
    Levek::VertexArray* va = nullptr;
    Levek::VertexBufferLayout layout;
    bool castShadow = true;//by default any body casts shadows

    Levek::Texture* texture;//single texture for now

    MeshPipelineState(ModelLoader* loader, const std::string& mesh, const std::string& texture);
    ~MeshPipelineState();
    void draw(Levek::Renderer* renderer);

};

};