#include "PerspectiveCamera.hpp"

namespace Levek {

    PerspectiveCamera::PerspectiveCamera(glm::vec3 eye, glm::vec3 front, glm::vec3 up, int width, int height, float fov, float near, float far) :
        Camera(eye, front, up),
        mWidth(width),
        mHeight(height),
        mFov(fov),
        mNear(near),
        mFar(far),
        mProjection(glm::perspective(glm::radians(fov), (width * 1.0f) / (1.0f * height), near, far)) {}
}