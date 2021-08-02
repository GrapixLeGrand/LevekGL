
#include "GLFWInputController.hpp"

namespace Levek {

    const int GLFWInputController::LEVEK_GLFW_KEYBINDINGS[26] = {
        GLFW_KEY_A,
        GLFW_KEY_B,
        GLFW_KEY_C,
        GLFW_KEY_D,
        GLFW_KEY_E,
        GLFW_KEY_F,
        GLFW_KEY_G,
        GLFW_KEY_H,
        GLFW_KEY_I,
        GLFW_KEY_J,
        GLFW_KEY_K,
        GLFW_KEY_L,
        GLFW_KEY_M,
        GLFW_KEY_N,
        GLFW_KEY_O,
        GLFW_KEY_P,
        GLFW_KEY_Q,
        GLFW_KEY_R,
        GLFW_KEY_S,
        GLFW_KEY_T,
        GLFW_KEY_U,
        GLFW_KEY_V,
        GLFW_KEY_W,
        GLFW_KEY_X,
        GLFW_KEY_Y,
        GLFW_KEY_Z
    };

    GLFWInputController::GLFWInputController(GLFWwindow* window): window(window) {};

    bool GLFWInputController::isKeyPressed(LevekKey key) {
        int state = glfwGetKey(this->window, LEVEK_GLFW_KEYBINDINGS[key]);
        return state == GLFW_PRESS;
    }

    bool GLFWInputController::isKeyReleased(LevekKey key) {
        int state = glfwGetKey(this->window, LEVEK_GLFW_KEYBINDINGS[key]);
        return state == GLFW_RELEASE;
    }

    bool GLFWInputController::isRightMouseButtonPressed() {
        return glfwGetMouseButton(this->window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS;
    }

    bool GLFWInputController::isLeftMouseButtonPressed() {
        return glfwGetMouseButton(this->window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS;    
    }

    float GLFWInputController::getMouseX() {
        double xpos, ypos;
        glfwGetCursorPos(this->window, &xpos, &ypos);
        return (float) xpos;
    }

    float GLFWInputController::getMouseY() {
        double xpos, ypos;
        glfwGetCursorPos(this->window, &xpos, &ypos);
        return (float) ypos;
    }


}