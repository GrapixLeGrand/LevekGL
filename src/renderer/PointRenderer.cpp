#include "PointRenderer.hpp"
#include "shader/ShaderFactory.hpp"

namespace Levek {

PointRenderer::PointRenderer(): pointShader(ShaderFactory::makeFromFile(
            RESOURCES_DIRECTORY"/shaders/Point.vert",
            RESOURCES_DIRECTORY"/shaders/Point.frag"
        )) {
        
        /*
        pointShader = std::make_shared<Shader>(
            std::string(RESOURCES_DIRECTORY) + "/shaders/Point.vert",
            std::string(RESOURCES_DIRECTORY) + "/shaders/Point.frag"
        );*/
        vao = std::make_shared<VertexArray>();
        layout.push<glm::vec3>(1);
        layout.push<glm::vec4>(1);
    }

};