#pragma once

namespace Levek {

/**
 * @enum for labelling the key states
 */
enum LevekKeyStates {
    LEVEK_DOWN, LEVEK_PRESSED
};

/**
 * @enum for labelling the keys
 */
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

/**
 * @interface for IO with Mouse / Keyboard
 */
class InputController {

protected:

    

public:

    virtual void poll() = 0;
    virtual ~InputController() {}; 

    /**
     * @param key the key that we want to check
     * if pressed.
     * @return true if the key has been pressed, false
     * otherwise.
     */
    virtual bool isKeyPressed(LevekKey key) = 0;

    /**
     * @param key the key that we want to check
     * if released.
     * @return true if the key has been released, false
     * otherwise.
     */
    virtual bool isKeyReleased(LevekKey key) = 0;

    /**
     * @return true if the right mouse button has been pressed,
     * false otherwise.
     */
    virtual bool isRightMouseButtonPressed() = 0;

    /**
     * @return true if the Left mouse button has been pressed,
     * false otherwise.
     */
    virtual bool isLeftMouseButtonPressed() = 0;

    /**
     * @return the position of the mouse in pixels
     */
    virtual float getMouseX() = 0;

    /**
     * @return the position of the mouse in pixels
     */
    virtual float getMouseY() = 0;

    virtual float getMouseScrollX() = 0;

    virtual float getMouseScrollY() = 0;

};

}