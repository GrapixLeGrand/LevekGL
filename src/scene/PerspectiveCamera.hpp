#pragma once

#include "Camera.hpp"

namespace Levek {
class PerspectiveCamera : public Camera {
private:

    int mWidth     = 0;
    int mHeight    = 0;

    glm::mat4 mProjection = glm::mat4(1.0f);

    float mFov = 90.0f;
    float mNear = 0.01f;
    float mFar = 100.0f;

public:
    
    PerspectiveCamera(glm::vec3 eye, glm::vec3 front, glm::vec3 up, int width, int height, float fov, float near, float far);
    PerspectiveCamera(glm::vec3 eye, glm::vec3 front, glm::vec3 up, int width, int height):
        PerspectiveCamera(eye, front, up, width, height, 90.0f, 0.01f, 100.0f) {}

    virtual ~PerspectiveCamera() {};

    virtual glm::mat4& getProjection() {
        return mProjection;
    }

};
};
