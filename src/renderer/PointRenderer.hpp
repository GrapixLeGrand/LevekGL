#pragma once

#include <vector>
#include <memory>
#include <string>
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
        Shader pointShader;
    public:

        PointRenderer();

        void AddPoint(glm::vec3 point, glm::vec4 color);

        void AddPoint(glm::vec3 point);

        void AddAllPoints(std::vector<glm::vec3> data, glm::vec4 color);

        void SetViewProjection(glm::mat4 viewProjection);

        void Draw();

    };
};