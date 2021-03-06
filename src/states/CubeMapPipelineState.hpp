#pragma once

#include <vector>
#include "../texture/CubeMap.hpp"
#include "../buffer/VertexArray.hpp"
#include "../layout/VertexBufferLayout.hpp"
#include "../buffer/VertexArray.hpp"
#include "../shader/Shader.hpp"
#include "../shader/ShaderFactory.hpp"
#include "../renderer/Renderer.hpp"

namespace Levek {

extern float skyboxVertices[108];


struct SkyBoxPipelineState {

	CubeMap* cubeMap = nullptr;
    VertexBuffer* cubeMapVbo = nullptr;
    VertexBufferLayout* cubeMapLayout = nullptr;
    VertexArray* cubeMapVa = nullptr;
    
    Shader cubeMapShader;

	SkyBoxPipelineState(const std::vector<std::string>& imagePaths);
    SkyBoxPipelineState(); //: SkyBoxPipelineState(getSkyBoxPaths()) {}
    ~SkyBoxPipelineState();

    /**
     * @brief draw the skybox on the main framebuffer
     * 
     * @param renderer
     * @param vp view projection matrix
     */
	void draw(Renderer *renderer, glm::mat4& vp);
    
    void draw(Levek::Renderer *renderer, glm::mat4 view, glm::mat4& projection);
};


};