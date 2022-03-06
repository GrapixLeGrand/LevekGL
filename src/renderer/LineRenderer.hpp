#pragma once

#include <vector>
#include <memory>
#include <string>
#include <GL/glew.h>
#include "glm/glm.hpp"
#include "../buffer/VertexArray.hpp"
#include "../buffer/VertexBuffer.hpp"
#include "Point.hpp"
#include "shader/Shader.hpp"


namespace Levek {

class LineRenderer {
private:
    int lineWidth = 5;
    std::shared_ptr<VertexBuffer> vbo;
    std::shared_ptr<VertexArray> vao;
    VertexBufferLayout layout;
    std::vector<Point> points;
    glm::mat4 viewProjection;
    Shader lineShader;

public:

    LineRenderer();

    void AddLine(glm::vec3 start, glm::vec3 end, glm::vec4 color) {
        points.push_back({start, color});
        points.push_back({end, color});
    }

    void AddLine(glm::vec3 start, glm::vec3 end) {
        points.push_back({start, {1, 1, 1, 1}});
        points.push_back({end, {1, 1, 1, 1}});
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
        lineShader.bind();
        lineShader.setUniformMat4f("viewProjection", viewProjection);
        vao->bind();

        GL_CHECK(glLineWidth(lineWidth));
        GL_CHECK(glDrawArrays(GL_LINES, 0, points.size()));
        
        //draw...
        points.clear();
    }

};
};
