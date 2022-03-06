#pragma once

#include <vector>
#include <memory>
#include <string>

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
    void AddLine(glm::vec3 start, glm::vec3 end, glm::vec4 color);
    void AddLine(glm::vec3 start, glm::vec3 end);
    void SetViewProjection(glm::mat4 viewProjection);
    void Draw();

};
};
