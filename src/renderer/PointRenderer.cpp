#include <GL/glew.h>
#include "../OpenGLError.hpp"
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

void PointRenderer::AddPoint(glm::vec3 point, glm::vec4 color) {
    points.push_back({ point, color });
}

void PointRenderer::AddPoint(glm::vec3 point) {
    points.push_back({ point, glm::vec4{1.0f} });
}

void PointRenderer::AddAllPoints(std::vector<glm::vec3> data, glm::vec4 color) {
    for (size_t i = 0; i < data.size(); i++) {
        AddPoint(data[i], color);
    }
}

void PointRenderer::SetViewProjection(glm::mat4 viewProjection) {
    this->viewProjection = viewProjection;
}

void PointRenderer::Draw() {

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
    pointShader.bind();
    pointShader.setUniformMat4f("viewProjection", viewProjection);
    vao->bind();

    GL_CHECK(glPointSize(pointWidth));
    GL_CHECK(glDrawArrays(GL_POINTS, 0, points.size()));

    //draw...
    points.clear();
}

};