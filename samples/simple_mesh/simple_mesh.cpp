#include <iostream>

#include "LevekGL.hpp"

int main(void) {

    std::cout << "Launching dragon example" << std::endl; 

    Levek::RenderingEngine* engine = new Levek::RenderingEngine(800, 600);
    Levek::WindowController* windowController = engine->getWindowController();
    Levek::InputController* inputController = engine->getInputController();
    
    Levek::ModelLoader* meshLoader = engine->getModelLoader();
    Levek::Model* model = meshLoader->loadFromFile(SAMPLES_DIRECTORY"/simple_mesh/dragon.obj");

    Levek::Renderer* renderer = engine->getRenderer();
    renderer->setClearColor({0.20f, 0.20f, 0.0f, 0.0f});
    
    Levek::Mesh* mesh = model->getMesh(0);
    Levek::Transform* transform = model->getTransform(0);

    Levek::VertexArray vertexArray();
    Levek::VertexBuffer vertexBuffer(mesh);
    Levek::IndexBuffer indexBuffer(mesh);

    Levek::VertexBufferLayout layout = Levek::VertexBufferLayout();
    layout.push<glm::vec3>(2);

    

    while (!windowController->exit()) {
        renderer->clear();

        //shader.bind();
        //shader.setUniform1f("u_time", windowController->getTime() / 5);
        //shader.unbind();

        //renderer->draw(vertexArray, shader);

        inputController->poll();
        windowController->swapBuffers();
    }

    
    delete engine;
    return 0;
}