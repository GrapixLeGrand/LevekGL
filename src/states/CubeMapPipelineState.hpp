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

	Levek::CubeMap* cubeMap = nullptr;
    Levek::VertexBuffer* cubeMapVbo = nullptr;
    Levek::VertexBufferLayout* cubeMapLayout = nullptr;
    Levek::VertexArray* cubeMapVa = nullptr;
    
    Levek::Shader cubeMapShader;

	SkyBoxPipelineState(const std::vector<std::string>& imagePaths);
    SkyBoxPipelineState(); //: SkyBoxPipelineState(getSkyBoxPaths()) {}
    ~SkyBoxPipelineState();

    /**
     * @brief draw the skybox on the main framebuffer
     * 
     * @param renderer
     * @param vp view projection matrix
     */
	void draw(Levek::Renderer *renderer, glm::mat4& vp);
    
};


};