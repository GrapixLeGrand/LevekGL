#pragma once

#include "glm/glm.hpp"
#include <algorithm>

namespace Levek {
    struct AABB {
        glm::vec3 min;
        glm::vec3 max;

        AABB(std::vector<glm::vec3>& points) {
            this->min = glm::vec3(std::numeric_limits<float>::max());
            this->max = glm::vec3(std::numeric_limits<float>::lowest());
            for (auto& p : points) {
                this->min = glm::min(this->min, p);
                this->max = glm::max(this->max, p);
            }
        }
        AABB(): min(glm::vec3(0)), max(glm::vec3(0)) {}

        //TODO check but both seems correct
        glm::vec3 getCenter() const {
            glm::vec3 center = min + glm::vec3(max - min) * 0.5f;
            glm::vec3 before = glm::vec3(min + max) * 0.5f;
            return center;//
        }

        float getMaxSide() {
            glm::vec3 r = max - min;
            r = glm::abs(r);
            return std::max(r.x, std::max(r.y, r.z));
        }

    };
}