#pragma once

#include "Camera.hpp"
#include "glm/gtx/euler_angles.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/fast_trigonometry.hpp"
#include "../input/InputController.hpp"
#include "../window/WindowController.hpp"
#include <stdio.h>
#include "CameraBase.hpp"

namespace Levek {

class FpsCamera : public CameraBase {

    glm::vec3 cameraPosition = glm::vec3(0.0);
    
    float elevation = -glm::half_pi<float>() * 0.5f; //
    float rotation = 0.0f;//glm::half_pi<float>();

    float minDistance = 0.01f;
    float maxDistance = std::numeric_limits<float>::max();

    float viewDistance = 22.0f;
    glm::vec3 baseCameraReference = glm::vec3(0, 0, 1);
    glm::vec3 lookAt = glm::vec3(0);
    glm::vec3 lookAtDirection = glm::vec3(0);
    float nearPlane = 0.01f;
    float farPlane = 1000.0f;

    bool needViewResync = true;
    
    glm::mat4 projection; //stored (never recomputed) projection matrix
    glm::mat4 view; //precomputed view matrix
    glm::mat3 normalView; //precomputed normal view matrix
    glm::mat4 vp; //precomputed view * projection


    bool moveMode = false;
    bool mouseReleasedLastFrame = false;
    float saveWheelLastFrame = 0.0f;
    float wheelSpeed = 10.0f;
    float targetMoveSpeed = 10.0f;
    float rotationSpeed = 40.0f;

    float minElevation = glm::radians(-65.0f);
    float maxElevation = glm::radians(65.0f);

    glm::vec2 saveMouseLastFramePosition = glm::vec2(0.0);
    glm::vec2 saveMouseInitialPosition = glm::vec2(0.0);

public:

    bool printDebug = true;
    FpsCamera(
        glm::vec3 initialPosition,
        float initialElevation,
        float initialRotation,
        float aspectRatio,
        float nearPlane,
        float farPlane
    ) {
        this->cameraPosition = initialPosition;
        this->elevation = initialElevation;
        this->rotation = initialRotation;
        this->minDistance = minDistance;
        this->maxDistance = maxDistance;
        this->nearPlane = nearPlane;
        this->farPlane = farPlane;

        this->projection = glm::perspective(glm::radians(45.0f), aspectRatio, nearPlane, farPlane);
        
    }

    FpsCamera() {}
    

    void updateCameraTargetWASD(InputController* inputController, float dt) {
        
        if (inputController->isKeyPressed(Levek::LevekKey::LEVEK_KEY_W)) {
            cameraPosition += lookAtDirection * targetMoveSpeed * dt;
            needViewResync = true;
        }

        if (inputController->isKeyPressed(Levek::LevekKey::LEVEK_KEY_S)) {
            cameraPosition -= lookAtDirection * targetMoveSpeed * dt;
            needViewResync = true;
        }

        if (inputController->isKeyPressed(Levek::LevekKey::LEVEK_KEY_A)) {
            glm::vec3 cross = glm::cross(lookAtDirection, glm::vec3(0, 1, 0));
            cameraPosition -= cross * targetMoveSpeed * dt;
            needViewResync = true;
        }

        if (inputController->isKeyPressed(Levek::LevekKey::LEVEK_KEY_D)) {
            glm::vec3 cross = glm::cross(lookAtDirection, glm::vec3(0, 1, 0));
            cameraPosition += cross * targetMoveSpeed * dt;
            needViewResync = true;
        }

    }

    void updateCameraOrientation(InputController* inputController, WindowController* windowController) {
        
        float currentMouseX = inputController->getMouseX();
        float currentMouseY = inputController->getMouseY();

        if (moveMode) {
            
            float dt = windowController->getDeltaTime();
    
                rotation +=
                    rotationSpeed * dt * glm::radians(
                    -(currentMouseX - ((float) windowController->getScreenX()) * 0.5f) / 2.0f
                    );
                rotation = glm::wrapAngle(rotation);
                
                elevation += 
                rotationSpeed * dt * glm::radians(
                    (currentMouseY - ((float) windowController->getScreenY()) * 0.5f) / 2.0f
                );
                elevation = glm::clamp(elevation, this->minElevation, this->maxElevation);
            //);

            
            if (printDebug) {
                printf("mouseY %f\n", inputController->getMouseY());
                printf("rotation:%f, elevation:%f, viewDistance:%f\n", rotation, elevation, viewDistance);
                printf("position: [%f, %f, %f]\n", cameraPosition[0], cameraPosition[1], cameraPosition[2]);
                printf("view distance: %f\n", viewDistance);
            }

            inputController->setMousePosition({ windowController->getScreenX() * 0.5f, windowController->getScreenY() * 0.5f });
            needViewResync = true;
        }

        if (inputController->isRightMouseButtonPressed()) {

            if (!moveMode && mouseReleasedLastFrame) {
                if (windowController->containsPoint({currentMouseX, currentMouseY})) {
                    moveMode = true;
                    saveMouseInitialPosition = {currentMouseX, currentMouseY};
                    inputController->setMousePosition({ windowController->getScreenX() * 0.5f, windowController->getScreenY() * 0.5f });
                    inputController->setMouseVisible(false);
                }
            }

        } else {
            if (moveMode) {
                moveMode = false;
                inputController->setMousePosition(saveMouseInitialPosition);
                inputController->setMouseVisible(true);
            }
        }

        float wheelchange = saveWheelLastFrame - inputController->getMouseScrollY();
        if (wheelchange != 0.0) {
            viewDistance = glm::clamp(viewDistance + wheelchange * wheelSpeed, minDistance, maxDistance);
            needViewResync = true;
        }
        saveWheelLastFrame = inputController->getMouseScrollY();
        mouseReleasedLastFrame = !inputController->isRightMouseButtonPressed();
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

        glm::vec3 lookAtOffset = t * baseCameraReference; //rotate the reference
        this->lookAtDirection = lookAtOffset;
        this->lookAt = lookAtOffset + cameraPosition; 
        //cameraPosition *= viewDistance;
        //cameraPosition += targetPosition;

        view = glm::lookAt(
            this->cameraPosition,
            this->lookAt,
            glm::vec3(0, 1, 0)
        );

        vp = projection * view;
        normalView = glm::inverse(glm::transpose(view));
        needViewResync = false;
    }

    void setPosition(const glm::vec3& newPosition) {
        cameraPosition = newPosition;
        needViewResync = true;
    }

    void setElevation(float newElevation) {
        elevation = glm::clamp(newElevation, -glm::half_pi<float>(), glm::half_pi<float>());
        needViewResync = true;
    }

    void setRotation(float newRotation) {
        rotation = newRotation;
        rotation = glm::wrapAngle(rotation);
        needViewResync = true;
    }

    void setViewDistance(float newViewDistance) {
        viewDistance = glm::clamp(newViewDistance, minDistance, maxDistance);
        needViewResync = true;
    }

    void setRotationSpeed(float newSpeed) {
        this->rotationSpeed = newSpeed;
    }

    virtual glm::vec3 getDirection() {
        return lookAt;
    }

    virtual glm::vec3 getPosition() {
        return cameraPosition;
    }

    virtual float getRotation() {
        return rotation;
    }

    virtual float getElevation() {
        return elevation;
    }

    virtual glm::mat4& getView() {
        updateViewMatrix();
        return view;
    }

    virtual glm::mat3& getNormalView() {
        updateViewMatrix();
        return normalView;
    }

    virtual glm::mat4& getViewProjection() {
        updateViewMatrix();
        return vp;
    }

    virtual glm::mat4& getProjection() {
        return projection;
    }
    
    void setMoveSpeed(float newSpeed) {
        this->targetMoveSpeed = newSpeed;
    }

};

}