#include "glm/glm.hpp"
#include "glm/gtc/quaternion.hpp"

namespace Levek {

struct Transform {
    glm::vec3 position;
    glm::quat rotation;
    glm::vec3 scale;
    Transform(): position({0, 0, 0}), rotation({1, 0, 0, 0}), scale({1, 1, 1}) {}
    Transform(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale): position(position), rotation(glm::quat(rotation)), scale(scale) {}
    Transform(glm::vec3 position, glm::quat rotation, glm::vec3 scale): position(position), rotation(rotation), scale(scale) {}
    Transform(glm::vec3 position, glm::quat rotation): position(position), rotation(rotation), scale({1, 1, 1}) {}
    Transform(glm::vec3 position, glm::vec3 rotation): position(position), rotation(glm::quat(rotation)), scale({1, 1, 1}) {}
    Transform(glm::vec3 position): position(position), rotation({1, 0, 0, 0}), scale({1, 1, 1}) {}
};

};