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
    Levek::Texture unitTexture;
    bool shadows = true;

	GroundPipelineState(ModelLoader* modelLoader, float scale);
    GroundPipelineState(ModelLoader* modelLoader, float scale, bool shadows);

	void setUniforms(const glm::mat4& mvp) {
		planeShader.bind();
		unitTexture.activateAndBind(0);
        planeShader.setUniform1i("has_shadows", this->shadows);
		planeShader.setUniformMat4f("mvp", mvp);
        planeShader.setUniform1i("tex", 0);
        planeShader.setUniform1i("shadowMap", 1);
        planeShader.setUniform1f("scale", scale);
	}

	void draw(Levek::Renderer* renderer, const glm::mat4& vp) {
        setUniforms(vp * model);
		renderer->draw(planeVA, planeIBO, &planeShader);
	}

    void draw(Levek::Renderer* renderer, const Texture* depthTexture, const glm::mat4& vp, const glm::mat4& light_vp) {
        setUniforms(vp * model);
        depthTexture->activateAndBind(1);
        planeShader.setUniformMat4f("light_mvp", light_vp * model);
		renderer->draw(planeVA, planeIBO, &planeShader);
	}

};
}