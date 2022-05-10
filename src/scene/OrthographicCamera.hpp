#pragma once

#include "Camera.hpp"

namespace Levek {
class OrthographicCamera : public Camera {

private:

    glm::mat4 mProjection;

    float mLeft = 0.0; 
    float mRight = 0.0; 
    float mBottom = 0.0; 
    float mTop = 0.0; 
    float mNear = 0.0; 
    float mFar = 0.0;

public:

    OrthographicCamera(glm::vec3 eye, glm::vec3 front, glm::vec3 up, float left, float right, float bottom, float top, float near, float far);
    
    virtual ~OrthographicCamera() {};

    virtual glm::mat4& getProjection() {
        return mProjection;
    }

    float getLeft() const {
        return mLeft;
    }

    float getRight() const {
        return mRight;
    }

    float getBottom() const {
        return mBottom;
    }

    float getTop() const {
        return mTop;
    }

    float getNear() const {
        return mNear;
    }

    float getFar() const {
        return mFar;
    }
};
};
