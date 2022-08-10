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

#include "../pipeline/ForwardRenderingState.hpp"

namespace Levek {

class MeshPipelineState : ForwardRenderingState {
public:
    glm::vec3 position {0.0f, 0.0f, 0.0f};
    glm::vec3 scale {0.0f, 0.0f, 0.0f};
    glm::quat rotation {glm::vec3{0.0f, 0.0f, 0.0f}};
    
    VertexBuffer* vb = nullptr;
    IndexBuffer* ib = nullptr;
    VertexArray* va = nullptr;
    VertexBufferLayout layout;
    bool castShadow = true;//by default any body casts shadows

    Texture* texture;//single texture for now

    MeshPipelineState(ModelLoader* loader, const std::string& mesh, const std::string& texture);
    ~MeshPipelineState();
    void draw(Renderer* renderer);

    virtual void render(const ForwardRenderingPassData* data) {}
};

};