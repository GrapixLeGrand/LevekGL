
#include <iostream>
#include "Camera.hpp"
#include "glm/gtc/matrix_transform.hpp"

namespace Levek {
    Camera::Camera(glm::vec3 eye, glm::vec3 front, glm::vec3 up): mEye(eye), mFront(front), mUp(up), mYaw(0.0f), mPitch(0.0f), mRoll(0.0f) {}
    //Camera::Camera(glm::vec3 eye, glm::vec3 target):
    Camera::Camera(): mEye({0, 0, 0}), mFront({0, 0, 1}), mUp({0, 1, 0}), mYaw(0.0f), mPitch(0.0f), mRoll(0.0f) {}
};