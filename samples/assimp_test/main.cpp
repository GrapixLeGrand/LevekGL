#include <iostream>

#include "LevekGL.hpp"
#include "../Utils.hpp"


int main(void) {

    std::cout << "Launching assimp test example" << std::endl; 

    Levek::RenderingEngine* engine = new Levek::RenderingEngine(1000, 800);
    Levek::WindowController* windowController = engine->getWindowController();
    Levek::InputController* inputController = engine->getInputController();
    
    Levek::ModelLoader* meshLoader = engine->getModelLoader();
    Levek::Model* model = meshLoader->loadFromFile(SAMPLES_DIRECTORY"/resources/sphere.obj");
       
    std::cout << "Num meshes: " << model->getNumMeshes() << std::endl;
    std::cout << "Num vertices: " << model->getMesh(0)->getVertices().size() << std::endl;

    delete engine;
    return 0;
}