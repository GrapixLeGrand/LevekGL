#pragma once
#include "Camera.hpp"

namespace Levek {
class ArcballCamera : public Camera {

    glm::vec3 cameraPosition = glm::vec3(0.0);
    glm::vec3 targetPosition = glm::vec3(0.0);
    float elevation;
    float rotation;
    float minDistance;
    float maxDistance;
    float viewDistance = 12.0f;
    glm::vec3 baseCameraReference = glm::vec3(0, 0, 1);

    float nearPlane;
    float farPlane;

    bool needViewResync = true;
    
    glm::mat4 projection;

    ArcballCamera(
        glm::vec3 targetPosition,
        float initialElevation,
        float initialRotation,
        float minDistance,
        float maxDistance,
        float initialDistance,
        float aspectRatio,
        float nearPlane,
        float farPlane
    ) {
        this->targetPosition = targetPosition;
        elevation = initialElevation;
        rotation = initialRotation;
        this->minDistance = minDistance;
        this->maxDistance = maxDistance;
        viewDistance = initialDistance;
        this->nearPlane = nearPlane;
        this->farPlane = farPlane;

        projection = glm::perspective(glm::radians(45.0f), aspectRatio, nearPlane, farPlane);
        
    }

    void updateViewMatrix() {
        //glm::rotate()
    }
};
}