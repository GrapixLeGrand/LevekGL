
#include "GLFWWindowController.hpp"
#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"

#define IMGUI_OPENGL3_GLSL_VERSION "#version 130"

namespace Levek {

    GLFWWindowController::GLFWWindowController(GLFWwindow* window) : window(window) {}

    GLFWWindowController::~GLFWWindowController() {
        if (ImGuiWasInitialized == true) {
            ImGui_ImplOpenGL3_Shutdown();
            ImGui_ImplGlfw_Shutdown();
            ImGui::DestroyContext();
        }
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
}