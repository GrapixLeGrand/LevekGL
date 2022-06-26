#pragma once

#include "glm/gtc/quaternion.hpp"
#include "../renderer/Renderer.hpp"
#include "../buffer/VertexBuffer.hpp"
#include "../buffer/IndexBuffer.hpp"
#include "../buffer/VertexArray.hpp"
#include "../layout/VertexBufferLayout.hpp"
#include "../mesh/loader/ModelLoader.hpp"
#include "../mesh/Mesh.hpp"
#include "../mesh/loader/ModelLoader.hpp"

namespace Levek {
struct GroundPipelineState {

    glm::mat4 model;
    float scale;
    float scaleInv;

	Levek::Shader planeShader;

    Levek::Model* planeModel;
    const Levek::Mesh* planeMesh;
    Levek::VertexBuffer* planeVBO;
    Levek::IndexBuffer* planeIBO;
    Levek::VertexBufferLayout planeLayout;
    Levek::VertexArray* planeVA;
    Levek::Texture* unitTexture;

	GroundPipelineState(ModelLoader* modelLoader, float scale);

	void setUniforms(const glm::mat4& mvp) {
		planeShader.bind();
		unitTexture->activateAndBind(0);
		planeShader.setUniformMat4f("mvp", mvp);
        planeShader.setUniform1i("tex", 0);
        planeShader.setUniform1f("scale", scale);
	}

	void draw(Levek::Renderer* renderer, const glm::mat4& vp) {
        setUniforms(vp * model);
		renderer->draw(planeVA, planeIBO, &planeShader);
	}

};
}