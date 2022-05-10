#include "OrthographicCamera.hpp"


namespace Levek {

    OrthographicCamera::OrthographicCamera(glm::vec3 eye, glm::vec3 front, glm::vec3 up, float left, float right, float bottom, float top, float near, float far) :
        Camera(eye, front, up),
        mRight(right),
        mLeft(left),
        mBottom(bottom),
        mTop(top),
        mNear(near),
        mFar(far),
        mProjection(glm::ortho(left, right, bottom, top, near, far)) {}
}