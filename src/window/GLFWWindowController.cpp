#include "GLFWWindowController.hpp"

namespace Levek {

    GLFWWindowController::GLFWWindowController(GLFWwindow* window) : window(window) {}

    bool GLFWWindowController::exit() {
        return glfwWindowShouldClose(this->window);
    }

    void GLFWWindowController::resize(int width, int height) {

    }

}