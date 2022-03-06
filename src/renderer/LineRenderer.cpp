#include <GL/glew.h>
#include "../OpenGLError.hpp"
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


    void LineRenderer::AddLine(glm::vec3 start, glm::vec3 end, glm::vec4 color) {
        points.push_back({ start, color });
        points.push_back({ end, color });
    }

    void LineRenderer::AddLine(glm::vec3 start, glm::vec3 end) {
        points.push_back({ start, {1, 1, 1, 1} });
        points.push_back({ end, {1, 1, 1, 1} });
    }

    void LineRenderer::SetViewProjection(glm::mat4 viewProjection) {
        this->viewProjection = viewProjection;
    }

    void LineRenderer::Draw() {

        if (points.size() == 0) {
            return;
        }

        if (vbo == nullptr) {
            vbo = std::make_shared<VertexBuffer>(points.data(), points.size() * sizeof(Point), GL_DYNAMIC_DRAW);
            vao->addBuffer(*vbo.get(), layout);
        }
        else {
            vbo->Update(points.data(), points.size() * sizeof(Point));
        }
        lineShader.bind();
        lineShader.setUniformMat4f("viewProjection", viewProjection);
        vao->bind();

        GL_CHECK(glLineWidth(lineWidth));
        GL_CHECK(glDrawArrays(GL_LINES, 0, points.size()));

        //draw...
        points.clear();
    }

};