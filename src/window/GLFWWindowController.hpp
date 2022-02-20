#pragma once

#include <GLFW/glfw3.h>
#include "WindowController.hpp"
#include <string>

namespace Levek {
class GLFWWindowController : public WindowController {

private:
    GLFWwindow* window = nullptr;
    float dt = 0.0f;
    float lastFrameTime = 0.0f;
    bool ImGuiWasInitialized = false;

public:
    GLFWWindowController(GLFWwindow* window);
    virtual ~GLFWWindowController();

    virtual bool exit();
    virtual void swapBuffers();
    virtual void resize(int width, int height);
    virtual float getTime();
    virtual float getDeltaTime();
    virtual void setWindowTitle(const std::string& name);
    virtual void initImGui();
};
}