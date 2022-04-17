#include "MeshPipelineState.hpp"
#include "../ErrorHandling.hpp"
#include "../mesh/Model.hpp"

namespace Levek {

    MeshPipelineState::MeshPipelineState(Levek::ModelLoader* loader, const std::string& meshPath, const std::string& texturePath) {
        
        Levek::Model* model = loader->loadFromFile(meshPath);

        LEVEKGL_ASSERT(model != nullptr, "model cannot be null! Path %s, wrong path?\n", meshPath.c_str());
        const Levek::Mesh* mesh = model->getMesh(0);
        LEVEKGL_ASSERT(model->getNumMeshes() == 1, "we allow only single meshes for now, here %zu\n", model->getNumMeshes());

        LEVEKGL_ASSERT(mesh != nullptr, "mesh cannot be null! Path %s, wrong path?\n", meshPath.c_str());
        LEVEKGL_ASSERT(mesh->hasNormals(), "mesh has no normals\n");
        LEVEKGL_ASSERT(mesh->hasTexturesCoords(), "mesh has no tex coords\n");
        LEVEKGL_ASSERT(mesh->hasVertices(), "mesh has no vertices\n");

        this->vb = new Levek::VertexBuffer(mesh);
        this->ib = new Levek::IndexBuffer(mesh);
        this->va = new Levek::VertexArray();

        Levek::VertexBufferLayout layout = Levek::VertexBufferLayout();

        layout.push<glm::vec3>(1);
        layout.push<glm::vec2>(1);
        layout.push<glm::vec3>(1);

        this->va->addBuffer(this->vb, &layout);

        this->vb->unbind();
        this->ib->unbind();
        this->va->unbind();

        this->texture = new Levek::Texture(texturePath);
    }

    MeshPipelineState::~MeshPipelineState() {

    }

    void draw(Levek::Renderer* renderer) {

    }

};