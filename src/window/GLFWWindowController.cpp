
#include "GLFWWindowController.hpp"
#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"

#define IMGUI_OPENGL3_GLSL_VERSION "#version 130"

namespace Levek {

    GLFWWindowController::GLFWWindowController(GLFWwindow* window) : window(window) {
        glfwGetWindowSize(window, &width, &height);
    }

    GLFWWindowController::~GLFWWindowController() {
        if (ImGuiWasInitialized == true) {
            ImGui_ImplOpenGL3_Shutdown();
            ImGui_ImplGlfw_Shutdown();
            ImGui::DestroyContext();
        }
    }


    bool GLFWWindowController::containsPoint(glm::vec2 point) {
        return (point.x >= 0 && point.x < width) && (point.y >= 0 && point.y < height);
    }

    bool GLFWWindowController::exit() {
        float currentTime = getTime();
        dt = currentTime - lastFrameTime;
        lastFrameTime = currentTime;
        return glfwWindowShouldClose(this->window);
    }

    void GLFWWindowController::swapBuffers() {
        glfwSwapBuffers(window);
    }

    void GLFWWindowController::resize(int width, int height) {

    }

    /**
     * @brief returns the time in seconds
     * 
     * @return float 
     */
    float GLFWWindowController::getTime() {
        return (float) glfwGetTime();
    }

    float GLFWWindowController::getDeltaTime() {
        return dt;
    }

    void GLFWWindowController::setWindowTitle(const std::string& name) {
        glfwSetWindowTitle(window, name.c_str());
    }

    void GLFWWindowController::initImGui() {
        ImGui::CreateContext();
        ImGui_ImplOpenGL3_Init(IMGUI_OPENGL3_GLSL_VERSION);
        ImGui_ImplGlfw_InitForOpenGL(window, true);
        ImGui::StyleColorsDark();
        ImGuiWasInitialized = true;
    };

    int GLFWWindowController::getScreenX() {
        return width;
    }

    int GLFWWindowController::getScreenY() {
        return height;
    }
}