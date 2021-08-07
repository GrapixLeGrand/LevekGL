
#include "LevekGL.hpp"


#include <iostream>
#include <vector>

int main(void) {

    std::cout << "hello triangle !" << std::endl;

    Levek::RenderingEngine engine = Levek::RenderingEngine(800, 600);
    Levek::WindowController* windowController = engine.getWindowController();
    Levek::InputController* inputController = engine.getInputController();

    const float points[15] = {
        -0.5f, -0.5f, 0.0f, 0.5f, 1.0f,//top
        0.5f, -0.5f, 0.0f, 1.0f, 0.0f, //right
        0.0f, 0.5f, 0.0f, 0.0f, 0.0f//left
    };

    Levek::VertexArray vertexArray = Levek::VertexArray();
    Levek::VertexBuffer vertexBuffer = Levek::VertexBuffer(points, sizeof(points));

    Levek::VertexBufferLayout layout = Levek::VertexBufferLayout();
    layout.push<glm::vec3>(1);
    layout.push<glm::vec2>(1);

    vertexArray.addBuffer(vertexBuffer, layout);
    vertexArray.unbind();

    Levek::Shader shader = Levek::ShaderFactory::makeFromFile(
        SAMPLES_DIRECTORY"/hello_triangle/triangle.vert",
        SAMPLES_DIRECTORY"/hello_triangle/triangle.frag"
    );

    Levek::Renderer* renderer = engine.getRenderer();

    renderer->setClearColor({0.20f, 0.20f, 0.0f, 0.0f});
    //renderer->clear();

    while (!windowController->exit()) {
        renderer->clear();

        shader.bind();
        shader.setUniform1f("u_time", windowController->getTime() / 5);
        shader.unbind();

        renderer->draw(vertexArray, shader);

        inputController->poll();
        windowController->swapBuffers();
    }

    return 0;
}