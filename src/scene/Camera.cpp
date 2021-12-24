
#include <iostream>
#include "Camera.hpp"
#include "glm/gtc/matrix_transform.hpp"

namespace Levek {
    Camera::Camera(glm::vec3 eye, glm::vec3 front, glm::vec3 up): eye(eye), front(front), up(up), yaw(0.0f), pitch(0.0f), roll(0.0f) {}
    Camera::Camera(): eye({0, 0, 0}), front({0, 0, 1}), up({0, 1, 0}), yaw(0.0f), pitch(0.0f), roll(0.0f) {}
};