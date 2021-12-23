#include <iostream>

#include "LevekGL.hpp"

int main(void) {

    Levek::RenderingEngine* engine = new Levek::RenderingEngine(800, 600);
    Levek::WindowController* windowController = engine->getWindowController();
    Levek::InputController* inputController = engine->getInputController();
    
    Levek::ModelLoader* meshLoader = engine->getModelLoader();
    Levek::Model* model = meshLoader->loadFromFile(SAMPLES_DIRECTORY"/simple_mesh/dragon.obj");

    
    std::cout << "hello" << std::endl; 
    delete engine;
    return 0;
}