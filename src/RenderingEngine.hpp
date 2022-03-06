#pragma once
#include <memory>
#include "renderer/Renderer.hpp"
#include "renderer/LineRenderer.hpp"
#include "renderer/PointRenderer.hpp"
#include "glm/glm.hpp"
#include "input/InputController.hpp"
#include "window/WindowController.hpp"
#include "mesh/loader/ModelLoader.hpp"


#define DEFAULT_WINDOW_WIDTH 1280
#define DEFAULT_WINDOW_HEIGHT 720

namespace Levek {
class RenderingEngine {

private:

    //GLFWwindow* window              = nullptr;
    Renderer* renderer              = nullptr;
    //ImGuiRenderer* imGuiRenderer    = nullptr;
    LineRenderer* lineRenderer      = nullptr;
    PointRenderer* pointRenderer    = nullptr;

    ModelLoader* modelLoader = nullptr;

    InputController* inputController = nullptr;
    WindowController* windowController = nullptr;

    int windowWidth     = 0;
    int windowHeight    = 0;

public:
    
    RenderingEngine(int width, int height);
    ~RenderingEngine();
  
    /*
    bool exit() {
        return glfwWindowShouldClose(this->window);
    }*/

    /*
    void swapBuffer() {
        glfwSwapBuffers(window);
    }*/

    int getWindowHeight() const {
        return windowHeight;
    }

    int getWindowWidth() const {
        return windowWidth;
    }
    /*
    GLFWwindow* getWindow() {
        return window; 
    }*/

    Renderer* getRenderer() { return renderer; }
    //ImGuiRenderer* getImGuiRenderer() { return imGuiRenderer; }
    LineRenderer* getLineRenderer() { return lineRenderer; }
    PointRenderer* getPointRenderer() { return pointRenderer; }
    InputController* getInputController() { return inputController; }
    WindowController* getWindowController() { return windowController; }
    ModelLoader* getModelLoader() { return modelLoader; }

};
};