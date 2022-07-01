#pragma once

#include <GLFW/glfw3.h>
#include "InputController.hpp"

namespace Levek {

class GLFWInputController : public InputController {
private:
    static const int LEVEK_GLFW_KEYBINDINGS[26];
    GLFWwindow* window = nullptr;
public:

    GLFWInputController(GLFWwindow* window);
    virtual ~GLFWInputController() {}

    virtual void poll() {
        glfwPollEvents();
    }

    virtual bool isKeyPressed(LevekKey key);
    virtual bool isKeyReleased(LevekKey key);
    virtual bool isRightMouseButtonPressed();
    virtual bool isLeftMouseButtonPressed();
    virtual float getMouseX();
    virtual float getMouseY();
    virtual float getMouseScrollX();
    virtual float getMouseScrollY();

};
}
