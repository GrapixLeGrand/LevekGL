
#pragma once
#include <memory>
//#include <GL/glew.h>
#include "OpenGLError.hpp"
#include "renderer/Renderer.hpp"
#include "renderer/LineRenderer.hpp"
#include "renderer/PointRenderer.hpp"
//#include "LevekEngine/LevekError.hpp"
//#include <GLFW/glfw3.h>
#include "ImGuiRenderer.hpp"
#include "glm/glm.hpp"

#include "input/InputController.hpp"
#include "window/WindowController.hpp"

#include "mesh/loader/ModelLoader.hpp"
#include "mesh/loader/AssimpModelLoader.hpp"

#define DEFAULT_WINDOW_WIDTH 1280
#define DEFAULT_WINDOW_HEIGHT 720

namespace Levek {
class RenderingEngine {

private:

    GLFWwindow* window              = nullptr;
    Renderer* renderer              = nullptr;
    ImGuiRenderer* imGuiRenderer    = nullptr;
    LineRenderer* lineRenderer      = nullptr;
    PointRenderer* pointRenderer    = nullptr;

    ModelLoader* modelLoader = nullptr;

    InputController* inputController = nullptr;
    WindowController* windowController = nullptr;

    int windowWidth     = 0;
    int windowHeight    = 0;

    glm::mat4 projection;

    float mFov = 90.0f;
    float mNearPlane = 0.01f;
    float mFarPlane = 100.0f;

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
    ImGuiRenderer* getImGuiRenderer() { return imGuiRenderer; }
    LineRenderer* getLineRenderer() { return lineRenderer; }
    PointRenderer* getPointRenderer() { return pointRenderer; }
    InputController* getInputController() { return inputController; }
    WindowController* getWindowController() { return windowController; }
    ModelLoader* getModelLoader() { return modelLoader; }

    glm::mat4& getProjectionMatrix() {
        return projection;
    }
};
};