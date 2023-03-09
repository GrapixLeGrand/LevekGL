#pragma once

#include <GLFW/glfw3.h>
#include "InputController.hpp"
#include "glm/glm.hpp"

namespace Levek {

class GLFWInputController : public InputController {
private:
    static const int LEVEK_GLFW_KEYBINDINGS[26];
    static const int GlfwJoysticks[4];
    static const int GlfwGamePadButtons[4];
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
    virtual void setMousePosition(glm::vec2 position);
    virtual void setMouseVisible(bool isVisible);

    virtual float gamePadAxis(Joystick index, int axisIndex);
    virtual bool gamePadButton(Joystick index, GamePadButton button);
};
}
