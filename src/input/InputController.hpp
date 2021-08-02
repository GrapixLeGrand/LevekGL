#pragma once
#include <GLFW/glfw3.h>

#ifndef LEVEK_INPUT_CONTROLLER
#define LEVEK_INPUT_CONTROLLER

namespace Levek {

enum LevekKeyStates {
    LEVEK_DOWN, LEVEK_PRESSED
};

enum LevekKey {
    LEVEK_KEY_A,
    LEVEK_KEY_B,
    LEVEK_KEY_C,
    LEVEK_KEY_D,
    LEVEK_KEY_E,
    LEVEK_KEY_F,
    LEVEK_KEY_G,
    LEVEK_KEY_H,
    LEVEK_KEY_I,
    LEVEK_KEY_J,
    LEVEK_KEY_K,
    LEVEK_KEY_L,
    LEVEK_KEY_M,
    LEVEK_KEY_N,
    LEVEK_KEY_O,
    LEVEK_KEY_P,
    LEVEK_KEY_Q,
    LEVEK_KEY_R,
    LEVEK_KEY_S,
    LEVEK_KEY_T,
    LEVEK_KEY_U,
    LEVEK_KEY_V,
    LEVEK_KEY_W,
    LEVEK_KEY_X,
    LEVEK_KEY_Y,
    LEVEK_KEY_Z
};



class InputController {
private:
    int LEVEK_GLFW_KEYBINDINGS[26] = {
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
    GLFWwindow* window;
public:
    void Initialize(GLFWwindow* window) {
        this->window = window;
    }

    void Poll() {
        glfwPollEvents();
    }

    bool shouldClose() {
        return glfwWindowShouldClose(this->window);
    }

    void Destroy() {}

    bool IsKeyPressed(LevekKey key) {
        int state = glfwGetKey(this->window, LEVEK_GLFW_KEYBINDINGS[key]);
        return state == GLFW_PRESS;
    }

    bool IsKeyReleased(LevekKey key) {
        int state = glfwGetKey(this->window, LEVEK_GLFW_KEYBINDINGS[key]);
        return state == GLFW_RELEASE;
    }

    bool IsRightMouseButtonPressed() {
        return glfwGetMouseButton(this->window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS;
    }

    bool IsLeftMouseButtonPressed() {
        return glfwGetMouseButton(this->window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS;    
    }

    float GetMouseX() {
        double xpos, ypos;
        glfwGetCursorPos(this->window, &xpos, &ypos);
        return (float) xpos;
    }

    float GetMouseY() {
        double xpos, ypos;
        glfwGetCursorPos(this->window, &xpos, &ypos);
        return (float) ypos;
    }

};
};

#endif