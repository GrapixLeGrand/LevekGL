
#include "LevekGL.hpp"

#include <iostream>
#include <vector>

int main(void) {

    std::cout << "hello triangle !" << std::endl;
    Levek::RenderingEngine engine = Levek::RenderingEngine(1024, 1024);
    Levek::WindowController* windowController = engine.getWindowController();
    Levek::InputController* inputController = engine.getInputController();

    const float points[9] = {
        -0.5f, -0.5f, 0.0f, //top
        0.5f, -0.5f, 0.0f, //right
        0.0f, 0.5f, 0.0f //left
    };

    Levek::VertexBuffer vertexBuffer = Levek::VertexBuffer(points, 9 * sizeof(float));
    
    Levek::VertexBufferLayout layout = Levek::VertexBufferLayout();
    layout.push<glm::vec3>(1);

    //layout.push<glm::vec2>(1);

    //const unsigned int indexes[3] = {0, 1, 2};

    //Levek::IndexBuffer indexBuffer = Levek::IndexBuffer(indexes, 3);

    Levek::VertexArray vertexArray = Levek::VertexArray();
    vertexArray.addBuffer(vertexBuffer, layout);

    vertexBuffer.unbind();
    vertexArray.unbind();

    Levek::Shader shader = Levek::ShaderFactory::makeFromFile(
        SAMPLES_DIRECTORY"/hello_triangle/triangle.vert",
        SAMPLES_DIRECTORY"/hello_triangle/triangle.frag"
    );
    shader.unbind();

    Levek::Renderer* renderer = engine.getRenderer();

    renderer->setClearColor({1.0f, 0.0f, 0.0f, 0.0f});
    //renderer->clear();
    
    while (!windowController->exit()) {
        //renderer->clear();

        //shader.bind();
        //vertexArray.bind();
        renderer->draw(vertexArray, shader);

        vertexArray.unbind();
        shader.unbind();

        windowController->swapBuffers();
        inputController->poll();
    }

    return 0;
}