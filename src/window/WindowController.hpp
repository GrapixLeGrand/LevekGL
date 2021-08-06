#pragma once

namespace Levek {

/**
 * Interface to manage the window events
 */
class WindowController {

public:

    virtual ~WindowController() {};

    virtual bool exit() = 0;
    virtual void swapBuffers() = 0;
    virtual void resize(int width, int height) = 0;

};

}