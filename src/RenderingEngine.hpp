
#pragma once
#include <memory>
#include <GL/glew.h>
#include "LevekGL/OpenGLError.hpp"
#include "LevekGL/renderer/Renderer.hpp"
#include "LevekGL/renderer/LineRenderer.hpp"
#include "LevekGL/renderer/PointRenderer.hpp"
//#include "LevekEngine/LevekError.hpp"
#include <GLFW/glfw3.h>
#include "ImGuiRenderer.hpp"
#include "glm/glm.hpp"

#ifndef OPENGL_RENDERING_ENGINE
#define OPENGL_RENDERING_ENGINE

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
    
    RenderingEngine(int width, int height) {

    }

    void Initialize() {
        
        /* Initialize the library */
        //int error = glfwInit();
        int err = glfwInit();
        if (!err) {
            //throw "Failed to initialize GLFW";
            LEVEK_RENDERING_FAIL("failed to initialize glfw");
        }

        LEVEK_INFO(("glew init returned : " + std::to_string(err)).c_str());

        //setup context options
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        //Create a windowed mode window and its OpenGL context
        window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Levek Engine", NULL, NULL);
        if (!window)
        {
            glfwTerminate();
            LEVEK_RENDERING_FAIL("Failed to initialize the window");   
        }

        // Make the window's context current
        glfwMakeContextCurrent(window);
        glfwSwapInterval(0);
        glewExperimental = GL_TRUE;

        if (glewInit() != GLEW_OK) {
            LEVEK_RENDERING_FAIL("failed to initialize glew");
            //throw "Failed to initialized GLEW";
        }
        
        // tell GL to only draw onto a pixel if the shape is closer to the viewer
        GL_CHECK(glEnable(GL_DEPTH_TEST)); // enable depth-testing
        GL_CHECK(glDepthFunc(GL_LESS)); // depth-testing interprets a smaller value as "closer"

    
		GL_CHECK(glEnable(GL_BLEND));
		GL_CHECK(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
        //glEnable(GL_CULL_FACE);
        //glDisable(GL_CULL_FACE);

        windowWidth = DEFAULT_WINDOW_WIDTH;
        windowHeight = DEFAULT_WINDOW_HEIGHT;

        //initialize ImGui
        imGuiRenderer = new ImGuiRenderer();
        imGuiRenderer->Initialize(window);
        renderer = new Renderer(windowWidth, windowHeight);
        renderer->setClearFlags(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        renderer->setClearColor(glm::vec4(0.0f));
        
        glEnable(GL_DEBUG_OUTPUT);
        glDebugMessageCallback(MessageCallback, 0);
        //warning I m not sure about the parameters exactly see : https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/glDebugMessageControl.xhtml
        glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, NULL, GL_FALSE);
        glDebugMessageControl(GL_DEBUG_SOURCE_API, GL_DEBUG_TYPE_ERROR, GL_DONT_CARE, 0, NULL, GL_TRUE);
        glDebugMessageControl(GL_DEBUG_SOURCE_SHADER_COMPILER, GL_DEBUG_TYPE_ERROR, GL_DONT_CARE, 0, NULL, GL_TRUE); 

        lineRenderer = new LineRenderer();
        pointRenderer = new PointRenderer();

    }

    void Destroy() {
        delete renderer;
        delete lineRenderer;
        delete pointRenderer;
        imGuiRenderer->Destroy();
        delete imGuiRenderer;
        glfwTerminate();
    }

    void SwapBuffer() {
        glfwSwapBuffers(window);
    }

    int GetWindowHeight() {
        return windowHeight;
    }

    int GetWindowWidth() {
        return windowWidth;
    }

    GLFWwindow* GetWindow() {
        return window; 
    }

    Renderer* GetRenderer() {
        return renderer;
    }

    ImGuiRenderer* GetImGuiRenderer() {
        return imGuiRenderer;
    }

    LineRenderer* GetLineRenderer() {
        return lineRenderer;
    }

    PointRenderer* GetPointRenderer() {
        return pointRenderer;
    }

};
};
#endif