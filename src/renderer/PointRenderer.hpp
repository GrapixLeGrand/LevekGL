#pragma once

#include <vector>
#include <memory>
#include <string>
#include <GL/glew.h>
#include "glm/glm.hpp"
#include "../buffer/VertexArray.hpp"
#include "../buffer/VertexBuffer.hpp"
#include "Point.hpp"
#include "../shader/Shader.hpp"

namespace Levek {
class PointRenderer {
private:
    int pointWidth = 5;
    std::shared_ptr<VertexBuffer> vbo;
    std::shared_ptr<VertexArray> vao;
    VertexBufferLayout layout;
    std::vector<Point> points;
    glm::mat4 viewProjection;
    Shader* pointShader = ShaderFactory::makeFromFile(
        RESOURCES_DIRECTORY"/shaders/Point.vert",
        RESOURCES_DIRECTORY"/shaders/Point.frag"
    );
public:

    PointRenderer() {
        /*
        pointShader = std::make_shared<Shader>(
            std::string(RESOURCES_DIRECTORY) + "/shaders/Point.vert",
            std::string(RESOURCES_DIRECTORY) + "/shaders/Point.frag"
        );*/
        vao = std::make_shared<VertexArray>();
        layout.push<glm::vec3>(1);
        layout.push<glm::vec4>(1);
    }

    void AddPoint(glm::vec3 point, glm::vec4 color) {
        points.push_back({point, color});
    }

    void AddPoint(glm::vec3 point) {
        points.push_back({ point, glm::vec4{1.0f} });
    }

    void AddAllPoints(std::vector<glm::vec3> data, glm::vec4 color) {
        for (size_t i = 0; i < data.size(); i++) {
            AddPoint(data[i], color);
        }
    }

    void SetViewProjection(glm::mat4 viewProjection) {
        this->viewProjection = viewProjection;
    }

    void Draw() {
        
        if (points.size() == 0) {
            return;
        }

        if (vbo == nullptr) {
            vbo = std::make_shared<VertexBuffer>(points.data(), points.size() * sizeof(Point), GL_DYNAMIC_DRAW);
            vao->addBuffer(*vbo.get(), layout);
        } else {
            vbo->Update(points.data(), points.size() * sizeof(Point));
        }
        pointShader->bind();
        pointShader->setUniformMat4f("viewProjection", viewProjection);
        vao->bind();

        GL_CHECK(glPointSize(pointWidth));
        GL_CHECK(glDrawArrays(GL_POINTS, 0, points.size()));
        
        //draw...
        points.clear();
    }
};
};