#pragma once
#include "Camera.hpp"
#include "glm/gtx/euler_angles.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/fast_trigonometry.hpp"
#include "../input/InputController.hpp"
#include "../window/WindowController.hpp"
#include "../utils/Utils.hpp"
#include <stdio.h>

namespace Levek {

/**
 * @brief Taken in parts from xna-4-3d-game-development-by-example-beginners-guide
 * 
 */
class ArcballCamera { // : public Camera

    glm::vec3 cameraPosition = glm::vec3(0.0);
    glm::vec3 targetPosition = glm::vec3(0.0);
    float elevation = 0.0f; //glm::half_pi<float>();
    float rotation = 0.0f;//glm::half_pi<float>();
    float minDistance = 0;
    float maxDistance = 1000.0f;
    float viewDistance = 22.0f;
    glm::vec3 baseCameraReference = glm::vec3(0, 0, 1);

    float nearPlane = 0.01f;
    float farPlane = 1000.0f;

    bool needViewResync = true;
    
    glm::mat4 projection; //stored (never recomputed) projection matrix
    glm::mat4 view; //precomputed view matrix
    glm::mat3 normalView; //precomputed normal view matrix
    glm::mat4 vp; //precomputed view * projection


    bool moveMode = true;
    float saveMouseX = 0.0f;
    float saveMouseY = 0.0f;

public:
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

    ArcballCamera() {}
    
    void updateCamera(InputController* inputController, WindowController* windowController) {
        
        float currentMouseX = inputController->getMouseX();
        float currentMouseY = inputController->getMouseY();

        if (moveMode) {

            float r = rotation;
            r = glm::radians(
                - (inputController->getMouseX() - 500) / 2.0f
            );
            setRotation(r);

            float e = elevation;
            e = glm::radians(
                (inputController->getMouseY() - 500) / 2.0f
            );
            setElevation(e);
            
            printf("rotation:%f, elevation:%f, viewDistance:%f\n", rotation, elevation, viewDistance);
            printf("target: [%f, %f, %f]\n", targetPosition[0], targetPosition[1], targetPosition[2]);
            needViewResync = true;
        }

        if (inputController->isRightMouseButtonPressed()) {

            if (windowController->containsPoint({currentMouseX, currentMouseY})) {
                moveMode = true;
                saveMouseX = currentMouseX;
                saveMouseY = currentMouseY;
            }

        } else {
            moveMode = false;
        }

    }

    void setProjection(glm::mat4 newProjection) {
        projection = newProjection;
    }

    inline void updateViewMatrix() {
        if (!needViewResync)
            return;

        glm::mat3 t = glm::eulerAngleYXZ(
            rotation,
            elevation,
            0.0f
        );

        cameraPosition = t * baseCameraReference;
        cameraPosition *= viewDistance;
        cameraPosition += targetPosition;

        view = glm::lookAt(
            cameraPosition,
            targetPosition,
            glm::vec3(0, 1, 0)
        );

        vp = projection * view;
        normalView = glm::inverse(glm::transpose(view));
        needViewResync = false;
    }

    void setTarget(const glm::vec3& newTarget) {
        targetPosition = newTarget;
        needViewResync = true;
    }

    void setElevation(float newElevation) {
        elevation = newElevation;
        needViewResync = true;
    }

    void setRotation(float newRotation) {
        
        rotation = newRotation;
        rotation = glm::wrapAngle(rotation);
        needViewResync = true;
    }

    void setViewDistance(float newViewDistance) {
        viewDistance = newViewDistance;
        needViewResync = true;
    }

    glm::mat4& getView() {
        updateViewMatrix();
        return view;
    }

    glm::mat3& getNormalView() {
        updateViewMatrix();
        return normalView;
    }

    glm::mat4& getViewProjection() {
        updateViewMatrix();
        return vp;
    }

    glm::mat4& getProjection() {
        return projection;
    }
};
}