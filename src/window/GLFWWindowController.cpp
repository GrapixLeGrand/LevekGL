#include "GLFWWindowController.hpp"

namespace Levek {

    GLFWWindowController::GLFWWindowController(GLFWwindow* window) : window(window) {}

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
}