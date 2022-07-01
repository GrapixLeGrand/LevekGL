#pragma once

#include <string>
#include "glm/glm.hpp"

namespace Levek {

/**
 * Interface to manage the window events
 */
class WindowController {

protected:
    int width = 0;
    int height = 0;

public:

    virtual ~WindowController() {};

    virtual bool containsPoint(glm::vec2 point) = 0;
    virtual bool exit() = 0;
    virtual void swapBuffers() = 0;
    virtual void resize(int width, int height) = 0;
    virtual float getTime() = 0;
    virtual float getDeltaTime() = 0;
    virtual void setWindowTitle(const std::string& name) = 0;
    virtual void initImGui() = 0;
};   

}