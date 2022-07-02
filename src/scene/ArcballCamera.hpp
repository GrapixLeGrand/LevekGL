#pragma once
#include "Camera.hpp"
#include "glm/gtx/euler_angles.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/fast_trigonometry.hpp"
#include "../input/InputController.hpp"
#include "../window/WindowController.hpp"
#include <stdio.h>

namespace Levek {

/**
 * @brief Taken in parts from xna-4-3d-game-development-by-example-beginners-guide
 * 
 */
class ArcballCamera { // : public Camera

    glm::vec3 cameraPosition = glm::vec3(0.0);
    glm::vec3 targetPosition = glm::vec3(0.0);
    float elevation = -glm::half_pi<float>() * 0.5f; //
    float rotation = 0.0f;//glm::half_pi<float>();
    float minDistance = 0.01f;
    float maxDistance = std::numeric_limits<float>::max();
    float viewDistance = 22.0f;
    glm::vec3 baseCameraReference = glm::vec3(0, 0, 1);

    float nearPlane = 0.01f;
    float farPlane = 1000.0f;

    bool needViewResync = true;
    
    glm::mat4 projection; //stored (never recomputed) projection matrix
    glm::mat4 view; //precomputed view matrix
    glm::mat3 normalView; //precomputed normal view matrix
    glm::mat4 vp; //precomputed view * projection


    bool moveMode = false;
    bool mouseReleasedLastFrame = false;
    float saveScroll = 0.0f;
    float targetMoveSpeed = 10.0f;

    glm::vec2 saveMouseLastFramePosition = glm::vec2(0.0);
    glm::vec2 saveMouseInitialPosition = glm::vec2(0.0);

public:

    bool printDebug = true;
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
    

    void updateCameraTargetWASD(InputController* inputController, float dt) {
        
        if (inputController->isKeyPressed(Levek::LevekKey::LEVEK_KEY_W)) {
            targetPosition.z -= targetMoveSpeed * dt;
            needViewResync = true;
        }

        if (inputController->isKeyPressed(Levek::LevekKey::LEVEK_KEY_S)) {
            targetPosition.z += targetMoveSpeed * dt;
            needViewResync = true;
        }

        if (inputController->isKeyPressed(Levek::LevekKey::LEVEK_KEY_A)) {
            targetPosition.x -= targetMoveSpeed * dt;
            needViewResync = true;
        }

        if (inputController->isKeyPressed(Levek::LevekKey::LEVEK_KEY_D)) {
            targetPosition.x += targetMoveSpeed * dt;
            needViewResync = true;
        }

    }

    void updateCameraOrientation(InputController* inputController, WindowController* windowController) {
        
        float currentMouseX = inputController->getMouseX();
        float currentMouseY = inputController->getMouseY();

        if (moveMode) {

            //setRotation(
                rotation +=
                glm::radians(
                    -(currentMouseX - windowController->getScreenX() * 0.5f) / 2.0f
                );
                rotation = glm::wrapAngle(rotation);
            //);

            //setElevation(
                
                elevation += 
                glm::radians(
                    (currentMouseY - windowController->getScreenY() * 0.5f) / 2.0f
                );
                elevation = glm::clamp(elevation, glm::radians(-70.0f), glm::radians(-10.0f));
            //);

            float scroll = inputController->getMouseScrollY();
            //setViewDistance(viewDistance + scroll - saveScroll);
            
            if (printDebug) {
                printf("mouseY %f\n", inputController->getMouseY());
                printf("rotation:%f, elevation:%f, viewDistance:%f\n", rotation, elevation, viewDistance);
                printf("target: [%f, %f, %f]\n", targetPosition[0], targetPosition[1], targetPosition[2]);
                printf("scrolling %f %f\n", scroll, scroll - saveScroll);
            }

            inputController->setMousePosition({ windowController->getScreenX() * 0.5f, windowController->getScreenY() * 0.5f });

            saveScroll = scroll;
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