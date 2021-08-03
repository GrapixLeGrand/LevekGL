#pragma once

#include <GLFW/glfw3.h>
#include "WindowController.hpp"

namespace Levek {
class GLFWWindowController : public WindowController {

private:
    GLFWwindow* window = nullptr;
public:
    GLFWWindowController(GLFWwindow* window);
    virtual ~GLFWWindowController() {};

    virtual bool exit();
    virtual void resize(int width, int height);

};
}