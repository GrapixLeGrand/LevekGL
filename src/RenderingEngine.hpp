
#pragma once
#include <memory>
#include <GL/glew.h>
#include "OpenGLError.hpp"
#include "renderer/Renderer.hpp"
#include "renderer/LineRenderer.hpp"
#include "renderer/PointRenderer.hpp"
//#include "LevekEngine/LevekError.hpp"
#include <GLFW/glfw3.h>
#include "ImGuiRenderer.hpp"
#include "glm/glm.hpp"

#define DEFAULT_WINDOW_WIDTH 1280
#define DEFAULT_WINDOW_HEIGHT 720

namespace Levek {
class RenderingEngine {

private:
    GLFWwindow* window;
    Renderer* renderer;
    ImGuiRenderer* imGuiRenderer;
    LineRenderer* lineRenderer;
    PointRenderer* pointRenderer;
    int windowWidth = 0;
    int windowHeight = 0;
public:
    
    RenderingEngine(int width, int height);
    ~RenderingEngine();

    /*
    void destroy() {
        delete renderer;
        delete lineRenderer;
        delete pointRenderer;
        imGuiRenderer->Destroy();
        delete imGuiRenderer;
        glfwTerminate();
    }*/

    void swapBuffer() {
        glfwSwapBuffers(window);
    }

    int getWindowHeight() const {
        return windowHeight;
    }

    int getWindowWidth() const {
        return windowWidth;
    }

    GLFWwindow* getWindow() {
        return window; 
    }

    Renderer* getRenderer() {
        return renderer;
    }

    ImGuiRenderer* getImGuiRenderer() {
        return imGuiRenderer;
    }

    LineRenderer* getLineRenderer() {
        return lineRenderer;
    }

    PointRenderer* getPointRenderer() {
        return pointRenderer;
    }

};
};