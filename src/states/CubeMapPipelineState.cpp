#include "CubeMapPipelineState.hpp"

namespace Levek {


    
        float skyboxVertices[] = {
        // positions          
        -1.0f,  1.0f, -1.0f,
        -1.0f, -1.0f, -1.0f,
        1.0f, -1.0f, -1.0f,
        1.0f, -1.0f, -1.0f,
        1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,

        -1.0f, -1.0f,  1.0f,
        -1.0f, -1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f,  1.0f,
        -1.0f, -1.0f,  1.0f,

        1.0f, -1.0f, -1.0f,
        1.0f, -1.0f,  1.0f,
        1.0f,  1.0f,  1.0f,
        1.0f,  1.0f,  1.0f,
        1.0f,  1.0f, -1.0f,
        1.0f, -1.0f, -1.0f,

        -1.0f, -1.0f,  1.0f,
        -1.0f,  1.0f,  1.0f,
        1.0f,  1.0f,  1.0f,
        1.0f,  1.0f,  1.0f,
        1.0f, -1.0f,  1.0f,
        -1.0f, -1.0f,  1.0f,

        -1.0f,  1.0f, -1.0f,
        1.0f,  1.0f, -1.0f,
        1.0f,  1.0f,  1.0f,
        1.0f,  1.0f,  1.0f,
        -1.0f,  1.0f,  1.0f,
        -1.0f,  1.0f, -1.0f,

        -1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f,  1.0f,
        1.0f, -1.0f, -1.0f,
        1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f,  1.0f,
        1.0f, -1.0f,  1.0f
    };

    SkyBoxPipelineState::SkyBoxPipelineState(const std::vector<std::string>& imagePaths) {
		cubeMap = new Levek::CubeMap(imagePaths, 2048, 2048);
		cubeMapVbo = new Levek::VertexBuffer(skyboxVertices, sizeof(skyboxVertices));
    	cubeMapLayout = new Levek::VertexBufferLayout(); cubeMapLayout->push<glm::vec3>(1);
		cubeMapVa = new Levek::VertexArray();
		cubeMapVa->addBuffer(cubeMapVbo, cubeMapLayout);
    cubeMapShader = Levek::ShaderFactory::makeFromFile(
		  LEVEKGL_RESOURCES_DIRECTORY"/shaders/skybox.vert",
		  LEVEKGL_RESOURCES_DIRECTORY"/shaders/skybox.frag"
    );
	}

    void SkyBoxPipelineState::draw(Levek::Renderer *renderer, glm::mat4& vp) {
		
		renderer->setDepthMask(false);
        cubeMapShader.bind();
        cubeMap->bind();
        cubeMapShader.setUniform1i("skybox", 0);
        cubeMapShader.setUniformMat4f("vp", vp);
        cubeMapShader.unbind();

        renderer->draw(cubeMapVa, &cubeMapShader);

        renderer->setDepthMask(true);
	}

    SkyBoxPipelineState::~SkyBoxPipelineState() {
		delete cubeMap;
		delete cubeMapVbo;
		delete cubeMapLayout;
		delete cubeMapVa;
	}
    
}