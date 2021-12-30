#pragma once

#include <iostream>
//#include "glm/glm.hpp"
#include "LevekGL.hpp"

namespace Levek {
extern void printMat4(const glm::mat4& m);
extern void printMat3(const glm::mat3& m);
extern void printVec3(const glm::vec3& v);

static void drawOrthographicBoundingBox(LineRenderer* lineRenderer, const OrthographicCamera* camera) {

    /**
     * The box is 
     * 
     */

    //glm::vec3 half(camera->);

    glm::vec3 v1 = camera->getEye();
    v1.x -= camera->getLeft();
    v1.y += camera->getNear();
    v1.z -= camera->getBottom();
    
    glm::vec3 v2 = camera->getEye();
    v2.x -= camera->getLeft();
    v2.z += camera->getTop();

    glm::vec3 v3 = camera->getEye();
    v3.x += camera->getRight();
    v3.z += camera->getTop();

    glm::vec3 v4 = camera->getEye();
    v4.x += camera->getRight();
    v4.z -= camera->getBottom();

    glm::vec3 v5 = v1;
    glm::vec3 v6 = v2;
    glm::vec3 v7 = v3;
    glm::vec3 v8 = v4;

    v1.y += camera->getNear();
    v2.y += camera->getNear();
    v3.y += camera->getNear();
    v4.y += camera->getNear();

    v5.y -= camera->getFar();
    v6.y -= camera->getFar();
    v7.y -= camera->getFar();
    v8.y -= camera->getFar();

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

static void addBox(LineRenderer* lineRenderer, const glm::vec3& position, const glm::vec3& half) {

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


/*
static void addBox(LineRenderer* lineRenderer, const glm::vec3& position, const ) {

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

};*/

};
