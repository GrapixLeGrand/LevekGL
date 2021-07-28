#pragma once

#include "glm/glm.hpp"
#include "LineRenderer.hpp"

namespace Levek {
static void AddBox(LineRenderer* lineRenderer, const glm::vec3& position, const glm::vec3& half) {

    glm::vec3 v1 = position;
    v1.x -= half.x;
    v1.y += half.y;
    v1.z -= half.z;

    glm::vec3 v2 = position;
    v2.x -= half.x;
    v2.y += half.y;
    v2.z += half.z;

    glm::vec3 v3 = position;
    v3.x -= half.x;
    v3.y -= half.y;
    v3.z += half.z;

    glm::vec3 v4 = position;
    v4.x -= half.x;
    v4.y -= half.y;
    v4.z -= half.z;

    glm::vec3 v5 = position;
    v5.x += half.x;
    v5.y -= half.y;
    v5.z -= half.z;

    glm::vec3 v6 = position;
    v6.x += half.x;
    v6.y += half.y;
    v6.z -= half.z;

    glm::vec3 v7 = position;
    v7.x += half.x;
    v7.y += half.y;
    v7.z += half.z;

    glm::vec3 v8 = position;
    v8.x += half.x;
    v8.y -= half.y;
    v8.z += half.z;

    lineRenderer->AddLine(v1, v2);
    lineRenderer->AddLine(v2, v3);
    lineRenderer->AddLine(v3, v4);
    lineRenderer->AddLine(v4, v1);

    lineRenderer->AddLine(v1, v6);
    lineRenderer->AddLine(v4, v5);
    lineRenderer->AddLine(v3, v8);
    lineRenderer->AddLine(v2, v7);

    lineRenderer->AddLine(v6, v7);
    lineRenderer->AddLine(v7, v8);
    lineRenderer->AddLine(v8, v5);
    lineRenderer->AddLine(v5, v6);

};
};