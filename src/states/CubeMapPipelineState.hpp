#pragma once

#include <vector>
#include "../texture/CubeMap.hpp"
#include "../buffer/VertexArray.hpp"
#include "../layout/VertexBufferLayout.hpp"
#include "../buffer/VertexArray.hpp"
#include "../shader/Shader.hpp"
#include "../shader/ShaderFactory.hpp"

namespace Levek {

extern float skyboxVertices[108];

struct SkyBoxPipelineState {

	Levek::CubeMap* cubeMap;
    Levek::VertexBuffer* cubeMapVbo; //= Levek::VertexBuffer(skyboxVertices, sizeof(skyboxVertices));
    Levek::VertexBufferLayout* cubeMapLayout;// = Levek::VertexBufferLayout(); cubeMapLayout.push<glm::vec3>(1);
    Levek::VertexArray* cubeMapVa;

    Levek::Shader cubeMapShader = Levek::ShaderFactory::makeFromFile(
		LEVEKGL_RESOURCES_DIRECTORY"/resources/shaders/skybox.vert",
		LEVEKGL_RESOURCES_DIRECTORY"/resources/shaders/skybox.frag"
	);

	SkyBoxPipelineState(const std::vector<std::string>& imagePaths) {
		cubeMap = new Levek::CubeMap(imagePaths, 2048, 2048);
		cubeMapVbo = new Levek::VertexBuffer(skyboxVertices, sizeof(skyboxVertices));
    	cubeMapLayout = new Levek::VertexBufferLayout(); cubeMapLayout->push<glm::vec3>(1);
		cubeMapVa = new Levek::VertexArray();
		cubeMapVa->addBuffer(cubeMapVbo, cubeMapLayout);
	}

	void draw(Levek::Renderer *renderer, glm::mat4& vp) {
		
		renderer->setDepthMask(false);
        cubeMapShader.bind();
        cubeMap->bind();
        cubeMapShader.setUniform1i("skybox", 0);
        cubeMapShader.setUniformMat4f("vp", vp);
        cubeMapShader.unbind();

        renderer->draw(cubeMapVa, &cubeMapShader);

        renderer->setDepthMask(true);
	}

	~SkyBoxPipelineState() {
		delete cubeMap;
		delete cubeMapVbo;
		delete cubeMapLayout;
		delete cubeMapVa;
	}
};

const std::vector<std::string> static getSkyBoxPaths() {

	std::vector<std::string> skyBoxImagesPaths { "right.jpg", "left.jpg", "top.jpg", "bottom.jpg", "front.jpg", "back.jpg" };
    for (auto it = skyBoxImagesPaths.begin(); it != skyBoxImagesPaths.end(); it++) {
        (*it) = LEVEKGL_RESOURCES_DIRECTORY"/resources/skybox/" + (*it);
    }

	return skyBoxImagesPaths;
}

};