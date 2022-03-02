#include "LineRenderer.hpp"
#include "shader/ShaderFactory.hpp"

namespace Levek {

    LineRenderer::LineRenderer(): lineShader(ShaderFactory::makeFromFile(
        RESOURCES_DIRECTORY"/shaders/Line.vert",
        RESOURCES_DIRECTORY"/shaders/Line.frag"
    )) {
        /*
        lineShader = std::make_shared<Shader>(
            std::string(RESOURCES_DIRECTORY) + "/shaders/Line.vert",
            std::string(RESOURCES_DIRECTORY) + "/shaders/Line.frag"
        );*/
        vao = std::make_shared<VertexArray>();
        layout.push<glm::vec3>(1);
        layout.push<glm::vec4>(1);
    }

};