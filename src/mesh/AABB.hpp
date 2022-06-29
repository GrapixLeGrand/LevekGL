#pragma once

#include "glm/glm.hpp"
#include <algorithm>

namespace Levek {
    struct AABB {
        glm::vec3 min;
        glm::vec3 max;

        glm::vec3 getCenter() const {
            return glm::vec3(min + max) * 0.5f;
        }

        float getMaxSide() {
            glm::vec3 r = max - min;
            r = glm::abs(r);
            return std::max(r.x, std::max(r.y, r.z));
        }

    };
}